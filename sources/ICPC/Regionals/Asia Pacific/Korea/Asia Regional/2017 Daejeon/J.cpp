/*
 * ICPC, Regionals, Asia Pacific, Korea, Asia Regional - Daejeon 2017
 * J. Strongly Matchable
 * QOJ 13116
 *
 * graph theory, maximum flow
 * Date: 2026.6.30
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;
using ii = pair<int, int>;
const int INF = 1e9;

class max_flow {
    struct edge {
        int to, cap, flow;
        edge(int v, int c): to(v), cap(c), flow(0) {}
    };

    vector<vector<int>> gph;
    vector<edge> edges;
    vector<int> level;
    vector<size_t> hist;

    bool _bfs(int s, int t) {
        queue<int> q; q.push(s);
        fill(begin(level), end(level), -1); level[s] = 0;

        while (!q.empty()) {
            int u = q.front(); q.pop();

            for (int e : gph[u]) {
                auto [v, c, f] = edges[e];

                if (level[v] == -1 && f < c) {
                    level[v] = level[u] + 1;
                    q.push(v);
                }
            }
        }

        return level[t] != -1;
    }

    int _dfs(int u, int t, int lim) {
        if (u == t) return lim;

        for (auto& p = hist[u]; p < gph[u].size(); ++p) {
            int e = gph[u][p];
            auto& [v, c, f] = edges[e];

            if (level[v] == level[u] + 1 && f < c) {
                int df = _dfs(v, t, min(lim, c - f));
                if (df > 0) {
                    f += df;
                    edges[e^1].flow -= df;
                    return df;
                }
            }
        }
        return 0;
    }

public:
    max_flow(int n): gph(n), level(n), hist(n) {}

    void add_edge(int u, int v, int c) {
        gph[u].push_back(edges.size());
        edges.emplace_back(v, c);
        gph[v].push_back(edges.size());
        edges.emplace_back(u, 0);
    }

    int run(int s, int t) {
        for (auto& e : edges) e.flow = 0;
        int f = 0;

        while (_bfs(s, t)) {
            fill(begin(hist), end(hist), 0);

            int df;
            while ((df = _dfs(s, t, INF)) > 0) f += df;
        }
        return f;
    }
};

bool adj[100][100] {};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m; cin >> n >> m;
    max_flow mf(2*n);

    for (int x = 0; x < n; ++x) mf.add_edge(2*x, 2*x+1, 1);
    while (m--) {
        int x, y; cin >> x >> y; --x; --y;
        adj[x][y] = adj[y][x] = true;
        mf.add_edge(2*x+1, 2*y, INF);
        mf.add_edge(2*y+1, 2*x, INF);
    }

    for (int x = 0; x < n; ++x)
    for (int y = x+1; y < n; ++y) if (!adj[x][y]) {
        if (mf.run(2*x+1, 2*y) < n/2) { cout << -1; return 0; }
    }
    cout << 1; return 0;
}
