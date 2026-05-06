/*
 * UCPC 2016 C. 분단의 슬픔
 * BOJ 13161
 *
 * max-flow min-cut duality, Dinic's
 * Date: 2022.1.28
 */

#include<bits/stdc++.h>
using namespace std;
constexpr int INF = INT32_MAX;

array<array<int, 512>, 512> cap;
array<vector<int>, 512> adj;
array<int, 512> party, level, adj_len, hist;
int S, T;

bool bfs() {
    queue<int> q; q.push(S);
    for (int u = 1; u <= T; ++u)
        level[u] = -1;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int& v : adj[u]) {
            if (cap[u][v] > 0 && level[v] < 0) {
                level[v] = level[u]+1;
                q.push(v);
            }
        }
    }
    return level[T] != -1;
}

int dfs(int u, int f) {
    if (u == T) return f;
    for (int& i = hist[u]; i < adj_len[u]; ++i) {
        int v = adj[u][i];
        if (cap[u][v] > 0 && level[v] == level[u]+1) {
            int r = dfs(v, min(f, cap[u][v]));
            if (r > 0) {
                cap[u][v] -= r;
                cap[v][u] += r;
                return r;
            }
        }
    }
    return 0;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int N; cin >> N;
    S = 0, T = N+1;
    for (int u = 1; u <= N; ++u) {
        cin >> party[u];
        if (party[u] == 1) {
            cap[S][u] = INF;
            adj[S].emplace_back(u);
            adj[u].emplace_back(S);
        }
        if (party[u] == 2) {
            cap[u][T] = INF;
            adj[u].emplace_back(T);
            adj[T].emplace_back(u);
        }
    }
    for (int u = 1; u <= N; ++u) {
    for (int v = 1; v <= N; ++v) {
        cin >> cap[u][v];
        if (party[u] == 2 || party[v] == 1)
            cap[u][v] = 0;
        if (u != v)
            adj[u].emplace_back(v);
    }
    }
    for (int u = S; u <= T; ++u)
        adj_len[u] = adj[u].size();

    int F = 0;
    level[S] = 0;
    while (bfs()) {
        for (int u = S; u <= T; ++u) hist[u] = 0;
        int f;
        while ((f = dfs(S, INF)) > 0) F += f;
    }

    cout << F << '\n';
    for (int u = 1; u <= N; ++u) if (level[u] != -1) cout << u << ' ';
    cout << '\n';
    for (int u = 1; u <= N; ++u) if (level[u] == -1) cout << u << ' ';
    cout << '\n';
    return 0;
}
