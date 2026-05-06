/*
 * ICPC, Regionals, Europe, Southwestern Europe Regional Contest,
 * SWERC 2020-2021 F. Mentors
 * BOJ 21213 - connected component DP
 * Date: 2025.8.8
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;

i64 dp[2048][2048] {};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int r, n, m; cin >> r >> n >> m;
    dp[0][0] = 1;
    for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= i; ++j) {
        dp[i][j] = dp[i - 1][j - 1];
        if (i != r) {
            dp[i][j] += j * dp[i - 1][j];
            dp[i][j] %= m;
            dp[i][j] += (j + 1) * j / 2 * dp[i - 1][j + 1];
            dp[i][j] %= m;
        }
    }
    cout << dp[n][1];
    return 0;
}
