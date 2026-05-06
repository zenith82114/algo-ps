/*
 * 한국정보올림피아드, KOI 2021 2차대회, 고등부 1. 헬기 착륙장
 * BOJ 22348
 * JUNGOL 4806
 *
 * DP
 * Date: 2025.9.28
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;
constexpr int MOD = 1e9 + 7;

int dp[500][50001] {};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    dp[0][0] = 1;
    for (int i = 1; i < 500; ++i)
    for (int j = 0; j <= 50000; ++j) {
        dp[i][j] = ((i <= j? dp[i - 1][j - i] : 0) + dp[i - 1][j]) % MOD;
    }
    for (int i = 1; i < 500; ++i)
    for (int j = 1; j <= 50000; ++j) {
        dp[i][j] = (dp[i][j - 1] + dp[i][j]) % MOD;
    }

    int tc; cin >> tc;
    while (tc--) {
        int a, b; cin >> a >> b;
        int ans = 0;
        for (int i = 1; i*(i + 1)/2 <= a + b; ++i) {
            ans = (ans + dp[i][a]) % MOD;
            int c = max(0, i*(i + 1)/2 - b);
            if (c) ans = (ans + MOD - dp[i][c - 1]) % MOD;
        }
        cout << ans << '\n';
    }

    return 0;
}
