/*
 * 트리와 쿼리 1
 * QOJ 18804
 *
 * HLD, segment tree
 * Date: 2026.7.2
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;
using ii = pair<int, int>;
const int MAXN = 1e5 +4;

struct edge { int x, y, w; } edges[MAXN];
vector<int> gph[MAXN];
array<int, MAXN> par, sz, ch_id, ch_dep, ch_pos, st_idx;

class seg_tree {
    int N;
    vector<int> ar;

public:
    seg_tree(int n) {
        N = 1; while (N < n) N *= 2;
        ar.assign(2*N, 0);
    }
    void update(int i, int w) {
        ar[i |= N] = w;
        for (; i > 1; i >>= 1) ar[i>>1] = max(ar[i], ar[i^1]);
    }
    int query(int i, int j) {
        int ret = 0;
        for (i |= N, j |= N; i <= j; i >>= 1, j >>= 1) {
            if ( i&1) ret = max(ret, ar[i++]);
            if (~j&1) ret = max(ret, ar[j--]);
        }
        return ret;
    }
};

int dfs(int px, int x) {
    par[x] = px;
    sz[x] = 1;
    for (int y : gph[x]) if (y != px) sz[x] += dfs(x, y);
    return sz[x];
}

void hld(int x, int ci, int cd, int cp) {
    static int clk = 0;
    ch_id[x] = ci;
    ch_dep[x] = cd;
    ch_pos[x] = cp;
    st_idx[x] = clk++;

    int hy = 0;
    for (int y : gph[x]) if (y != par[x] && (!hy || sz[y] > sz[hy])) hy = y;
    if (hy) hld(hy, ci, cd, cp+1);
    for (int y : gph[x]) if (y != par[x] && y != hy) hld(y, y, cd+1, 0);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n; cin >> n;
    for (int i = 1; i < n; ++i) {
        int x, y, w; cin >> x >> y >> w;
        gph[x].push_back(y);
        gph[y].push_back(x);
        edges[i] = { x, y, w };
    }

    par[1] = 0;
    sz[0] = 0;

    dfs(0, 1);
    hld(1, 1, 0, 0);

    seg_tree segt(n);

    for (int i = 1; i < n; ++i) {
        auto& [x, y, w] = edges[i];

        if (ch_id[x] != ch_id[y]) {
            if (ch_dep[x] > ch_dep[y]) swap(x, y);
        }
        else if (ch_pos[x] > ch_pos[y]) swap(x, y);
        segt.update(st_idx[y], w);
    }

    int m; cin >> m;
    while (m--) {
        int q; cin >> q;

        if (q&1) {
            int i, w; cin >> i >> w;
            segt.update(st_idx[edges[i].y], w);
        }
        else {
            int x, y; cin >> x >> y;
            int ans = 0;

            while (ch_id[x] != ch_id[y]) {
                if (ch_dep[x] > ch_dep[y]) swap(x, y);
                ans = max(ans, segt.query(st_idx[ch_id[y]], st_idx[y]));
                y = par[ch_id[y]];
            }
            if (ch_pos[x] > ch_pos[y]) swap(x, y);
            ans = max(ans, segt.query(st_idx[x]+1, st_idx[y]));
            cout << ans << '\n';
        }
    }

    return 0;
}
