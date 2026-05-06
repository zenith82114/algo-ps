/*
 * 한국정보올림피아드, KOI 2020 1차대회, 고등부 3. 조명등
 * BOJ 19943
 * JUNGOL 4522
 *
 * convex hull trick
 * Date: 2025.11.20
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;

struct line {
    i64 y0, m;
    line(i64 y0, i64 m): y0(y0), m(m) {};
};
inline i64 cx(const line& a, const line& b) {
    return (b.y0 - a.y0)/(a.m - b.m);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cout << setfill('0');

    int tc; cin >> tc;
    while (tc--) {
        int n; cin >> n;
        vector<pair<int, int> > u;
        for (int i = 0; i < n; ++i) {
            int x, h; cin >> x >> h;
            u.emplace_back(x - h, - x - h);
        }
        sort(begin(u), end(u));

        vector<pair<i64, i64> > v;
        v.emplace_back(0, 0);
        for (auto [l, r] : u) {
            if (v.back().second < -r) v.emplace_back(l, -r);
        }

        i64 dp = 0;
        deque<line> hl;
        int sz = 0;

        for (size_t i = 1; i < v.size(); ++i) {
            auto [l, r] = v[i];
            line f(dp + l*l, -2*l);
            while (sz > 1 && cx(hl[sz-2], hl[sz-1]) >= cx(hl[sz-1], f)) {
                sz--; hl.pop_back();
            }
            sz++; hl.emplace_back(f);
            while (sz > 1 && cx(hl[0], hl[1]) < r) {
                sz--; hl.pop_front();
            }
            dp = r*r + hl[0].y0 + hl[0].m * r;
        }
        cout << (dp>>2) << '.' << setw(2) << (25*(dp&3)) << '\n';
    }

    return 0;
}
