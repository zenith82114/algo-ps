/*
 * Baltic Olympiad in Informatics, BOI 2009 Day 2 B. Triangulation
 * BOJ 3351
 *
 * tree DP, LCA
 * Date: 2024.1.13
 */

#include<bits/stdc++.h>
using namespace std;
constexpr int MAXN = 100'004;

vector<pair<int, int> > edg;
int chk[MAXN*2];
int tri[MAXN][3];
vector<int> clr[MAXN];

vector<int> tree[MAXN];
int sz[MAXN], dfn[MAXN], dep[MAXN] {0};
int rmq[18][MAXN*2];

void dfs1(int px, int x, int& clk) {
    sz[x] = 1;
    dfn[x] = clk;
    dep[x] = dep[px] + 1;
    rmq[0][clk++] = x;
    for (int y : tree[x]) if (y != px) {
        dfs1(x, y, clk);
        sz[x] += sz[y];
        rmq[0][clk++] = x;
    }
}

int lca(int x, int y) {
    int l = dfn[x], r = dfn[y]; if (l > r) swap(l, r);
    int d = r - l + 1;
    int i = 17; while (~d & (1<<i)) --i;
    int x1 = rmq[i][l], x2 = rmq[i][r - (1<<i) + 1];
    return dep[x1] < dep[x2]? x1 : x2;
}

void dfs2(int px, int x) {
    for (int y : tree[x]) if (y != px) {
        dfs2(x, y);
        chk[x] += chk[y];
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n; cin >> n; n -= 2;
    for (int x = 1; x <= n; ++x) {
        auto v = tri[x]; int c;
        cin >> v[0] >> v[1] >> v[2] >> c;
        clr[c].emplace_back(x);
        sort(v, v+3);
        edg.emplace_back(v[0], v[1]);
        edg.emplace_back(v[0], v[2]);
        edg.emplace_back(v[1], v[2]);
    }
    sort(edg.begin(), edg.end());
    edg.erase(unique(edg.begin(), edg.end()), edg.end());
    for (int x = 1; x <= n; ++x) {
        auto v = tri[x]; int e;
        e = lower_bound(edg.begin(), edg.end(), make_pair(v[0], v[1])) - edg.begin();
        if (!chk[e]) chk[e] = x;
        else {
            tree[x].emplace_back(chk[e]);
            tree[chk[e]].emplace_back(x);
        }
        e = lower_bound(edg.begin(), edg.end(), make_pair(v[0], v[2])) - edg.begin();
        if (!chk[e]) chk[e] = x;
        else {
            tree[x].emplace_back(chk[e]);
            tree[chk[e]].emplace_back(x);
        }
        e = lower_bound(edg.begin(), edg.end(), make_pair(v[1], v[2])) - edg.begin();
        if (!chk[e]) chk[e] = x;
        else {
            tree[x].emplace_back(chk[e]);
            tree[chk[e]].emplace_back(x);
        }
    }

    int clk = 0; dfs1(0, 1, clk);

    for (int i = 1; i < 18; ++i)
    for (int j = 0; j + (1<<i>>1) < 2*n; ++j) {
        int x1 = rmq[i-1][j], x2 = rmq[i-1][j + (1<<i>>1)];
        rmq[i][j] = dep[x1] < dep[x2]? x1 : x2;
    }

    fill_n(chk+1, n, 0);
    for (int c = 1; c <= n+2; ++c) if (clr[c].size()) {
        int x = clr[c].front();
        for (int y : clr[c]) x = lca(x, y);
        chk[x] += clr[c].size();
    }

    dfs2(0, 1);

    int ans = 0;
    for (int x = 2; x <= n; ++x) if (chk[x] == sz[x]) ++ans;
    cout << ans;
    return 0;
}
