/*
 * International Olympiad in Informatics, IOI 2013, Day 1 A. Dreaming
 * BOJ 8872
 * JUNGOL 2626
 *
 * tree diamater and radius
 * Date: 2025.7.18
 */

#include<bits/stdc++.h>
using namespace std;
constexpr int MAXN = 1e5;

vector<pair<int, int> > adj[MAXN];
bitset<MAXN> vis;
array<int, MAXN> par, dep;

int dfs(int px, int x) {
    int ans = x;
    par[x] = px;
    vis.set(x);
    for (const auto& [y, w] : adj[x]) if (y != px) {
        dep[y] = dep[x] + w;
        int z = dfs(x, y);
        if (dep[ans] < dep[z]) ans = z;
    }
    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m, L; cin >> n >> m >> L;
    while (m--) {
        int x, y, w; cin >> x >> y >> w;
        adj[x].emplace_back(y, w);
        adj[y].emplace_back(x, w);
    }

    int d1 = 0;
    int r1 = -1, r2 = -1, r3 = -1;
    for (int x = 0; x < n; ++x) if (!vis[x]) {
        dep[x] = 0;
        int y = dfs(-1, x);
        dep[y] = 0;
        int u = dfs(-1, y);
        int d = dep[u];
        while (u != y && dep[par[u]] * 2 > d) u = par[u];
        int v = par[u];

        dep[u] = 0;
        int r = dep[dfs(-1, u)];
        if (v != -1) {
            dep[v] = 0;
            r = min(r, dep[dfs(-1, v)]);
        }

        d1 = max(d, d1);
        if (r1 <= r) { r3 = r2; r2 = r1; r1 = r; }
        else if (r2 <= r) { r3 = r2; r2 = r; }
        else r3 = max(r3, r);
    }

    int ans = d1;
    if (r2 > -1) ans = max(ans, r1 + r2 + L);
    if (r3 > -1) ans = max(ans, r2 + r3 + L + L);
    cout << ans;
    return 0;
}
