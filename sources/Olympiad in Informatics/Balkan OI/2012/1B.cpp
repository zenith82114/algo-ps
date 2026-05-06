/*
 * Balkan Olympiad in Informatics, BOI 2012 Day 1 B. Shortest Paths
 * BOJ 5250
 * JUNGOL 8304
 *
 * Dijkstra's, segment tree
 * Date: 2023.8.18
 */

#include<bits/stdc++.h>
using namespace std;
constexpr int inf = INT32_MAX;

class seg_tree {
    vector<int> ar;
    int n;
public:
    seg_tree(int sz) {
        n = 1; while (n < sz) n <<= 1;
        ar.resize(2*n, inf);
    }
    void set_min(int i, int j, int x) {
        for (i |= n, j |= n; i <= j; i >>= 1, j >>= 1) {
            if ( i&1) ar[i] = min(ar[i], x), ++i;
            if (~j&1) ar[j] = min(ar[j], x), --j;
        }
    }
    int query(int i) {
        int ans = inf;
        for (i |= n; i; i >>= 1) ans = min(ans, ar[i]);
        return ans;
    }
};

vector<pair<int, int> > gph[2048];
int path_idx[2048];
int dist_a[2048], dist_b[2048];
int loa_a[2048], loa_b[2048]; // lowest on-path ancestor

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);

    int n, m, a, b; cin >> n >> m >> a >> b;
    while (m--) {
        int x, y, w; cin >> x >> y >> w;
        gph[x].emplace_back(y, w);
        gph[y].emplace_back(x, w);
    }
    for (int x = 1; x <= n; ++x) {
        path_idx[x] = -1; loa_a[x] = -1; loa_b[x] = -1;
    }
    int k; cin >> k;
    for (int i = 0; i < k; ++i) {
        int x; cin >> x;
        path_idx[x] = i; loa_a[x] = x; loa_b[x] = x;
    }

    priority_queue<pair<int, int> > pq;
    pq.emplace(0, a);
    for (int x = 1; x <= n; ++x) dist_a[x] = inf;
    dist_a[a] = 0;
    while (!pq.empty()) {
        auto [dx, x] = pq.top(); pq.pop(); dx = -dx;
        if (dist_a[x] < dx) continue;
        for (const auto& [y, w] : gph[x]) if (dist_a[y] > dx + w) {
            dist_a[y] = dx + w;
            if (path_idx[y] == -1) loa_a[y] = loa_a[x];
            pq.emplace(-dist_a[y], y);
        }
    }

    pq.emplace(0, b);
    for (int x = 1; x <= n; ++x) dist_b[x] = inf;
    dist_b[b] = 0;
    while (!pq.empty()) {
        auto [dx, x] = pq.top(); pq.pop(); dx = -dx;
        if (dist_b[x] < dx) continue;
        for (const auto& [y, w] : gph[x]) if (dist_b[y] > dx + w) {
            dist_b[y] = dx + w;
            if (path_idx[y] == -1) loa_b[y] = loa_b[x];
            pq.emplace(-dist_b[y], y);
        }
    }

    seg_tree segt(k);
    for (int x = 1; x <= n; ++x) for (const auto& [y, w] : gph[x]) {
        int i = path_idx[x], j = path_idx[y];
        if (i != -1 && j != -1 && (i - j == 1 || i - j == -1)) continue;
        if (dist_a[x] == inf || dist_b[y] == inf) continue;

        i = path_idx[loa_a[x]], j = path_idx[loa_b[y]];
        if (i >= j) continue;
        segt.set_min(i, j-1, dist_a[x] + w + dist_b[y]);
    }

    for (int i = 0; i < k-1; ++i) {
        int ans = segt.query(i);
        cout << (ans == inf? -1 : ans) << '\n';
    }
    return 0;
}
