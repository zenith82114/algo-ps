/*
 * ICPC Japanese Alumni Group, JAG Spring Contest 2013 E. Parentheses
 * BOJ 10637 - HLD, segment tree
 * Date: 2023.5.11
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;
using ii = pair<int, int>;
using iiii = tuple<int, int, int, int>;

class disjoint_sets {
    int cnt;
    vector<int> ar;
    int find(int x) {
        if (ar[x] < 0) return x;
        return ar[x] = find(ar[x]);
    }
public:
    disjoint_sets(int sz): cnt(0), ar(sz, -1) {}
    bool unite(int x, int y) {
        x = find(x), y = find(y);
        if (x == y) return false;
        ar[y] = x; ++cnt; return true;
    }
    int get_cnt() { return cnt; }
};

array<vector<ii>, 100'001> mst;
array<int, 100'001> par, sz, ch_id, ch_dep, ch_pos, ord;
array<int, 200'000> edge_to_ord;

void dfs(int px, int x) {
    par[x] = px;
    sz[x] = 1;
    for (const auto& [y, i] : mst[x])
        if (y != px) dfs(x, y), sz[x] += sz[y];
}

void hld(int x, int ci, int cd, int cp, int& clk) {
    ch_id[x] = ci;
    ch_dep[x] = cd;
    ch_pos[x] = cp;
    ord[x] = clk++;

    int hy = 0, hi = 0;
    for (const auto& [y, i] : mst[x])
        if (y != par[x] && (!hy || sz[hy] < sz[y])) hy = y, hi = i;
    if (!hy) return;

    hld(hy, ci, cd, cp+1, clk);
    edge_to_ord[hi] = ord[hy];
    for (const auto& [y, i] : mst[x]) if (y != par[x] && y != hy) {
        hld(y, y, cd+1, 0, clk);
        edge_to_ord[i] = ord[y];
    }
}

class seg_tree {
    int N;
    vector<int> ar;
public:
    seg_tree(int sz) {
        for (N = 1; N < sz; N <<= 1);
        ar.resize(N<<1, INT_MAX);
    }
    void set_min(int l, int r, int x) {
        for (l |= N, r |= N; l <= r; l >>= 1, r >>= 1) {
            if ( l&1) ar[l] = min(ar[l], x), ++l;
            if (~r&1) ar[r] = min(ar[r], x), --r;
        }
    }
    int query(int i) {
        int ans = INT_MAX;
        for (i |= N; i; i >>= 1) ans = min(ans, ar[i]);
        return ans;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int N, M; cin >> N >> M;
    vector<iiii> edges(M);
    for (int m = 0; m < M; ++m) {
        auto& [w, i, x, y] = edges[m];
        i = m; cin >> x >> y >> w;
    }

    i64 W = 0;
    disjoint_sets dsu(N+1);
    sort(edges.begin(), edges.end());
    for (const auto& [w, i, x, y] : edges) if (dsu.unite(x, y)) {
        W += w;
        mst[x].emplace_back(y, i);
        mst[y].emplace_back(x, i);
    }
    if (dsu.get_cnt() != N-1) {
        while (M--) cout << "-1\n";
        return 0;
    }

    dfs(0, 1);
    edge_to_ord.fill(-1);
    int clk = 0; hld(1, 1, 0, 0, clk);

    seg_tree segt(N+1);
    for (auto [w, i, x, y] : edges) if (edge_to_ord[i] == -1) {
        while (ch_id[x] != ch_id[y]) {
            if (ch_dep[x] > ch_dep[y]) swap(x, y);
            segt.set_min(ord[ch_id[y]], ord[y], w);
            y = par[ch_id[y]];
        }
        if (ch_pos[x] > ch_pos[y]) swap(x, y);
        if (ord[x] < ord[y]) segt.set_min(ord[x]+1, ord[y], w);
    }

    vector<i64> ans(M, W);
    for (const auto& [w, i, x, y] : edges) if (edge_to_ord[i] != -1) {
        int r = segt.query(edge_to_ord[i]);
        ans[i] = (r != INT_MAX)? (ans[i] - w + r) : -1;
    }
    for (i64 a : ans) cout << a << '\n';
    return 0;
}
