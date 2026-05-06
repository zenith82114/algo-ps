/*
 * Central Europe Olympiad in Informatics, CEOI 2009, Day 1 B. harbingers
 * BOJ 3319
 * JUNGOL 4982
 *
 * CHT, stack rollback
 * Date: 2024.3.10
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;
using i128 = __int128_t;
constexpr int MAXN = 1e5 + 4;

struct Line {
    i64 y0, m;
    Line(): y0(0), m(0) {}
    Line(i64 y0, i64 m): y0(y0), m(m) {}
    i64 eval(int x) const { return y0 + m*x; };
};

array<vector<pair<int, int> >, MAXN> adj;
array<int, MAXN> S, V;
array<Line, MAXN> stk;
array<i64, MAXN> dp;

bool chk1(const Line& a, const Line& b, i64 x) {
    return x*(a.m - b.m) <= (b.y0 - a.y0);
}

bool chk2(const Line& a, const Line& b, const Line& c) {
    return (i128)(c.y0 - a.y0)*(a.m - b.m) <= (i128)(b.y0 - a.y0)*(a.m - c.m);
}

void dfs(int px, int x, int dep, int sz) {
    int lo = 0, hi = sz-1;
    while (lo < hi) {
        int mid = (lo+hi)>>1;
        if (chk1(stk[mid], stk[mid+1], V[x])) hi = mid;
        else lo = mid+1;
    }
    dp[x] = S[x] + (i64)dep*V[x] + stk[lo].eval(V[x]);

    Line ln(dp[x], -dep);

    if (sz == 1) {
        sz = (stk[0].m == ln.m)? 0 : 1;
    } else {
        lo = 1, hi = sz;
        while (lo < hi) {
            int mid = (lo+hi)>>1;
            if (chk2(stk[mid-1], stk[mid], ln)) hi = mid;
            else lo = mid+1;
        }
        sz = lo;
    }

    Line ln_old = stk[sz];
    stk[sz++] = ln;
    for (const auto& [y, w] : adj[x]) if (y != px) {
        dfs(x, y, dep+w, sz);
    }
    stk[--sz] = ln_old;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n; cin >> n;
    for (int i = 1; i < n; ++i) {
        int x, y, w; cin >> x >> y >> w;
        adj[x].emplace_back(y, w);
        adj[y].emplace_back(x, w);
    }
    for (int x = 2; x <= n; ++x) cin >> S[x] >> V[x];

    for (int i = 0; i <= n; ++i) stk[i] = Line(); // avoid unwritten read
    dp[1] = 0;
    for (const auto& [y, w] : adj[1]) dfs(1, y, w, 1);
    for (int x = 2; x <= n; ++x) cout << dp[x] << ' ';
    return 0;
}
