/*
 * 트리와 쿼리 10
 * QOJ 18813
 *
 * HLD, maximum subarray sum segment tree
 * Date: 2024.6.11
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;
using ii = pair<int, int>;
const int MAXN = 1e5 +4;

struct node {
    int ts, ls, rs, ms;
    bool valid;
    node(): ts(0), ls(0), rs(0), ms(0), valid(false) {}
    node(int ts, int ls, int rs, int ms, bool valid)
    : ts(ts), ls(ls), rs(rs), ms(ms), valid(valid) {}
};

node merge(const node& a, const node& b) {
    if (!a.valid) return b;
    if (!b.valid) return a;
    return node(
        a.ts + b.ts,
        max(a.ls, a.ts + b.ls),
        max(a.rs + b.ts, b.rs),
        max({a.ms, b.ms, a.rs + b.ls}),
        true
    );
}

class lazy_seg_tree {
    int N, lgN;
    vector<node> ar;
    vector<int> lz, len;

    void _apply(int i, int x) {
        ar[i].ts = len[i] * x;
        ar[i].ls = ar[i].rs = ar[i].ms = max(0, ar[i].ts);
        if (i < N) lz[i] = x;
    }
    void _push(int i) {
        if (lz[i] == 0xdead) return;
        _apply(i<<1,   lz[i]);
        _apply(i<<1|1, lz[i]);
        lz[i] = 0xdead;
    }
    void _pull(int i) { ar[i] = merge(ar[i<<1], ar[i<<1|1]); }

public:
    lazy_seg_tree(int sz) {
        N = 1; lgN = 0; while (N < sz) { N *= 2; ++lgN; }
        ar.resize(2*N);
        lz.resize(N, 0xdead);
        len.resize(2*N, 1);
        for (int i = N-1; i; --i) len[i] = 2*len[2*i];
    }
    void init_set(int i, int x) {
        ar[i|N].valid = true;
        _apply(i|N, x);
    }
    void init_build() { for (int i = N-1; i; --i) _pull(i); }

    void update(int i, int j, int x) {
        i |= N, j |= N;
        for (int k = lgN; k; --k) {
            if (    i>>k<<k !=   i) _push(i>>k);
            if ((j+1)>>k<<k != j+1) _push(j>>k);
        }
        for (int l = i, r = j; l <= r; l >>= 1, r >>= 1) {
            if ( l&1) _apply(l++, x);
            if (~r&1) _apply(r--, x);
        }
        for (int k = 1; k <= lgN; ++k) {
            if (    i>>k<<k !=   i) _pull(i>>k);
            if ((j+1)>>k<<k != j+1) _pull(j>>k);
        }
    }
    node query(int i, int j) {
        i |= N, j |= N;
        for (int k = lgN; k; --k) {
            if (    i>>k<<k !=   i) _push(i>>k);
            if ((j+1)>>k<<k != j+1) _push(j>>k);
        }
        node tl, tr;
        for (int l = i, r = j; l <= r; l >>= 1, r >>= 1) {
            if ( l&1) tl = merge(tl, ar[l++]);
            if (~r&1) tr = merge(ar[r--], tr);
        }
        return merge(tl, tr);
    }
};

array<vector<int>, MAXN> gph;
array<int, MAXN> par, sz, dep, ch_no, ch_dep, vis;

int dfs(int px, int x) {
    par[x] = px;
    sz[x] = 1;
    dep[x] = dep[px] + 1;
    for (int y : gph[x]) if (y != px) sz[x] += dfs(x, y);
    return sz[x];
}

void hld(int x, int cn, int cd) {
    static int clk = 0;
    ch_no[x] = cn;
    ch_dep[x] = cd;
    vis[x] = clk++;

    int hy = 0;
    for (int y : gph[x]) {
        if (y != par[x] && sz[hy] < sz[y]) hy = y;
    }
    if (hy) hld(hy, cn, cd);
    for (int y : gph[x]) {
        if (y != par[x] && y != hy) hld(y, y, cd+1);
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n; cin >> n;
    vector<int> wgt(n+1);
    for (int x = 1; x <= n; ++x) cin >> wgt[x];

    for (int i = 1; i < n; ++i) {
        int x, y; cin >> x >> y;
        gph[x].push_back(y);
        gph[y].push_back(x);
    }
    sz[0] = dep[0] = 0;
    dfs(0, 1);
    hld(1, 1, 0);

    lazy_seg_tree segt(n);
    for (int x = 1; x <= n; ++x) segt.init_set(vis[x], wgt[x]);
    segt.init_build();

    int m; cin >> m;
    while (m--) {
        int q; cin >> q;
        if (q&1) {
            int x, y; cin >> x >> y;
            node tx, ty;
            while (ch_no[x] != ch_no[y]) {
                if (ch_dep[x] > ch_dep[y]) {
                    tx = merge(segt.query(vis[ch_no[x]], vis[x]), tx);
                    x = par[ch_no[x]];
                } else {
                    ty = merge(segt.query(vis[ch_no[y]], vis[y]), ty);
                    y = par[ch_no[y]];
                }
            }
            if (dep[x] > dep[y]) { swap(x, y); swap(tx, ty); }
            node u = segt.query(vis[x], vis[y]);
            swap(tx.ls, tx.rs);
            cout << merge(tx, merge(u, ty)).ms << '\n';
        } else {
            int x, y, w; cin >> x >> y >> w;
            while (ch_no[x] != ch_no[y]) {
                if (ch_dep[x] > ch_dep[y]) swap(x, y);
                segt.update(vis[ch_no[y]], vis[y], w);
                y = par[ch_no[y]];
            }
            if (dep[x] > dep[y]) swap(x, y);
            segt.update(vis[x], vis[y], w);
        }
    }

    return 0;
}
