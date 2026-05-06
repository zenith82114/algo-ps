/*
 * ICPC, Regionals, Asia Pacific, Indonesia,
 * The 2018 ICPC Asia Jakarta Regional Contest K. Boomerangs
 * BOJ 16583 - DFS, greedy
 * Date: 2023.1.13
 */

#include<bits/stdc++.h>
using namespace std;

vector<vector<pair<int, int>>> adj;
vector<bool> vrtx_vis, edge_vis;
vector<tuple<int, int, int>> ans;

bool dfs(int pu, int u) {
    if (vrtx_vis[u]) return true;
    vrtx_vis[u] = true;

    vector<int> T;
    for (const auto& [v, i] : adj[u]) if (!edge_vis[i]) {
        edge_vis[i] = true;
        edge_vis[i^1] = true;
        if (dfs(u, v)) T.emplace_back(v);
    }
    int sT = T.size();
    for (int i = 0; i+1 < sT; i += 2)
        ans.emplace_back(T[i], u, T[i+1]);
    if (sT & 1) {
        if (pu) ans.emplace_back(pu, u, T.back());
        return false;
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int N, M; cin >> N >> M;
    adj.resize(N+1);
    for (int i = 0; i < M; ++i) {
        int u, v; cin >> u >> v;
        adj[u].emplace_back(v, i<<1);
        adj[v].emplace_back(u, i<<1|1);
    }
    vrtx_vis.resize(N+1, false);
    edge_vis.resize(M<<1, false);

    for (int u = 1; u <= N; ++u) if (!vrtx_vis[u])
        dfs(0, u);

    cout << ans.size() << '\n';
    for (const auto& [u, v, w] : ans)
        cout << u << ' ' << v << ' ' << w << '\n';
    return 0;
}
