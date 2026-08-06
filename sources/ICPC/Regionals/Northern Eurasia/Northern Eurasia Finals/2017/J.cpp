/*
 * ICPC, Regionals, Northern Eurasia, Northern Eurasia Finals 2017
 * J. Journey from Petersburg to Moscow
 * QOJ 11794
 *
 * Dijkstra's
 * Date: 2026.8.6
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;
using ii = pair<int, int>;

const int MAXN = 3e3+4;
const i64 INF = 1e18;

int n;
vector<ii> gph[MAXN];
array<i64, MAXN> dist;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int m, k; cin >> n >> m >> k;
    vector<int> wgt { 0 };
    while (m--) {
        int x, y, w; cin >> x >> y >> w;
        gph[x].emplace_back(y, w);
        gph[y].emplace_back(x, w);
        wgt.push_back(w);
    }

    i64 ans = INF;
    for (int t : wgt) {
        priority_queue<pair<i64, int>> pq; pq.emplace(0, 1);
        dist.fill(INF); dist[1] = 0;

        while (!pq.empty()) {
            auto [dx, x] = pq.top(); pq.pop(); dx = -dx;
            if (dist[x] < dx) continue;

            for (auto [y, w] : gph[x]) {
                int c = max(0, w - t);
                if (dist[y] > dist[x] + c) {
                    dist[y] = dist[x] + c;
                    pq.emplace(-dist[y], y);
                }
            }
        }
        ans = min(ans, (i64)k*t + dist[n]);
    }

    cout << ans;
    return 0;
}
