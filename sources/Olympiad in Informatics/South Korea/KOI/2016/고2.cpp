/*
 * 한국정보올림피아드, KOI 2016, 고등부 2. 주유소
 * BOJ 13308
 * JUNGOL 2999
 *
 * Dijkstra's
 * Date: 2023.11.8
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;

vector<pair<int, int> > adj[2501];
int price[2501];
i64 dist[2501][2501];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);

    int n, m; cin >> n >> m;
    for (int x = 1; x <= n; ++x) cin >> price[x];
    while (m--) {
        int x, y, w; cin >> x >> y >> w;
        adj[x].emplace_back(y, w);
        adj[y].emplace_back(x, w);
    }

    dist[1][price[1]] = 0;
    for (int x = 1; x <= n; ++x)
    for (int p = 1; p <= 2500; ++p) dist[x][p] = INT64_MAX;

    priority_queue<tuple<i64, int, int> > pq;
    pq.emplace(0, 1, price[1]);
    while (!pq.empty()) {
        auto [d, x, p] = pq.top(); pq.pop();
        d = -d;
        if (dist[x][p] < d) continue;
        for (const auto& [y, w] : adj[x]) {
            int np = min(p, price[y]);
            i64 nd = d + w*p;
            if (dist[y][np] > nd) {
                dist[y][np] = nd;
                pq.emplace(-nd, y, np);
            }
        }
    }

    i64 ans = INT64_MAX;
    for (int p = 1; p <= 2500; ++p) ans = min(ans, dist[n][p]);
    cout << ans;
    return 0;
}
