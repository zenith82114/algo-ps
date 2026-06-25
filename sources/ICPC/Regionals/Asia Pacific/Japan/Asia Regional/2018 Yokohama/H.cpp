/*
 * ICPC, Regionals, Asia Pacific, Japan, 2018 ICPC Asia Yokohama Regional Contest
 * H. Four-Coloring
 * QOJ 3318
 *
 * planar graph
 * Date: 2026.6.26
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;
using ii = pair<int, int>;

const int MAXN = 1e4 +4;

array<int, MAXN> x, y, indeg, clr;
vector<int> gph[MAXN];
int dag[MAXN][4] {};
bitset<MAXN> seen;

bool connected(int u, int t, int c1, int c2) {
    seen.set(u);
    if (u == t) return true;
    for (int v : gph[u]) if (clr[v] == c1 || clr[v] == c2) {
        if (!seen[v] && connected(v, t, c1, c2)) return true;
    }
    return false;
}

void swap_color(int u, int c1, int c2) {
    clr[u] ^= c1 ^ c2;
    for (int v : gph[u]) if (clr[u] == clr[v]) swap_color(v, c1, c2);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m; cin >> n >> m;
    for (int i = 1; i <= n; ++i) cin >> x[i] >> y[i];
    indeg.fill(0);
    while (m--) {
        int u, v; cin >> u >> v;
        gph[u].push_back(v);
        gph[v].push_back(u);

        if (y[u] < y[v] || (y[u] == y[v] && x[u] > x[v])) swap(u, v);
        ++indeg[v];

        if (x[u] > x[v]) dag[u][0] = v;
        else if (x[u] == x[v]) dag[u][1] = v;
        else if (y[u] > y[v]) dag[u][2] = v;
        else dag[u][3] = v;
    }

    stack<int> st;
    queue<int> q;
    for (int u = 1; u <= n; ++u) if (!indeg[u]) q.push(u);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        st.push(u);
        for (int v : dag[u]) if (v) {
            if (--indeg[v] == 0) q.push(v);
        }
    }

    while (!st.empty()) {
        int u = st.top(); st.pop();
        int b = 0; for (int v : dag[u]) b |= 1<<clr[v];
        int c = 1; while ((b>>c)&1) ++c;

        if (c < 5) { clr[u] = c; continue; }

        const auto& v = dag[u];

        seen.reset();
        if (connected(v[0], v[2], clr[v[0]], clr[v[2]])) {
            clr[u] = clr[v[1]];
            swap_color(v[1], clr[v[1]], clr[v[3]]);
        }
        else {
            clr[u] = clr[v[0]];
            swap_color(v[0], clr[v[0]], clr[v[2]]);
        }
    }

    for (int u = 1; u <= n; ++u) cout << clr[u] << '\n';
    return 0;
}
