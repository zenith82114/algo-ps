/*
 * Petrozavodsk Programming Camp, Winter 2017, Day 1: Jagiellonian U Contest B. Dissertation
 * BOJ 19348 - greedy, DP
 * Date: 2025.10.26
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;
constexpr int MAXN = 1e6 + 4, MAXM = 1e3 + 4;

int nxt[MAXN][26];
int dp[MAXM][MAXM];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int tc;
    for (cin >> tc; tc--;) {
        string s, t; cin >> s >> t;
        int n = s.size(), m = t.size();
        s.insert(begin(s), 0); t.insert(begin(t), 0);

        fill_n(nxt[n + 1], 2 * 26, n + 1);
        for (int i = n; i > 0; --i) {
            memcpy(nxt[i], nxt[i + 1], sizeof nxt[0]);
            nxt[i][s[i] - 'a'] = i;
        }

        for (int j = 0; j <= m; ++j) {
            dp[j][0] = 0;
            for (int k = 1; k <= j; ++k) {
                dp[j][k] = min(dp[j - 1][k], nxt[dp[j - 1][k - 1] + 1][t[j] - 'a']);
            }
            dp[j][j + 1] = n + 1;
        }

        for (int k = m; k >= 0; --k) if (dp[m][k] <= n) {
            cout << k << '\n'; break;
        }
    }

    return 0;
}
