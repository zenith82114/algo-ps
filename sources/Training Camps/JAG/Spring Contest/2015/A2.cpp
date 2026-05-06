/*
 * ICPC Japanese Alumni Group, JAG Spring Contest 2015 A. Balanced Paths
 * BOJ 11706 - DSU on trees
 * Date: 2026.1.3
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;
constexpr int MAXN = 1e5 + 4;

char label[MAXN];
vector<int> g[MAXN];
int sz[MAXN];
deque<int> dp[MAXN][2]; // [x][0 / 1]: up until / down from x (both inclusive)
i64 ans = 0;

int get_sz(int px, int x) {
    sz[x] = 1;
    for (int y : g[x]) if (y != px) sz[x] += get_sz(x, y);
    return sz[x];
}

void shift(deque<int>& dq, int delta) {
    if (delta == 1) dq.push_front(0);
    else if (!dq.empty()) dq.pop_front();
}

void dfs(int px, int x) {
    // reuse heavy child
    int yh = 0;
    for (int y : g[x]) if (y != px && sz[yh] < sz[y]) yh = y;
    if (yh) {
        dfs(x, yh);
        dp[x][0] = move(dp[yh][0]);
        dp[x][1] = move(dp[yh][1]);
    }
    shift(dp[x][0], label[x] == '(' ? +1 : -1);
    shift(dp[x][1], label[x] == ')' ? +1 : -1);

    // leaf
    if (dp[x][0].size() < 2u) dp[x][0].resize(2, 0);
    if (dp[x][1].size() < 2u) dp[x][1].resize(2, 0);

    // singleton path
    dp[x][label[x] == '(' ? 0 : 1][1]++;

    // paths in heavy subtree starting/ending at x
    // those in other (light) children are counted in the loop below
    if (!dp[x][0].empty()) ans += dp[x][0][0];
    if (!dp[x][1].empty()) ans += dp[x][1][0];

    for (int y : g[x]) if (y != px && y != yh) {
        dfs(x, y);

        for (size_t i = 0; i < min(dp[x][0].size(), dp[y][1].size()); ++i) {
            ans += (i64)dp[x][0][i] * dp[y][1][i];
        }
        for (size_t i = 0; i < min(dp[x][1].size(), dp[y][0].size()); ++i) {
            ans += (i64)dp[x][1][i] * dp[y][0][i];
        }

        shift(dp[y][0], label[x] == '(' ? +1 : -1);
        shift(dp[y][1], label[x] == ')' ? +1 : -1);

        while (dp[x][0].size() < dp[y][0].size()) dp[x][0].push_back(0);
        while (dp[x][1].size() < dp[y][1].size()) dp[x][1].push_back(0);
        for (size_t i = 0; i < dp[y][0].size(); ++i) dp[x][0][i] += dp[y][0][i];
        for (size_t i = 0; i < dp[y][1].size(); ++i) dp[x][1][i] += dp[y][1][i];

        dp[y][0].clear();
        dp[y][1].clear();
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n; cin >> n;
    for (int x = 1; x <= n; ++x) cin >> label[x];
    for (int i = 1; i < n; ++i) {
        int x, y; cin >> x >> y;
        g[x].push_back(y);
        g[y].push_back(x);
    }

    get_sz(0, 1);
    dfs(0, 1);
    cout << ans;
    return 0;
}
