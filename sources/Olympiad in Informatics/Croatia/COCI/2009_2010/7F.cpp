/*
 * Croatian Open Competition in Informatics, COCI 2009/2010, Contest #7 F. RESTORAN
 * BOJ 2889
 *
 * Eulerian circuit
 * Date: 2025.12.30
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;
using ii = pair<int, int>;
constexpr int MAXN = 1e5 + 4, MAXM = 2e5;

vector<ii> g[MAXN];
vector<ii>::iterator iter[MAXN];
bitset<MAXN> node_vis;
int edge_vis[MAXM];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m; cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int x, y; cin >> x >> y;
        g[x].emplace_back(y, i);
        g[y].emplace_back(x, i);
    }
    int old_m = m;
    for (int x = 1; x <= n; ++x) if (g[x].size() & 1) {
        g[0].emplace_back(x, m);
        g[x].emplace_back(0, m);
        ++m;
    }
    for (int x = 0; x <= n; ++x) iter[x] = begin(g[x]);

    for (int x = 0; x <= n; ++x) if (!node_vis[x]) {
        stack<ii> s; s.emplace(x, -1);
        int color = 1;
        while (!s.empty()) {
            auto [x, i] = s.top();
            while (iter[x] < end(g[x]) && edge_vis[iter[x]->second] != 0) ++iter[x];
            if (iter[x] == end(g[x])) {
                s.pop();
                node_vis.set(x);
                if (i != -1) { edge_vis[i] = color; color ^= 3; }
            }
            else {
                s.emplace(*iter[x]);
                edge_vis[iter[x]->second] = -1;
            }
        }
    }

    for (int x = 0; x <= n; ++x) {
        if (g[x].size() == 2 && edge_vis[g[x][0].second] == edge_vis[g[x][1].second]) {
            cout << 0; return 0;
        }
    }
    for (int i = 0; i < old_m; ++i) cout << edge_vis[i] << '\n';
    return 0;
}
