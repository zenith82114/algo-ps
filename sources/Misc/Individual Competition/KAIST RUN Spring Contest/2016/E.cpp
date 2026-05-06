/*
 * 2016 Spring RUN@KAIST Programming Contest E. Traffic
 * BOJ 12746 - difference array, LCA
 * Date: 2024.10.7
 */

#include<bits/stdc++.h>
using namespace std;

constexpr int MAXN = 300000;
vector<int> g[MAXN];
int dfn[MAXN], dep[MAXN] {}, ps[MAXN] {};
int rmq[20][2 * MAXN];

void dfs1(int px, int x, int& clk) {
    dfn[x] = clk;
    dep[x] = dep[px] + 1;
    rmq[0][clk++] = x;
    for (int y : g[x]) if (y != px) {
        dfs1(x, y, clk);
        rmq[0][clk++] = x;
    }
}

int lca(int x, int y) {
    int l = dfn[x], r = dfn[y]; if (l > r) swap(l, r);
    int d = r - l + 1;
    int i = 20; while (~d & (1<<i)) --i;
    int x1 = rmq[i][l], x2 = rmq[i][r - (1<<i) + 1];
    return dep[x1] < dep[x2]? x1 : x2;
}

int ans = 0;
pair<int, int> anse {MAXN, MAXN};

void dfs2(int px, int x) {
    for (int y : g[x]) if (y != px) {
        dfs2(x, y);
        ps[x] += ps[y];
    }
    auto e = make_pair(min(px, x), max(px, x));
    if (ans < ps[x]) {
        ans = ps[x];
        anse = e;
    }
    else if (ans == ps[x]) {
        anse = min(anse, e);
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, q; cin >> n >> q;
    for (int _ = 1; _ < n; ++_) {
        int x, y; cin >> x >> y;
        g[x].emplace_back(y);
        g[y].emplace_back(x);
    }

    int clk = 0; dfs1(0, 1, clk);

    for (int i = 1; i < 20; ++i)
    for (int j = 0; j + (1<<i>>1) < 2*n; ++j) {
        int x1 = rmq[i - 1][j], x2 = rmq[i - 1][j + (1<<i>>1)];
        rmq[i][j] = dep[x1] < dep[x2]? x1 : x2;
    }

    while (q--) {
        int x, y; cin >> x >> y;
        ++ps[x]; ++ps[y]; ps[lca(x, y)] -= 2;
    }

    dfs2(0, 1);
    cout << anse.first << ' ' << anse.second << ' ' << ans;

    return 0;
}
