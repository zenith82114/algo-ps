/*
 * 한국정보올림피아드, KOI 2019 2차대회, 고등부 4. 고압선
 * BOJ 17625
 * JUNGOL 3437
 *
 * Bulldozer trick
 * Date: 2024.3.3
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;

struct point {
    i64 x, y;
    bool operator<(const point& oth) const {
        return tie(x, y) < tie(oth.x, oth.y);
    }
};

struct vec2 {
    i64 dx, dy;
    int i, j;
    bool prll;
    vec2(int i, int j, const point& a, const point& b, bool p)
    : dx{b.x - a.x}, dy{b.y - a.y}, i{i}, j{j}, prll{p} {}

    bool operator<(const vec2& oth) const {
        i64 cx = dy*oth.dx - dx*oth.dy;
        return cx? cx < 0 : tie(i, j) < tie(oth.i, oth.j);
    }
    bool operator==(const vec2& oth) const {
        return dy*oth.dx == dx*oth.dy;
    }
};

double pp_dist(const point& a, const point& b) {
    return hypot(b.x - a.x, b.y - a.y);
}

double pv_dist(const point& a, const point& b, const point& c) {
    i64 cp = (b.x - a.x)*(c.y - a.y) - (c.x - a.x)*(b.y - a.y);
    return abs(cp)/pp_dist(a, b);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n; cin >> n;
    vector<point> pt(n);
    for (auto& [x, y] : pt) cin >> x >> y;
    sort(pt.begin(), pt.end());

    vector<vec2> v;
    for (int i =   0; i < n; ++i)
    for (int j = i+1; j < n; ++j) {
        v.emplace_back(i, j, pt[i], pt[j], true);
        point a { -pt[i].y, pt[i].x };
        point b { -pt[j].y, pt[j].x };
        if (!(a < b)) swap(a, b);
        v.emplace_back(i, j, a, b, false);
    }
    sort(v.begin(), v.end());

    vector<int> pos(n); iota(pos.begin(), pos.end(), 0);

    double ans = 0.;

    for (const auto& [dx, dy, i, j, prll] : v) {
        if (prll) {
            swap(pos[i], pos[j]);
            swap(pt[pos[i]], pt[pos[j]]);

            int pi = pos[i], pj = pos[j];
            if (pi > pj) swap(pi, pj);
            if (pi > 0) {
                ans = max(ans, pv_dist(pt[pi], pt[pj], pt[pi-1]));
            }
            if (pj < n-1) {
                ans = max(ans, pv_dist(pt[pi], pt[pj], pt[pj+1]));
            }
        }
        else if (abs(pos[i] - pos[j]) == 1) {
            ans = max(ans, pp_dist(pt[pos[i]], pt[pos[j]]));
        }
    }

    cout << setprecision(9) << .5*ans;
    return 0;
}
