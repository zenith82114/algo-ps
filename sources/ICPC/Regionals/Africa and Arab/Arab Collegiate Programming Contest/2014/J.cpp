/*
 * ICPC, Regionals, Africa and Arab,
 * 2014 Arab Collegiate Programming Contest J. Mario and Evil Toad
 * BOJ 11808 - tree DP
 * Date: 2024.12.19
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;

int n, k;
vector<pair<int, int> > g[1001];
vector<i64> dp[1001];

void dfs(int x) {
    dp[x].clear();
    dp[x].emplace_back(0);
    if (x != 1) dp[x].emplace_back(0);
    for (const auto& [y, w] : g[x]) {
        dfs(y);
        int sx = dp[x].size(), sy = dp[y].size();
        dp[x].resize(sx + sy - 1);

        for (int i = sx + sy - 2; i >= 0; --i)
        for (int j = max(0, i - sx + 1); j <= min(i, sy - 1); ++j) {
            dp[x][i] = max(dp[x][i],
                dp[x][i - j] + dp[y][j] + (i64)2 * w * min(j, k - j + 1));
        }

        dp[x].resize(min(sx + sy - 1, k + 1));
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int TC; cin >> TC;
    for (int tc = 1; tc <= TC; ++tc) {
        cin >> n >> k;
        for (int x = 1; x <= n; ++x) g[x].clear();
        for (int x = 2; x <= n; ++x) {
            int px, w; cin >> px >> w;
            g[px].emplace_back(x, w);
        }
        dfs(1);
        cout << "Case " << tc << ": " << dp[1][k] << '\n';
    }

    return 0;
}
