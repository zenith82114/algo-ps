/*
 * 트리와 쿼리 6
 * QOJ 18809
 *
 * HLD, BBST, centroid DnC
 * Date: 2024.5.11
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;
using ii = pair<int, int>;
const int MAXN = 1e5 +4;

array<vector<int>, MAXN> gph;
array<int, MAXN> par, sz, ch_no, vis, ivis;
bitset<MAXN> color; // 0,1 = B,W
set<int> color_set[MAXN][2];

class seg_tree {
    int N;
    vector<int> ar;

public:
    void init(int sz) {
        for (N = 1; N < sz; N *= 2);
        ar.resize(2*N, 0);
    }
    void add(int x, int y, int d) {
        for (int i = N|vis[x], j = N|vis[y]; i <= j; i >>= 1, j >>= 1) {
            if ( i&1) ar[i++] += d;
            if (~j&1) ar[j--] += d;
        }
    }
    int query(int x) {
        int ans = 0;
        for (int i = N|vis[x]; i; i >>= 1) ans += ar[i];
        return ans;
    }
} segt[2];

int dfs(int px, int x) {
    par[x] = px;
    sz[x] = 1;
    for (int y : gph[x]) if (y != px) sz[x] += dfs(x, y);
    return sz[x];
}

void hld(int x, int cn) {
    static int clk = 0;
    ch_no[x] = cn;
    vis[x] = clk++;
    ivis[vis[x]] = x;

    int hy = 0;
    for (int y : gph[x]) {
        if (y != par[x] && sz[hy] < sz[y]) hy = y;
    }
    if (hy) hld(hy, cn);
    for (int y : gph[x]) {
        if (y != par[x] && y != hy) hld(y, y);
    }
}

int top(int x) {
    int k = !color[x];
    for (int y = x, cy = 0; y; y = par[cy]) {
        cy = ch_no[y];
        auto& s = color_set[cy][k];
        if (s.size()) {
            auto lb = s.lower_bound(vis[y]);
            if (lb != s.begin()) return ivis[*prev(lb) + 1];
        }
        if (par[cy] && color[par[cy]] == k) return cy;
    }
    return 1;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n; cin >> n;
    for (int i = 1; i < n; ++i) {
        int x, y; cin >> x >> y;
        gph[x].emplace_back(y);
        gph[y].emplace_back(x);
    }
    sz[0] = 0;
    dfs(0, 1);
    hld(1, 1);

    segt[0].init(n);
    segt[1].init(n);
    for (int x = 1; x <= n; ++x) {
        color_set[ch_no[x]][0].emplace(vis[x]);
        segt[0].add(x, x, sz[x]);
        segt[1].add(x, x, 1);
    }

    int m; cin >> m;
    while (m--) {
        int op, x; cin >> op >> x;
        if (op&1) {
            int k = !color[x];

            if (x != 1 && color[par[x]] != k) {
                int y = par[top(x)]; if (!y) y = 1;
                int z = par[x];

                int delta = -segt[k^1].query(x);
                for (; ch_no[z] != ch_no[y]; z = par[ch_no[z]]) {
                    segt[k^1].add(ch_no[z], z, delta);
                }
                segt[k^1].add(y, z, delta);

                delta = segt[k].query(x);
                segt[k].add(par[x], par[x], delta);
            }

            color.flip(x);
            color_set[ch_no[x]][k].emplace(vis[x]);
            color_set[ch_no[x]][k^1].erase(vis[x]);

            if (x != 1 && color[par[x]] == k) {
                int y = par[top(x)]; if (!y) y = 1;
                int z = par[x];

                int delta = segt[k].query(x);
                for (; ch_no[z] != ch_no[y]; z = par[ch_no[z]]) {
                    segt[k].add(ch_no[z], z, delta);
                }
                segt[k].add(y, z, delta);

                delta = -segt[k^1].query(x);
                segt[k^1].add(par[x], par[x], delta);
            }
        } else {
            cout << segt[color[x]].query(top(x)) << '\n';
        }
    }

    return 0;
}
