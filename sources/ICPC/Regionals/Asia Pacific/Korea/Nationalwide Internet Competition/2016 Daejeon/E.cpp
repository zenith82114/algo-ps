/*
 * ICPC, Regionals, Asia Pacific, Korea,
 * Daejeon Nationalwide Internet Competition 2016 E. Meteor Shower
 * BOJ 13329
 *
 * sweep line, BBST
 * Date: 2025.1.11
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;

struct vec2 {
    int x, y;
    vec2(): x(0), y(0) {}
    vec2(int x, int y): x(x), y(y) {}
    vec2 operator-(const vec2& v) const {
        return { x - v.x, y - v.y };
    }
    bool operator<(const vec2& v) const {
        return 1ll * x * v.y > 1ll * y * v.x;
    }
};
inline i64 cross(const vec2& v, const vec2& w) {
    return 1ll * v.x * w.y - 1ll * v.y * w.x;
}
inline i64 ccw(const vec2& o, const vec2& p, const vec2& q) {
    return cross(p - o, q - o);
}

array<vec2, 100005> s, t;

struct set_elem {
    int id;
    set_elem(int id): id(id) {}
    bool operator<(const set_elem& e) const {
        if (s[id] < s[e.id])
            return ccw(s[id], t[id], s[e.id]) < 0;
        else
            return ccw(s[e.id], t[e.id], s[id]) > 0;
    }
};

set<set_elem> z;
array<set<set_elem>::iterator, 100005> itr;
bitset<100005> chk;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n; cin >> n;
    vector<int> ev; ev.reserve(2 * n);

    for (int i = 1; i <= n; ++i) {
        s[i] = vec2(-1, 0);
        t[i] = vec2(+1, 0);
        int m; cin >> m;
        while (m--) {
            int x, y; cin >> x >> y; vec2 v(x, y);
            s[i] = min(s[i], v);
            t[i] = max(t[i], v);
        }
        ev.emplace_back(+i);
        ev.emplace_back(-i);
    }

    sort(ev.begin(), ev.end(), [] (int i, int j) {
        return (i > 0? s[i] : t[-i]) < (j > 0? s[j] : t[-j]);
    });
    for (int id : ev) {
        if (id > 0) itr[id] = z.emplace(id).first;
        else z.erase(itr[-id]);
        if (!z.empty()) chk.set(z.begin()->id);
    }
    cout << (n - (int)chk.count());
    return 0;
}
