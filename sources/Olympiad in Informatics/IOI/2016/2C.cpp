/*
 * International Olympiad in Informatics, IOI 2016, Day 2 C. Aliens
 * JUNGOL 3681
 *
 * Aliens trick, convex hull trick
 * Date: 2026.5.1
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = long long;

struct line {
    i64 y0, m;
    line(i64 y0, i64 m): y0(y0), m(m) {};
};
inline i64 cx(const line& a, const line& b) {
    return (b.y0 - a.y0)/(a.m - b.m);
}

vector<int> x, y;

inline i64 sqr(int a) { return (i64)a*a; }

pair<i64, int> solve(i64 lmd) {
    i64 dp = 0;
    int opt = 0;
    deque<line> hl; hl.emplace_back(2*sqr(x[0] - 1), -4*(x[0] - 1));
    deque<int> hl_opt; hl_opt.push_back(0);
    int sz = 1;

    for (size_t i = 0; i + 1 < x.size(); ++i) {
        while (sz > 1 && cx(hl[0], hl[1]) < y[i]) {
            sz--; hl.pop_front(); hl_opt.pop_front();
        }
        dp = 2*sqr(y[i]) + lmd + hl[0].y0 + hl[0].m*y[i];
        opt = hl_opt[0] + 1;

        line f (dp + 2*sqr(x[i + 1] - 1) - 2*sqr(max(0, y[i] - x[i + 1] + 1)), -4*(x[i + 1] - 1));

        while (sz > 1 && cx(hl[sz - 2], hl[sz - 1]) >= cx(hl[sz - 1], f)) {
            sz--; hl.pop_back(); hl_opt.pop_back();
        }
        sz++; hl.push_back(f);
        hl_opt.push_back(opt);
    }

    while (sz > 1 && cx(hl[0], hl[1]) < y.back()) {
        sz--; hl.pop_front(); hl_opt.pop_front();
    }
    dp = 2*sqr(y.back()) + lmd + hl[0].y0 + hl[0].m*y.back();
    opt = hl_opt[0] + 1;

    return { dp, opt };
}

long long take_photos(int n, int m, int k, std::vector<int> r, std::vector<int> c) {
    for (int i = 0; i < n; ++i) if (r[i] > c[i]) swap(r[i], c[i]);

    vector<int> ord(n);
    iota(ord.begin(), ord.end(), 0);
    sort(ord.begin(), ord.end(), [&] (int i, int j) {
        return make_pair(r[i], -c[i]) < make_pair(r[j], -c[j]);
    });

    y.push_back(0);
    for (int i : ord) {
        if (c[i] + 1 > y.back()) x.push_back(r[i] + 1), y.push_back(c[i] + 1);
    }
    y.erase(y.begin());
    k = min(k, (int)x.size());

    i64 lo = 0, hi = 1e12;
    while (lo + 1 < hi) {
        i64 mid = (lo + hi)/2;
        (solve(2*mid + 1).second > k ? lo : hi) = mid;
    }
    return solve(2*hi).first/2 - hi*k;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m, k; cin >> n >> m >> k;
    vector<int> r(n), c(n);
    for (int i = 0; i < n; ++i) cin >> r[i] >> c[i];
    cout << take_photos(n, m, k, r, c);
    return 0;
}
