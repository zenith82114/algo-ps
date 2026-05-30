/*
 * ICPC, Regionals, Europe, Northwestern Europe Regional Contest,
 * NWERC 2008 C. Cat vs. Dog
 * BOJ 3683
 * JUNGOL 15569
 *
 * bipartite matching, Konig's theorem
 * Date: 2022.9.22
 */

#include<bits/stdc++.h>
using namespace std;

char cap[502][502];
vector<int> adj[502];

inline void add_edge(int u, int v) {
    cap[u][v] = 1;
    cap[v][u] = 0;
    adj[u].emplace_back(v);
    adj[v].emplace_back(u);
}

bool bfs(int s, int t, vector<int> &pred) {
    queue<int> q;
    q.push(s);
    vector<bool> visited(pred.size(), false);
    visited[s] = true;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (const int &v : adj[u]) {
            if (!visited[v] && cap[u][v] > 0) {
                if (v == t) {
                    pred[t] = u;
                    return true;
                }
                visited[v] = true;
                pred[v] = u;
                q.push(v);
            }
        }
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int T; cin >> T;
    while (T--) {
        int C, D, V; cin >> C >> D >> V;

        vector<pair<int, int>> gC, gD;
        for (int i = 0; i < V; ++i) {
            char t1, t2;
            int a, b;
            cin >> t1 >> a >> t2 >> b;
            (t1 == 'C'? gC : gD).emplace_back(a, b);
        }
        const int VC = gC.size();
        const int VD = gD.size();

        for (int i = 0; i <= V+1; ++i)
            adj[i].clear();
        for (int i = 0; i < VC; ++i) {
            add_edge(0, i+1);
            for (int j = 0; j < VD; ++j)
                if (gC[i].first == gD[j].second || gC[i].second == gD[j].first)
                    add_edge(i+1, j+VC+1);
        }
        for (int j = 0; j < VD; ++j)
            add_edge(j+VC+1, V+1);

        int ans = 0;
        for (int i = 1; i <= V; ++i)
            ans += adj[i].size() > 0;

        vector<int> pred(V+2);
        while (bfs(0, V+1, pred)) {
            --ans;
            for (int i = V+1; i; i = pred[i]) {
                cap[pred[i]][i]--;
                cap[i][pred[i]]++;
            }
        }

        cout << ans << '\n';
    }

    return 0;
}
