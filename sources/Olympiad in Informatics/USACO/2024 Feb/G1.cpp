/*
 * USA Computing Olympiad, USACO 2024 February Contest, Gold 1. Bessia Motors
 * JUNGOL 6272
 *
 * Dijkstra's
 * Date: 2026.5.1
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;
const int MAXN = 5e4 + 4;

vector<pair<int, int> > gph[MAXN];
set<int> src[MAXN];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m, c, r; size_t k; cin >> n >> m >> c >> r >> k;
    while (m--) {
        int x, y, w; cin >> x >> y >> w;
        gph[x].emplace_back(y, w);
        gph[y].emplace_back(x, w);
    }

    using entry = tuple<i64, int, int>;
    priority_queue<entry, vector<entry>, greater<>> pq;
    for (int x = 1; x <= c; ++x) pq.emplace(0, x, x);

    while (!pq.empty()) {
        auto [d, s, x] = pq.top(); pq.pop();
        if (src[x].size() >= k || src[x].find(s) != end(src[x])) continue;

        src[x].emplace(s);
        for (auto& [y, w] : gph[x]) if (src[y].size() < k && d + w <= r) {
            pq.emplace(d + w, s, y);
        }
    }

    vector<int> ans;
    for (int x = c + 1; x <= n; ++x) if (src[x].size() == k) ans.push_back(x);
    cout << ans.size();
    for (int x : ans) cout << '\n' << x;
    return 0;
}
