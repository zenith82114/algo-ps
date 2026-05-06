/*
 * Petrozavodsk Programming Camp, Winter 2018, Day 8: Saratov SU Contest L. Increasing Costs
 * Open Cup 2017/2018 Stage 13: Grand Prix of Saratov L. Increasing Costs
 * BOJ 19335 - Dijkstra's, dominator tree of a DAG
 * Date: 2023.4.26
 */

#include<bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int N, M; cin >> N >> M;

    using ii = pair<int, int>;
    vector<vector<ii> > adj(N+1);

    struct edge { int u, v, c; };
    vector<edge> edges(M);
    for (auto& [u, v, c] : edges) {
        cin >> u >> v >> c;
        adj[u].emplace_back(v, c);
        adj[v].emplace_back(u, c);
    }

    using i64 = int64_t;
    priority_queue<pair<i64, int> > pq; pq.emplace(0, 1);
    vector<i64> dist(N+1, INT64_MAX); dist[1] = 0;

    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop(); d = -d;
        if (d > dist[u]) continue;
        for (const auto& [v, c] : adj[u]) {
            if (dist[v] > d + c) {
                dist[v] = d + c;
                pq.emplace(-dist[v], v);
            }
        }
    }

    vector<vector<int> > succ(N+1), pred(N+1);
    for (auto& [u, v, c] : edges) {
        if (dist[u] > dist[v]) swap(u, v);
        if (dist[u] + c == dist[v]) {
            succ[u].emplace_back(v);
            pred[v].emplace_back(u);
        }
    }

    const int lgN = [] (int n) {
        int k = 0; for (int m = 1; 2*m <= n; m <<= 1, ++k); return k; } (N);
    vector<vector<int> > tbl(lgN+1, vector<int>(N+1));
    vector<int> dep(N+1);

    auto lca = [&] (int x, int y) {
        if (dep[x] < dep[y]) swap(x, y);
        for (int d = dep[x] - dep[y], i = 0; d; d >>= 1, ++i)
            if (d&1) x = tbl[i][x];
        if (x != y) {
            for (int i = lgN; ~i; --i) if (tbl[i][x] != tbl[i][y])
                x = tbl[i][x], y = tbl[i][y];
            return tbl[0][x];
        }
        return x;
    };

    vector<int> topol;
    queue<int> q; for (int v : succ[1]) q.emplace(v);
    vector<int> in_deg(N+1);
    for (int v = 2; v <= N; ++v) in_deg[v] = pred[v].size();

    while (!q.empty()) {
        int u = q.front(); q.pop();
        topol.emplace_back(u);

        int pu = pred[u].front();
        for (int v : pred[u]) pu = lca(pu, v);
        tbl[0][u] = pu;
        for (int i = 0; i < lgN; ++i) tbl[i+1][u] = tbl[i][tbl[i][u]];
        dep[u] = dep[pu] + 1;

        for (int v : succ[u]) if (--in_deg[v] == 0) q.emplace(v);
    }

    vector<int> sz(N+1, 1);
    reverse(topol.begin(), topol.end());
    for (int u : topol) sz[tbl[0][u]] += sz[u];

    for (const auto& [u, v, c] : edges)
        cout << (u == tbl[0][v] && pred[v].size() == 1UL? sz[v] : 0) << '\n';

    return 0;
}
