/*
 * Petrozavodsk Programming Camp, Summer 2019, Day 8: Jingzhe Tang Contest 2, XIX Open Cup Onsite D. Honeycomb
 * BOJ 18653 - Gomory-Hu tree; Gusfield's
 * Date: 2026.3.16
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;
using ii = pair<int, int>;
constexpr int MAXV = 100*100;

string grid[403];
bitset<MAXV> valid;
vector<ii> gph[MAXV];
vector<int> cap;
array<int, MAXV> par, dsu;
array<ii, MAXV> pred;

int dsu_find(int x) {
    return dsu[x] < 0 ? x : (dsu[x] = dsu_find(dsu[x]));
}

int dsu_unite(int x, int y) {
    x = dsu_find(x), y = dsu_find(y);
    if (x == y) return 0;
    if (dsu[x] < dsu[y]) swap(x, y);
    int ret = dsu[x] * dsu[y];
    dsu[y] += dsu[x];
    dsu[x] = y;
    return ret;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int TC; cin >> TC;
    for (int tc = 1; tc <= TC; ++tc) {
        int n, m; cin >> n >> m;
        cin.ignore();

        const int L = 4*n + 3;
        for (int i = 0; i < L; ++i) getline(cin, grid[i]);

        auto at_grid = [&](int x, int y) -> char {
            if (x < 0 || x >= L) return ' ';
            if (y < 0 || y >= (int)grid[x].size()) return ' ';
            return grid[x][y];
        };

        valid.set();
        for (int u = 0; u < n*m; ++u) gph[u].clear();
        cap.clear();

        for (int x = 0; x < n; ++x)
        for (int y = 0; y < m; ++y) {
            if (at_grid(4*x + 2 + (y&1 ? 2 : 0), 6*y + 4) != '*') {
                valid.reset(x*m + y);
                continue;
            }

            ii edge_pos[6], nbor_pos[6];
            if (y%2 == 0) {
                edge_pos[0]={4*x,   6*y+4}; nbor_pos[0]={x-1, y};
                edge_pos[1]={4*x+1, 6*y+7}; nbor_pos[1]={x-1, y+1};
                edge_pos[2]={4*x+3, 6*y+7}; nbor_pos[2]={x,   y+1};
                edge_pos[3]={4*x+4, 6*y+4}; nbor_pos[3]={x+1, y};
                edge_pos[4]={4*x+3, 6*y+1}; nbor_pos[4]={x,   y-1};
                edge_pos[5]={4*x+1, 6*y+1}; nbor_pos[5]={x-1, y-1};
            } else {
                edge_pos[0]={4*x+2, 6*y+4}; nbor_pos[0]={x-1, y};
                edge_pos[1]={4*x+3, 6*y+7}; nbor_pos[1]={x,   y+1};
                edge_pos[2]={4*x+5, 6*y+7}; nbor_pos[2]={x+1, y+1};
                edge_pos[3]={4*x+6, 6*y+4}; nbor_pos[3]={x+1, y};
                edge_pos[4]={4*x+5, 6*y+1}; nbor_pos[4]={x+1, y-1};
                edge_pos[5]={4*x+3, 6*y+1}; nbor_pos[5]={x,   y-1};
            }

            for (int i = 0; i < 6; ++i) {
                auto [nx, ny] = nbor_pos[i];
                if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
                auto [ex, ey] = edge_pos[i];
                if (at_grid(ex, ey) == ' ') {
                    int u = x*m + y, v = nx*m + ny;
                    if (u < v) {
                        gph[u].emplace_back(v, (int)cap.size());
                        cap.push_back(1);
                        gph[v].emplace_back(u, (int)cap.size());
                        cap.push_back(1);
                    }
                }
            }
        }

        auto bfs = [&] (int s, int t) -> bool {
            queue<int> q; q.emplace(s);
            for (int u = 0; u < n*m; ++u) pred[u].first = -1;
            while (!q.empty()) {
                int u = q.front(); q.pop();
                if (u == t) return true;
                for (auto [v, e] : gph[u]) if (pred[v].first == -1 && cap[e]) {
                    q.emplace(v);
                    pred[v] = ii(u, e);
                }
            }
            return false;
        };

        auto bfs_final = [&] (int s) -> bitset<MAXV> {
            queue<int> q; q.emplace(s);
            bitset<MAXV> seen; seen.set(s);
            while (!q.empty()) {
                int u = q.front(); q.pop();
                for (auto [v, e] : gph[u]) if (!seen[v] && cap[e]) {
                    q.emplace(v);
                    seen.set(v);
                }
            }
            return seen;
        };

        vector<tuple<int, int, int> > edges;
        par.fill(0);

        for (int u = 1; u < n*m; ++u) if (valid[u]) {
            int flow = 0;
            fill(cap.begin(), cap.end(), 1);
            while (bfs(u, par[u])) {
                ++flow;
                for (int w = par[u]; w != u;) {
                    auto [v, e] = pred[w];
                    --cap[e], ++cap[e^1];
                    w = v;
                }
            }
            edges.emplace_back(flow, u, par[u]);
            auto min_cut = bfs_final(u);
            for (int v = u + 1; v < n*m; ++v) {
                if (min_cut[v] && par[v] == par[u]) par[v] = u;
            }
        }

        i64 ans = 0;
        dsu.fill(-1);
        sort(edges.begin(), edges.end(), greater<>());
        for (auto [w, x, y] : edges) ans += (i64)w * dsu_unite(x, y);
        cout << "Case #"<<tc<<": " << ans << '\n';
    }

    return 0;
}
