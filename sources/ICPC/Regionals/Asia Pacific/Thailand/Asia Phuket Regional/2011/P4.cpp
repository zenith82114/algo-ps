/*
 * ICPC, Regionals, Asia Pacific, Thailand,
 * 2011 ACM-ICPC Asia Phuket Regional Programming Contest 연습 세션 P4. Crucial Links
 * BOJ 5651 - maximum flow
 * Date: 2023.3.27
 */

#include<bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int cap[301][301];
    vector<int> adj[301];
    vector<pair<int, int>> edges;
    int pred[301];

    int tc; cin >> tc;
    while (tc--) {
        int N, M; cin >> N >> M;

        memset(cap, 0, sizeof cap);
        for (int i = 1; i <= N; adj[i++].clear());
        edges.clear();
        while (M--) {
            int u, v, c; cin >> u >> v >> c;
            cap[u][v] += c;
            adj[u].emplace_back(v);
            adj[v].emplace_back(u);
            edges.emplace_back(u, v);
        }

        auto bfs = [&] (int s, int t) {
            queue<int> q; q.emplace(s);
            memset(pred, 0, sizeof pred);
            while (!q.empty()) {
                int u = q.front(); q.pop();
                for (int& v : adj[u]) if (!pred[v] && cap[u][v]) {
                    pred[v] = u;
                    if (v == t) return true;
                    q.emplace(v);
                }
            }
            return false;
        };

        while (bfs(1, N)) {
            int f = INT_MAX;
            for (int v = N; v != 1; v = pred[v])
                f = min(f, cap[pred[v]][v]);
            for (int v = N; v != 1; v = pred[v]) {
                cap[pred[v]][v] -= f;
                cap[v][pred[v]] += f;
            }
        }

        int ans = 0;
        for (auto& [u, v] : edges) if (!bfs(u, v)) ans++;
        cout << ans << '\n';
    }

    return 0;
}
