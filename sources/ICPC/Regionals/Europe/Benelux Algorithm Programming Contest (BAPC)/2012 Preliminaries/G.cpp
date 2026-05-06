/*
 * ICPC, Regionals, Europe,
 * Benelux Algorithm Programming Contest, BAPC 2012 Preliminaries G. Gunslinger
 * BOJ 5377 - convex hull
 * Date: 2023.3.20
 */

#include<bits/stdc++.h>
using namespace std;

struct vec2 {
    int x, y;
    bool operator<(const vec2& v) const {
        return y != v.y ? y < v.y : x < v.x;
    }
    bool operator==(const vec2& v) const {
        return x == v.x && y == v.y;
    }
    bool operator!=(const vec2& v) const {
        return x != v.x || y != v.y;
    }
    vec2 operator-(const vec2& v) const {
        return { x - v.x, y - v.y };
    }
    friend istream& operator>>(istream& is, vec2& v) {
        is >> v.x >> v.y; return is;
    }
};
int64_t cross(const vec2& v, const vec2& w) {
    return v.x*w.y - v.y*w.x;
}
int64_t dot(const vec2& v, const vec2& w) {
    return v.x*w.x + v.y*w.y;
}
int ccw(const vec2& o, const vec2& p, const vec2& q) {
    auto k = cross(p - o, q - o);
    return k < 0? -1 : (k > 0);
}
inline double dist(const vec2& p, const vec2& q) {
    return hypot(p.x - q.x, p.y - q.y);
}

vector<vec2> convex_hull(vector<vec2>& G) {
    swap(G.front(), *min_element(G.begin(), G.end()));
    sort(++G.begin(), G.end(), [orig = G.front()] (const vec2& p, const vec2& q) {
        int k = ccw(orig, p, q);
        return k? k > 0 : dot(q - p, orig - p) < 0;
    });
    vector<vec2> H;
    int sz = 0;
    for (auto& g : G) {
        while (sz > 1 && ccw(H[sz-2], H[sz-1], g) <= 0)
            H.pop_back(), --sz;
        H.push_back(g), ++sz;
    }
    return H;
}

bool inside(const vector<vec2>& H, const vec2& p) {
    const int sz = H.size();
    for (int i = 0; i < sz; ++i)
        if (ccw(H[i], H[(i+1)%sz], p) <= 0)
            return false;
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cout << fixed << setprecision(3);

    int tc; cin >> tc;
    while (tc--) {
        vec2 s, t; cin >> s >> t;
        int N; cin >> N;
        vector<vec2> G(N);
        for (auto& p : G) cin >> p;
        auto H = convex_hull(G);

        if (inside(H, s) || inside(H, t))
            cout << "IMPOSSIBLE\n";
        else {
            H.emplace_back(s);
            H.emplace_back(t);
            H = convex_hull(H);
            const int sz = H.size();
            const auto nxt = [sz] (int i) { return i+1 == sz? 0 : i+1; };

            int i = 0, j = 0;
            while (i < sz &&
                (H[nxt(i)] == s || ccw(H[i], H[nxt(i)], s) > 0)) ++i;
            while (j < sz &&
                (H[nxt(j)] == t || ccw(H[j], H[nxt(j)], t) > 0)) ++j;

            if (i == sz || j == sz || i == j)
                cout << dist(s, t) << '\n';
            else {
                double d1 = dist(s, H[nxt(i)]);
                for (int k = nxt(i); k != j; k = nxt(k)) d1 += dist(H[k], H[nxt(k)]);
                d1 += dist(H[j], t);
                double d2 = dist(t, H[nxt(j)]);
                for (int k = nxt(j); k != i; k = nxt(k)) d2 += dist(H[k], H[nxt(k)]);
                d2 += dist(H[i], s);
                cout << min(d1, d2) << '\n';
            }
        }
    }

    return 0;
}
