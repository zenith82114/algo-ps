/*
 * USA Computing Olympiad, USACO March 2005 Contest, Gold 1. Ombrophobic Bovines
 * BOJ 1745
 * JUNGOL 1493
 *
 * Floyd-Warshall, maximum flow, binary search
 * Date: 2024.7.16
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;
constexpr int inf32 = INT32_MAX/2;
constexpr i64 inf64 = INT64_MAX/2;

array<array<int, 404>, 404> cap_sav, cap;
array<array<i64, 404>, 404> dst, wei;
array<vector<int>, 404> adj;
array<int, 404> level, hist;
int s, t, asum;

bool bfs(i64 w) {
    for (int x = s; x <= t; ++x) level[x] = -1;
    level[s] = 0;
    queue<int> q; q.push(s);
    while (!q.empty()) {
        int x = q.front(); q.pop();
        for (int y : adj[x]) {
            if (cap[x][y] > 0 && wei[x][y] <= w && level[y] == -1) {
                level[y] = level[x] + 1;
                q.push(y);
            }
        }
    }
    return level[t] != -1;
}

int dfs(int x, int f, i64 w) {
    if (x == t) return f;
    for (int& i = hist[x]; i < (int)adj[x].size(); ++i) {
        int y = adj[x][i];
        if (cap[x][y] > 0 && wei[x][y] <= w && level[y] == level[x] + 1) {
            int r = dfs(y, min(f, cap[x][y]), w);
            if (r > 0) {
                cap[x][y] -= r;
                cap[y][x] += r;
                return r;
            }
        }
    }
    return 0;
}

bool decide(i64 w) {
    for (int x = s; x <= t; ++x)
    for (int y = s; y <= t; ++y) cap[x][y] = cap_sav[x][y];
    int F = 0;
    while (bfs(w)) {
        for (int x = s; x <= t; ++x) hist[x] = 0;
        int f;
        while ((f = dfs(s, inf32, w)) > 0) F += f;
    }
    return F == asum;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    auto add_edge = [] (int x, int y, int c, i64 w) {
        adj[x].push_back(y);
        cap_sav[x][y] = c;
        wei[x][y] = w;
        adj[y].push_back(x);
        wei[y][x] = w;
    };

    for (auto& row : cap_sav) row.fill(0);
    for (auto& row : dst) row.fill(inf64);

    int n, m; cin >> n >> m;
    s = 0; t = 2*n + 1;

    asum = 0;
    for (int i = 1; i <= n; ++i) {
        int a, b; cin >> a >> b;
        asum += a;
        add_edge(s, i, a, 0);
        add_edge(i + n, t, b, 0);
    }

    for (int i = 1; i <= n; ++i) dst[i][i] = 0;
    while (m--) {
        int i, j, d; cin >> i >> j >> d;
        dst[i][j] = min<i64>(dst[i][j], d);
        dst[j][i] = min<i64>(dst[j][i], d);
    }

    for (int k = 1; k <= n; ++k)
    for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= n; ++j) {
        dst[i][j] = min(dst[i][j], dst[i][k] + dst[k][j]);
    }

    for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= n; ++j) if (dst[i][j] < inf64) {
        add_edge(i, j + n, inf32, dst[i][j]);
    }

    i64 lo = -1, hi = inf64;
    while (lo + 1 < hi) {
        i64 mid = (lo + hi)/2;
        (decide(mid)? hi : lo) = mid;
    }
    cout << (hi < inf64? hi : -1);
    return 0;
}
