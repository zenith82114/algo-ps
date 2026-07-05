/*
 * ICPC, Regionals, Asia Pacific, Korea, Asia Regional - Seoul 2019
 * F. Quadrilaterals
 * QOJ 10951
 *
 * Bulldozer trick
 * Date: 2026.7.5
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;
using ii = pair<int, int>;

struct vec2 {
    i64 dx, dy;
    int i, j;

    vec2(int i, int j, const ii& a, const ii& b)
    : dx(b.first - a.first), dy(b.second - a.second), i(i), j(j) {}

    bool operator<(const vec2& oth) const {
        i64 cx = dy*oth.dx - dx*oth.dy;
        return cx? cx < 0 : tie(i, j) < tie(oth.i, oth.j);
    }
    bool operator==(const vec2& oth) const {
        return dy*oth.dx == dx*oth.dy;
    }
};

i64 cross(const ii& a, const ii& b, const ii& c) {
    auto [ax, ay] = a;
    auto [bx, by] = b;
    auto [cx, cy] = c;
    i64 x1 = bx - ax, x2 = cx - ax;
    i64 y1 = by - ay, y2 = cy - ay;
    return x1*y2 - y1*x2;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n; cin >> n;
    vector<ii> p(n);
    for (auto& [x, y] : p) cin >> x >> y;
    sort(begin(p), end(p));

    vector<vec2> v;
    for (int i = 0; i < n; ++i)
    for (int j = i+1; j < n; ++j) v.emplace_back(i, j, p[i], p[j]);
    sort(begin(v), end(v));

    vector<int> loc(n); iota(begin(loc), end(loc), 0);

    i64 min_area = INT64_MAX;
    i64 ans_cnvx = 0, ans_area = 0;

    for (const auto& [dx, dy, i, j] : v) {
        int k = min(loc[i], loc[j]);
        ans_cnvx += k*(n - k - 2);

        for (int i = max(0, k-2); i < k; ++i)
        for (int j = k+2; j < min(k+4, n); ++j) {
            i64 area = abs(cross(p[k], p[k+1], p[i])) + abs(cross(p[k], p[k+1], p[j]));

            if (min_area > area) min_area = area, ans_area = 0;
            if (min_area == area) {
                bool convex = ((cross(p[i], p[j], p[k]) ^ cross(p[i], p[j], p[k+1])) < 0);
                ans_area += convex? 1 : 2;
            }
        }

        swap(loc[i], loc[j]);
        swap(p[loc[i]], p[loc[j]]);
    }

    cout << (ans_cnvx + ans_area);
    return 0;
}
