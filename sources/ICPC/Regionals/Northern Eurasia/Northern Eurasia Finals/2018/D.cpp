/*
 * ICPC, Regionals, Northern Eurasia, Northern Eurasia Finals 2018
 * D. Distance Sum
 * QOJ 5392
 *
 * sparse graph, prefix sum
 * Date: 2026.8.13
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;
using ii = pair<int, int>;
const int MAXN = 1e5+4, INF = 1e9;

vector<ii> gph[MAXN];
int deg[MAXN];
i64 w[MAXN];

bitset<MAXN+42> seen;
vector<int> sp;
bitset<MAXN> is_sp;
vector<vector<int>> paths;

vector<int> dist[MAXN]; // for sp vertices only

i64 ps_w[2*MAXN], ps_wa[2*MAXN], ps_wb[2*MAXN];
i64 F[MAXN];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m; cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int x, y; cin >> x >> y;
        gph[x].emplace_back(y, i); ++deg[x];
        gph[y].emplace_back(x, i); ++deg[y];
    }
    for (int x = 1; x <= n; ++x) w[x] = 1;
    i64 ans_leaf = 0;

    // remove leaves
    queue<int> q;
    for (int x = 1; x <= n; ++x) if (deg[x] == 1) q.push(x);
    while (!q.empty()) {
        int x = q.front(); q.pop();
        if (deg[x] != 1) continue;

        deg[x] = 0;
        --m;
        ans_leaf += w[x]*(n - w[x]);

        for (auto [y, i] : gph[x]) if (deg[y]) {
            w[y] += w[x];
            if (--deg[y] == 1) q.push(y);
            seen.set(i);
            break;
        }
    }
    // no edge remaining; the graph was a tree
    if (!m) { cout << ans_leaf; return 0; }

    for (int x = 1; x <= n; ++x) if (deg[x] > 2) {
        sp.push_back(x);
        is_sp.set(x);
    }
    if (sp.empty()) {
        for (int x = 1; x <= n; ++x) if (deg[x]) {
            sp.push_back(x);
            is_sp.set(x);
            break;
        }
    }

    // BFS and F values for sp vertices
    for (int x0 : sp) {
        auto& d = dist[x0];
        d.assign(n+1, INF); d[x0] = 0;
        queue<int> q; q.push(x0);

        while (!q.empty()) {
            int x = q.front(); q.pop();

            for (auto [y, i] : gph[x]) if (deg[y] && !seen[i]) {
                if (d[y] > d[x] + 1) {
                    d[y] = d[x] + 1;
                    q.push(y);
                }
            }
        }

        for (int y = 1; y <= n; ++y) if (deg[y]) F[x0] += w[y]*d[y];
    }

    // find sp-sp paths
    for (int x0 : sp) {
        for (auto [y, i] : gph[x0]) if (deg[y] && !seen[i]) {
            vector<int> path { x0, y };
            int x = y, e = i;
            seen.set(i);

            while (!is_sp[x]) {
                int nx = -1, ne = -1;

                for (auto [z, j] : gph[x]) if (deg[z] && j != e) {
                    nx = z, ne = j; break;
                }
                path.push_back(nx);
                seen.set(ne);
                x = nx, e = ne;
            }

            paths.emplace_back(std::move(path));
        }
    }

    seen.reset();

    // compute F values for all internal vertices in sp-sp path in batch
    for (const auto& path : paths) {
        int L = path.size()-1;
        int a = path[0], b = path[L];
        int C = L + dist[a][b];

        for (int x : path) seen.set(x);

        fill_n(ps_w, 2*L+1, 0);
        fill_n(ps_wa, 2*L+1, 0);
        fill_n(ps_wb, 2*L+1, 0);

        for (int x = 1; x <= n; ++x) if (deg[x] && !seen[x]) {
            int dt = dist[a][x] - dist[b][x]; // in [-L, L]
            ps_w[L+dt] += w[x];
            ps_wa[L+dt] += w[x]*dist[a][x];
            ps_wb[L+dt] += w[x]*dist[b][x];
        }
        partial_sum(ps_w, ps_w + 2*L+1, ps_w);
        partial_sum(ps_wa, ps_wa + 2*L+1, ps_wa);
        partial_sum(ps_wb, ps_wb + 2*L+1, ps_wb);

        // outside contribution
        for (int i = 1; i < L; ++i) {
            F[path[i]] += i*ps_w[2*(L-i)] + ps_wa[2*(L-i)]
                + (L-i)*(ps_w[2*L] - ps_w[2*(L-i)]) + ps_wb[2*L] - ps_wb[2*(L-i)];
        }

        ps_w[0] = ps_wa[0] = 0;
        for (int i = 1; i < L; ++i) {
            ps_w[i] = w[path[i]];
            ps_wa[i] = i * w[path[i]];
        }
        partial_sum(ps_w, ps_w + L, ps_w);
        partial_sum(ps_wa, ps_wa + L, ps_wa);

        // inside contribution
        for (int i = 1; i < L; ++i) {
            F[path[i]] += i*ps_w[i-1] - ps_wa[i-1]
                + (ps_wa[L-1] - ps_wa[i]) - i*(ps_w[L-1] - ps_w[i]);

            int q = i - C/2 - 1;
            if (q >= 0) F[path[i]] += (C - 2*i)*ps_w[q] + 2*ps_wa[q];
            q = i + C/2;
            if (q < L) F[path[i]] += (C + 2*i)*(ps_w[L-1] - ps_w[q]) - 2*(ps_wa[L-1] - ps_wa[q]);
        }

        // sp contribution
        for (int i = 1; i < L; ++i) {
            F[path[i]] += w[a]*min(i, C-i);
            if (a != b) F[path[i]] += w[b]*min(L-i, dist[a][b]+i);
        }

        for (int x : path) seen.reset(x);
    }

    i64 ans_core = 0;
    for (int x = 1; x <= n; ++x) if (deg[x]) ans_core += w[x]*F[x];
    cout << (ans_leaf + ans_core/2);
    return 0;
}
