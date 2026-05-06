/*
 * POI Training Camp, ONTAK 2011 3-3. Ewakuacja
 * BOJ 8452 - BFS, offline queries
 * Date: 2024.1.24
 */

#include<bits/stdc++.h>
using namespace std;

vector<int> adj[1024];
int dist[1024];
pair<int, int> edg[100'005];
bitset<100'005> del;
int que[200'005];
int ans[200'005];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m, q; cin >> n >> m >> q;
    for (int i = 1; i <= m; ++i) {
        auto& [x, y] = edg[i]; cin >> x >> y;
    }
    for (int i = 1; i <= q; ++i) {
        char op; cin >> op >> que[i];
        if (op == 'U') del.set(que[i]);
        else que[i] = ~que[i];
    }
    for (int i = 1; i <= m; ++i) if (!del[i]) {
        const auto& [x, y] = edg[i];
        adj[x].emplace_back(y);
    }
    memset(dist, 0x3f, sizeof dist); dist[1] = 0;
    queue<int> Q; Q.emplace(1);
    while (!Q.empty()) {
        int x = Q.front(); Q.pop();
        for (int y : adj[x]) if (dist[y] > dist[x] + 1) {
            dist[y] = dist[x] + 1;
            Q.emplace(y);
        }
    }

    for (int i = q; i > 0; --i) {
        int k = que[i];
        if (k > 0) {
            auto [x, y] = edg[k];
            adj[x].emplace_back(y);
            if (dist[y] <= dist[x] + 1) continue;
            dist[y] = dist[x] + 1; Q.emplace(y);
            while (!Q.empty()) {
                int x = Q.front(); Q.pop();
                for (int y : adj[x]) if (dist[y] > dist[x] + 1) {
                    dist[y] = dist[x] + 1;
                    Q.emplace(y);
                }
            }
        } else {
            ans[i] = dist[~k];
        }
    }
    for (int i = 1; i <= q; ++i) if (que[i] < 0) {
        cout << (ans[i] == 0x3f3f3f3f? -1 : ans[i]) << '\n';
    }

    return 0;
}
