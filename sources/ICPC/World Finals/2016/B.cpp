/*
 * ICPC, World Finals, ACM-ICPC World Finals 2016 B. Branch Assignment
 * BOJ 12766
 * JUNGOL 3512
 *
 * Dijkstra's, DnC DP optimization
 * Date: 2023.1.8
 */

#include<bits/stdc++.h>
using namespace std;

using graph = vector<vector<pair<int, int>>>;
using i64 = int64_t;

void dijkstra(int src, const graph& adj, vector<int>& dist) {
    priority_queue<pair<i64, int>> pq;
    pq.emplace(0, src);
    dist.resize(adj.size(), INT_MAX);
    dist[src] = 0L;

    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop(); d = -d;
        for (const auto& [v, l] : adj[u]) if (dist[v] > d + l) {
            dist[v] = d + l;
            pq.emplace(-dist[v], v);
        }
    }
}

vector<i64> psum, dp0, dp1;

void dnc(int jl, int jr, int kl, int kr) {
    if (jl > jr) return;
    int jm = (jl + jr)>>1;
    i64& ans = dp1[jm] = INT64_MAX;
    int opt = 0;
    for (int k = kl; k <= min(jm, kr); ++k) {
        i64 tmp = dp0[k-1] + (jm - k) * (psum[jm] - psum[k-1]);
        if (ans > tmp) {
            ans = tmp;
            opt = k;
        }
    }
    dnc(jl, jm-1, kl, opt);
    dnc(jm+1, jr, opt, kr);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int N, B, S, R; cin >> N >> B >> S >> R;
    graph g(N+1), gt(N+1);
    while (R--) {
        int u, v, l; cin >> u >> v >> l;
        g[u].emplace_back(v, l);
        gt[v].emplace_back(u, l);
    }

    vector<int> d, dt;
    dijkstra(B+1, g, d);
    dijkstra(B+1, gt, dt);
    psum.resize(B+1, 0L);
    for (int j = 1; j <= B; ++j) psum[j] = d[j] + dt[j];
    sort(psum.begin(), psum.end());
    partial_sum(psum.begin(), psum.end(), psum.begin());

    dp0.resize(B+1);
    dp1.resize(B+1);
    for (int j = 0; j <= B; ++j) dp1[j] = (j-1) * psum[j];
    for (int i = 2; i <= S; ++i) {
        dp0.swap(dp1);
        dnc(1, B, 1, B);
    }
    cout << dp1[B] << '\n';

    return 0;
}
