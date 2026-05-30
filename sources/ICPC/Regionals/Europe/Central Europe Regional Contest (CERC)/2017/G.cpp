/*
 * ICPC, Regionals, Europe, Central Europe Regional Contest,
 * CERC 2017 G. Gambling Guide
 * BOJ 15264
 * JUNGOL 11581
 *
 * Dijkstra's
 * Date: 2023.6.1
 */

#include<bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);

    int N, M; cin >> N >> M;
    vector<vector<int> > adj(N+1);
    while (M--) {
        int x, y; cin >> x >> y;
        adj[x].emplace_back(y);
        adj[y].emplace_back(x);
    }

    vector<double> dist(N+1, DBL_MAX); dist[N] = 0.;
    vector<int> cnt(N+1);
    vector<double> sum(N+1);

    priority_queue<pair<double, int> > pq; pq.emplace(0., N);
    while (!pq.empty()) {
        auto [d, x] = pq.top(); pq.pop();
        d = -d;
        if (dist[x] < d) continue;
        for (int y : adj[x]) if (dist[y] > d) {
            ++cnt[y];
            sum[y] += d;
            double t = (adj[y].size() + sum[y]) / cnt[y];
            if (dist[y] > t) {
                dist[y] = t;
                pq.emplace(-t, y);
            }
        }
    }

    cout << fixed << setprecision(10) << dist[1];
    return 0;
}
