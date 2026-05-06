/*
 * International Olympiad in Informatics, IOI 2013, Day 1 A. Dreaming
 * BOJ 8872
 * JUNGOL 2626
 *
 * tree diamater and radius
 * Date: 2025.1.15
 */

#include<bits/stdc++.h>
using namespace std;

vector<pair<int, int> > adj[100000];
bitset<100000> vis;
array<int, 100000> f, h;

int dfs1(int px, int x) {
    int d = 0;
    h[x] = 0;
    int h2x = 0;
    for (const auto& [y, w] : adj[x]) if (y != px) {
        d = max(d, dfs1(x, y));
        int t = w + h[y];
        if (h[x] <= t) { h2x = h[x]; h[x] = t; }
        else h2x = max(h2x, t);
    }
    for (const auto& [y, w] : adj[x]) if (y != px) {
        f[y] = w + (w + h[y] == h[x]? h2x : h[x]);
    }
    d = max(d, h[x] + h2x);
    return d;
}

int dfs2(int px, int x) {
    vis.set(x);
    int r = max(f[x], h[x]);
    for (const auto& [y, w] : adj[x]) if (y != px) {
        f[y] = max(f[y], f[x] + w);
        r = min(r, dfs2(x, y));
    }
    return r;
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
        f[x] = 0;
        d1 = max(d1, dfs1(-1, x));
        int r = dfs2(-1, x);
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
