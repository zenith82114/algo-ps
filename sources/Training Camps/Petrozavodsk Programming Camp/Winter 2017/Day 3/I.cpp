/*
 * Petrozavodsk Programming Camp, Winter 2017, Day 3: U of Tokyo Selection 1
 * I. Shortest Path Queries
 * QOJ 671
 *
 * Dijkstra's, DnC
 * Date: 2024.6.15
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;
using ii = pair<int, int>;
const int
    MAXW = 10,
    MAXH = 1e4,
    MAXQ = 1e5;
const i64 INF = 2e18;
const int dt[] { 0, 1, 0, -1, 0 };

int w, h, q;
int cost[MAXW][MAXH];

struct query { int sx, sy, tx, ty; };
query que[MAXQ];
i64 ans[MAXQ];

priority_queue<tuple<i64, int, int> > pq;
i64 dist[MAXW][MAXH];

void dnc(const vector<int>& ids, int lo, int hi) {
    int mid = (lo + hi)/2;

    for (int s = 0; s < w; ++s) {
        for (int x = 0; x < w; ++x)
        for (int y = lo; y <= hi; ++y) dist[x][y] = INF;

        dist[s][mid] = 0;
        pq.emplace(0, s, mid);

        while (!pq.empty()) {
            auto [d, x, y] = pq.top(); pq.pop();
            d = -d;
            if (dist[x][y] < d) continue;

            for (int k = 0; k < 4; ++k) {
                int nx = x + dt[k];
                int ny = y + dt[k+1];
                if (nx < 0 || nx == w || ny < lo || ny > hi) continue;
                if (dist[nx][ny] > d + cost[nx][ny]) {
                    dist[nx][ny] = d + cost[nx][ny];
                    pq.emplace(-dist[nx][ny], nx, ny);
                }
            }
        }

        for (int id : ids) {
            const auto& [sx, sy, tx, ty] = que[id];
            ans[id] = min(ans[id], dist[sx][sy] + dist[tx][ty] + cost[s][mid]);
        }
    }

    vector<int> ids_lo, ids_hi;
    for (int id : ids) {
        if (que[id].ty < mid) ids_lo.push_back(id);
        if (que[id].sy > mid) ids_hi.push_back(id);
    }
    if (ids_lo.size()) dnc(ids_lo, lo, mid-1);
    if (ids_hi.size()) dnc(ids_hi, mid+1, hi);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> w >> h >> q;

    for (int y = 0; y < h; ++y)
    for (int x = 0; x < w; ++x) cin >> cost[x][y];

    for (int id = 0; id < q; ++id) {
        auto& [sx, sy, tx, ty] = que[id];
        cin >> sx >> sy >> tx >> ty;
        --sx; --sy; --tx; --ty;
        if (sy > ty) { swap(sx, tx); swap(sy, ty); }
        ans[id] = INF;
    }

    vector<int> ids(q); iota(ids.begin(), ids.end(), 0);
    dnc(ids, 0, h-1);
    for (int id = 0; id < q; ++id) cout << ans[id] << '\n';
    return 0;
}
