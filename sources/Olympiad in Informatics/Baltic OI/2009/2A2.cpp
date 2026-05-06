/*
 * Baltic Olympiad in Informatics, BOI 2009 Day 2 A. Rectangle
 * BOJ 2415
 * JUNGOL 2451
 *
 * geometry, two pointers
 * Date: 2025.9.30
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;

struct vec2 {
    int x, y;
    vec2(int x, int y): x(x), y(y) {}
    bool operator==(const vec2& other) const {
        return x == other.x && y == other.y;
    }
    bool operator!=(const vec2& other) const {
        return x != other.x || y != other.y;
    }
    bool operator<(const vec2& other) const {
        return make_pair(x, y) < make_pair(other.x, other.y);
    }
    vec2 operator-(const vec2& other) const {
        return vec2(x - other.x, y - other.y);
    }
    i64 cross(const vec2& other) const {
        return (i64)x * other.y - (i64)y * other.x;
    }
    i64 dot(const vec2& other) const {
        return (i64)x * other.x + (i64)y * other.y;
    }
};

struct elem {
    vec2 p, v;
    elem(const vec2& p, const vec2& v): p(p), v(v) {}
    bool operator<(const elem& other) const {
        if (v != other.v) return v < other.v;
        return p.dot(v) < other.p.dot(other.v);
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

    vector<elem> b;
    for (const auto& i : a)
    for (const auto& j : a) if (i != j) {
        if (i.x < j.x && i.y <= j.y) b.emplace_back(i, j - i);
    }
    sort(begin(b), end(b));

    i64 ans = 0;
    for (auto i = begin(b), j = begin(b); i < end(b); i = j) {
        auto ymin = i, ymax = i;
        for (; j < end(b) && i->v == j->v && i->p.dot(i->v) == j->p.dot(j->v); ++j) {
            if (j->p.y < ymin->p.y) ymin = j;
            if (j->p.y > ymax->p.y) ymax = j;
        }
        ans = max(ans, i->v.cross(ymax->p - ymin->p));
    }

    cout << ans;
    return 0;
}
