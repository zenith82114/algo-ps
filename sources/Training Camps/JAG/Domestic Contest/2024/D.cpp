/*
 * ICPC Japanese Alumni Group, JAG Domestic Contest 2024 D. 過去問の共有
 * BOJ 32092 - bitmask DP, linearity of expectation
 * Date: 2024.9.27
 */

#include<bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    constexpr int MOD = 998244353;

    int n, m, k; cin >> n >> m >> k;
    for (; n | m | k; cin >> n >> m >> k) {
        const int m_inv = [] (int a) {
            int b = 1;
            for (int e = MOD - 2; e; e >>= 1) {
                if (e&1) b = 1ll * b * a % MOD;
                a = 1ll * a * a % MOD;
            }
            return b;
        } (m);
        vector<pair<int, int> > edg(m);
        for (auto& [x, y] : edg) cin >> x >> y, --x, --y;

        vector<int> dp(1<<n);
        for (int x = 0; x < n; ++x) dp[1<<x] = 1;

        for (int t = 0; t < k; ++t) {
            vector<int> dp_nxt(1<<n);
            for (int s = 0; s < (1<<n); ++s) {
                for (auto [x, y] : edg) {
                    int ns = s;
                    if ((s & (1<<x)) || (s & (1<<y))) ns |= (1<<x) | (1<<y);
                    dp_nxt[ns] += (1ll * dp[s] * m_inv) % MOD;
                    dp_nxt[ns] %= MOD;
                }
            }
            dp.swap(dp_nxt);
        }

        int ans = 0;
        for (int s = 1; s < (1<<n); s += 2) ans = (ans + dp[s]) % MOD;
        cout << ans << '\n';
    }

    return 0;
}
