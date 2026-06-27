/*
 * ICPC, Regionals, Northern Eurasia, Northern Eurasia Finals 2018
 * B. Bimatching
 * QOJ 5390
 *
 * general maximum matching
 * Date: 2026.6.27
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;
using ii = pair<int, int>;
const int MAXN = 300;

vector<int> gph[MAXN];
array<int, MAXN> match, vis, orig, par, upd;
int tag = 0;

int lca(int x, int y) {
    ++tag;
    while (!x || upd[x] != tag) {
        if (x) {
            upd[x] = tag;
            x = orig[par[match[x]]];
        }
        swap(x, y);
    }
    return x;
}

void blossom(int x, int y, int a, queue<int>& q) {
    while (orig[x] != a) {
        par[x] = y; y = match[x];
        if (vis[y] == 1) { q.push(y); vis[y] = 0; }
        orig[x] = orig[y] = a;
        x = par[y];
    }
}

bool bfs(int u) {
    iota(begin(orig), end(orig), 0);
    vis.fill(-1); vis[u] = 0;
    queue<int> q; q.push(u);

    while (!q.empty()) {
        int x = q.front(); q.pop();

        for (int y : gph[x]) {
            if (vis[y] == -1) {
                par[y] = x; vis[y] = 1;
                if (!match[y]) {
                    while (y) {
                        int py = par[y];
                        int ny = match[py];
                        match[y] = py; match[py] = y;
                        y = ny;
                    }
                    return true;
                }
                q.push(match[y]); vis[match[y]] = 0;
            }
            else if (vis[y] == 0 && orig[x] != orig[y]) {
                int a = lca(orig[x], orig[y]);
                blossom(x, y, a, q);
                blossom(y, x, a, q);
            }
        }
    }
    return false;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int tc; cin >> tc;
    while (tc--) {
        int n, m; cin >> n >> m;
        for (int u = 1; u <= 2*n + m; ++u) gph[u].clear();

        auto add_edge = [](int x, int y) {
            gph[x].push_back(y);
            gph[y].push_back(x);
        };

        for (int i = 1; i <= n; ++i) {
            add_edge(i, n + i);

            string s; cin >> s;
            for (int j = 1; j <= m; ++j) if (s[j-1] == '1') {
                add_edge(i, 2*n + j);
                add_edge(n + i, 2*n + j);
            }
        }

        match.fill(0);
        upd.fill(0);
        int ans = 0;
        for (int u = 1; u <= 2*n + m; ++u) if (!match[u] && bfs(u)) ++ans;
        cout << (ans - n) << '\n';
    }
}
