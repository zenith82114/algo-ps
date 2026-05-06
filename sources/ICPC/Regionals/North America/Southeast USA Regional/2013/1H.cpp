/*
 * ICPC, Regionals, North America,
 * 2013 Southeast USA Regional Programming Contest, Division 1 H. Triangles
 * BOJ 9484 - Bulldozer trick
 * Date: 2024.3.3
 */

#include<bits/stdc++.h>
using namespace std;

struct point {
    int x, y;
    bool operator<(const point& oth) const {
        return tie(x, y) < tie(oth.x, oth.y);
    }
};

struct vec2 {
    int i, j, dx, dy;
    vec2(int i, int j, const point& a, const point& b)
    : i{i}, j{j}, dx{b.x - a.x}, dy{b.y - a.y} {}
    bool operator<(const vec2& oth) const {
        int cx = dy*oth.dx - dx*oth.dy;
        return cx? cx < 0 : tie(i, j) < tie(oth.i, oth.j);
    }
    bool operator==(const vec2& oth) const {
        return dy*oth.dx == dx*oth.dy;
    }
};

int cross_prod(const point& a, const point& b, const point& c) {
    int x1 = b.x - a.x, x2 = c.x - a.x;
    int y1 = b.y - a.y, y2 = c.y - a.y;
    return abs(x1*y2 - y1*x2);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    for (cin >> n; n; cin >> n) {
        vector<point> pt(n);
        for (auto& [x, y] : pt) cin >> x >> y;
        sort(pt.begin(), pt.end());

        vector<vec2> v;
        for (int i =   0; i < n; ++i)
        for (int j = i+1; j < n; ++j) {
            v.emplace_back(i, j, pt[i], pt[j]);
        }
        sort(v.begin(), v.end());

        vector<int> pos(n); iota(pos.begin(), pos.end(), 0);
        int ans_min = INT32_MAX, ans_max = 0;

        for (const auto& [i, j, dx, dy] : v) {
            swap(pos[i], pos[j]);
            swap(pt[pos[i]], pt[pos[j]]);

            int pi = pos[i], pj = pos[j];
            if (pi > pj) swap(pi, pj);
            int cp;
            if (pi > 0) {
                cp = cross_prod(pt[pi], pt[pj], pt[pi-1]);
                ans_min = min(ans_min, cp);
                cp = cross_prod(pt[pi], pt[pj], pt[0]);
                ans_max = max(ans_max, cp);
            }
            if (pj < n-1) {
                cp = cross_prod(pt[pi], pt[pj], pt[pj+1]);
                ans_min = min(ans_min, cp);
                cp = cross_prod(pt[pi], pt[pj], pt[n-1]);
                ans_max = max(ans_max, cp);
            }
        }
        cout << (ans_min>>1)<<'.'<<(ans_min&1? 5 : 0) << ' ';
        cout << (ans_max>>1)<<'.'<<(ans_max&1? 5 : 0) << '\n';
    }

    return 0;
}
