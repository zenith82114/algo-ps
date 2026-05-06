/*
 * KTH Challenge, KTH Challenge 2017 E. Global Warming
 * Q22038 - bitmask DP
 * Date: 2026.2.3
*/

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;

int w[256][256];
int dsu[256];
int pc[1<<22];
int dp[1<<22];

int _find(int x) {
    if (dsu[x] == x) return x;
    return dsu[x] = _find(dsu[x]);
}

inline void upd(int& a, int b) { a = min(a, b); }

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m; cin >> n >> m;
    memset(w, -1, sizeof w);
    iota(dsu, dsu + n + 1, 0);
    while (m--) {
        int x, y, c; cin >> x >> y >> c;
        w[x][y] = w[y][x] = c;
        x = _find(x), y = _find(y);
        dsu[x] = y;
    }

    int ans = 0;
    for (int x0 = 1; x0 <= n; ++x0) if (_find(x0) == x0) {
        vector<int> v;
        for (int x = 1; x <= n; ++x) if (_find(x) == x0) v.push_back(x);
        const int m = v.size();
        if (m & 1) { cout << "impossible"; return 0; }

        pc[0] = 0;
        memset(dp, 0x3f, sizeof(int) * (1<<m));
        dp[0] = 0;

        for (int u = 0; u < 1<<m; ++u) if (~pc[u] & 1) {
            for (int i = 0; i < m; ++i) if (~u & (1<<i)) {
                pc[u | (1<<i)] = pc[u] + 1;
                for (int j = i + 1; j < m; ++j) if (~u & (1<<j)) {
                    upd(dp[u | (1<<i) | (1<<j)], dp[u] + w[v[i]][v[j]]);
                }
            }
        }

        ans += dp[(1<<m) - 1];
    }

    cout << ans;
    return 0;
}
