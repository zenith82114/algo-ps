/*
 * ICPC, Regionals, Asia Pacific, Korea,
 * Daejeon Nationalwide Internet Competition 2013 H. Networks with Unidirectional Links
 * BOJ 3295
 *
 * bipartite matching
 * Date: 2022.10.3
 */

#include<bits/stdc++.h>
using namespace std;

vector<vector<int> > adj;
vector<int> takes;
bitset<1024> visited;

bool match(int u) {
    visited.set(u);
    for (const int &v : adj[u]) {
        int t = takes[v];
        if (t == -1 || (!visited[t] && match(t))) {
            takes[v] = u;
            return true;
        }
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int T; cin >> T;
    while (T--) {
        int N, M; cin >> N >> M;
        adj.clear(); adj.resize(N);
        while (M--) {
            int u, v; cin >> u >> v;
            adj[u].emplace_back(v);
        }

        takes.clear(); takes.resize(N, -1);
        int ans = 0;
        for (int u = 0; u < N; ++u) {
            visited.reset();
            if (match(u)) ans++;
        }

        cout << ans << '\n';
    }

    return 0;
}
