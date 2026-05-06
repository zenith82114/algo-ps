/*
 * ICPC, Regionals, Europe, Central Europe Regional Contest,
 * Polish Collegiate Programming Contest, AMPPZ 2012 H. Hydra
 * BOJ 7981 - DP, Dijkstra's
 * Date: 2024.1.22
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;

constexpr int MAXN = 200001;
array<vector<int>, MAXN> adj, adj_rev;
array<i64, MAXN> f, g;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n; cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> g[i] >> f[i];
        int r; cin >> r;
        while (r--) {
            int j; cin >> j;
            adj[i].emplace_back(j);
            adj_rev[j].emplace_back(i);
        }
    }
    for (int i = 1; i <= n; ++i) {
        for (int j : adj[i]) g[i] += f[j];
    }

    priority_queue<pair<i64, int> > pq;
    for (int i = 1; i <= n; ++i) {
        if (f[i] > g[i]) pq.emplace(-g[i], i);
    }

    while (!pq.empty()) {
        int i = pq.top().second; pq.pop();
        if (f[i] > g[i]) {
            i64 x = f[i] - g[i];
            f[i] = g[i];
            for (int j : adj_rev[i]) {
                g[j] -= x;
                if (f[j] > g[j]) pq.emplace(-g[j], j);
            }
        }
    }
    cout << f[1];
    return 0;
}
