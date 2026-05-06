/*
 * 한국정보올림피아드, KOI 2014, 고등부 4. 안전한 비상연락망
 * BOJ 10169
 * JUNGOL 2800
 *
 * minimum spanning tree, HLD, segment tree
 * Date: 2026.4.30
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;
using ii = pair<int, int>;
const int MAXN = 1e5 + 4, MAXM = 3e5 + 4;

struct edge {
    int w, id, x, y;
    bool operator<(const edge& other) const {
        return tie(w, id, x, y) < tie(other.w, other.id, other.x, other.y);
    };
};

class disjoint_sets {
    vector<int> ar;
    int _find(int x) {
        if (ar[x] < 0) return x;
        return ar[x] = _find(ar[x]);
    }
public:
    disjoint_sets(int sz): ar(sz, -1) {}
    bool unite(int x, int y) {
        x = _find(x), y = _find(y);
        if (x == y) return false;
        ar[y] = x; return true;
    }
};

array<vector<ii>, MAXN> mst;
array<int, MAXN> par, sz, ch_id, ch_dep, ch_pos, ord;
array<int, MAXM> edge_to_ord;

void dfs(int px, int x) {
    par[x] = px;
    sz[x] = 1;
    for (const auto& [y, i] : mst[x]) if (y != px) {
        dfs(x, y); sz[x] += sz[y];
    }
}

void hld(int x, int ci, int cd, int cp) {
    static int clk = 0;
    ch_id[x] = ci;
    ch_dep[x] = cd;
    ch_pos[x] = cp;
    ord[x] = clk++;

    int hy = 0, hid = 0;
    for (const auto& [y, id] : mst[x]) {
        if (y != par[x] && (!hy || sz[hy] < sz[y])) hy = y, hid = id;
    }
    if (!hy) return;

    hld(hy, ci, cd, cp + 1);
    edge_to_ord[hid] = ord[hy];
    for (const auto& [y, id] : mst[x]) if (y != par[x] && y != hy) {
        hld(y, y, cd + 1, 0);
        edge_to_ord[id] = ord[y];
    }
}

class seg_tree {
    int N;
    vector<int> ar;
public:
    seg_tree(int sz) {
        for (N = 1; N < sz; N *= 2);
        ar.resize(2*N, INT32_MAX);
    }
    void set_min(int l, int r, int x) {
        for (l |= N, r |= N; l <= r; l >>= 1, r >>= 1) {
            if ( l&1) ar[l] = min(ar[l], x), ++l;
            if (~r&1) ar[r] = min(ar[r], x), --r;
        }
    }
    int query(int i) {
        int ans = INT32_MAX;
        for (i |= N; i; i >>= 1) ans = min(ans, ar[i]);
        return ans;
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m; cin >> n >> m;
    vector<edge> edges(m);
    for (int i = 0; i < m; ++i) {
        auto& [w, id, x, y] = edges[i];
        id = i; cin >> x >> y >> w;
    }

    i64 W = 0;
    disjoint_sets dsu(n + 1);
    sort(begin(edges), end(edges));
    for (const auto& [w, id, x, y] : edges) if (dsu.unite(x, y)) {
        W += w;
        mst[x].emplace_back(y, id);
        mst[y].emplace_back(x, id);
    }

    dfs(0, 1);
    edge_to_ord.fill(-1);
    hld(1, 1, 0, 0);

    seg_tree segt(n + 1);
    for (auto [w, id, x, y] : edges) if (edge_to_ord[id] == -1) {
        while (ch_id[x] != ch_id[y]) {
            if (ch_dep[x] > ch_dep[y]) swap(x, y);
            segt.set_min(ord[ch_id[y]], ord[y], w);
            y = par[ch_id[y]];
        }
        if (ch_pos[x] > ch_pos[y]) swap(x, y);
        if (ord[x] < ord[y]) segt.set_min(ord[x] + 1, ord[y], w);
    }

    vector<i64> ans(m, W);
    for (const auto& [w, id, x, y] : edges) if (edge_to_ord[id] != -1) {
        int r = segt.query(edge_to_ord[id]);
        ans[id] = (r != INT32_MAX) ? (W - w + r) : -1;
    }
    for (i64 a : ans) cout << a << '\n';
    return 0;
}
