/*
 * Baltic Olympiad in Informatics, BOI 2009 Day 2 A. Rectangle
 * BOJ 2415
 * JUNGOL 2451
 *
 * geometry, two pointers
 * Date: 2025.9.28
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;

struct vec2 {
    int x, y;
    vec2(int x, int y): x(x), y(y) {}
    i64 cross(const vec2& other) const {
        return (i64)x * other.y - (i64)y * other.x;
    }
    i64 dot(const vec2& other) const {
        return (i64)x * other.x + (i64)y * other.y;
    }
    i64 norm_sqr() const {
        return (i64)x * x + (i64)y * y;
    }
    bool operator==(const vec2& other) const {
        return x == other.x && y == other.y;
    }
};

struct elem {
    vec2 base, dir;
    elem(int bx, int by, int dx, int dy): base(bx, by), dir(dx, dy) {}
    bool operator<(const elem& other) const {
        auto p = make_pair(base.x, base.y);
        auto other_p = make_pair(other.base.x, other.base.y);
        if (p != other_p) return p < other_p;

        i64 ns = dir.norm_sqr(), other_ns = other.dir.norm_sqr();
        if (ns != other_ns) return ns < other_ns;

        return dir.cross(other.dir) > 0;
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n; cin >> n;
    vector<vec2> a;
    for (int i = 0; i < n; ++i) {
        int x, y; cin >> x >> y;
        a.emplace_back(x, y);
    }

    vector<elem> v;
    for (int i = 0; i < n; ++i)
    for (int j = i + 1; j < n; ++j) {
        const auto& [xi, yi] = a[i];
        const auto& [xj, yj] = a[j];
        v.emplace_back(xi + xj, yi + yj, xi - xj, yi - yj);
        auto& d = v.back().dir;
        if (d.y < 0 || (d.y == 0 && d.x < 0)) d.x = -d.x, d.y = -d.y;
    }
    const int m = v.size();
    sort(begin(v), end(v));

    i64 ans = 0;
    for (int s = 0, e = 0; s < m; s = e) {
        while (e < m &&
            v[s].base == v[e].base &&
            v[s].dir.norm_sqr() == v[e].dir.norm_sqr()
        ) ++e;

        for (int i = s, j = s; j < e; ++i) {
            while (j < e && v[i].dir.dot(v[j].dir) > 0) {
                ans = max(ans, v[i].dir.cross(v[j].dir) / 2);
                ++j;
            }
            if (j < e) ans = max(ans, v[i].dir.cross(v[j].dir) / 2);
        }
    }

    cout << ans;
    return 0;
}
