/*
 * Central Europe Olympiad in Informatics, CEOI 2019, Day 1 B. Dynamic Diameter
 * BOJ 17642 - Euler tour technique, lazy segment tree
 * Date: 2024.2.14
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;

class lazy_seg_tree {
    struct node {
        i64 v0, v1, v2, v3, v4;
        bool valid;
        node(): v0{0}, v1{0}, v2{0}, v3{0}, v4{0}, valid{false} {}
    };
    int n, lgn;
    vector<node> ar;
    vector<i64> lz;

    void apply(int i, i64 x) {
        ar[i].v0 += x;
        ar[i].v1 -= 2*x;
        ar[i].v2 -= x;
        ar[i].v3 -= x;
        if (i < n) lz[i] += x;
    }
    void push(int i) {
        apply(i<<1,   lz[i]);
        apply(i<<1|1, lz[i]);
        lz[i] = 0;
    }
    node merge(const node& a, const node& b) {
        if (!b.valid) return a;
        node c;
        c.v0 = max(a.v0, b.v0);
        c.v1 = max(a.v1, b.v1);
        c.v2 = max({a.v2, b.v2, a.v0 + b.v1});
        c.v3 = max({a.v3, b.v3, a.v1 + b.v0});
        c.v4 = max({a.v4, b.v4, a.v0 + b.v3, a.v2 + b.v0});
        c.valid = true;
        return c;
    }
    void pull(int i) { ar[i] = merge(ar[i<<1], ar[i<<1|1]); }
public:
    void resize(int sz) {
        n = 1; lgn = 0; while (n < sz) { n <<= 1; ++lgn; }
        ar.resize(n<<1);
        lz.resize(n);
    }
    void init_set(int i, i64 x) {
        ar[i|n].valid = true;
        apply(i|n, x);
    }
    void init_build() { for (int i = n-1; i; --i) pull(i); }
    void add(int i, int j, i64 x) {
        i |= n, j |= n;
        for (int k = lgn; k; --k) {
            if (    i>>k<<k !=   i) push(i>>k);
            if ((j+1)>>k<<k != j+1) push(j>>k);
        }
        for (int l = i, r = j; l <= r; l >>= 1, r >>= 1) {
            if ( l&1) apply(l++, x);
            if (~r&1) apply(r--, x);
        }
        for (int k = 1; k <= lgn; ++k) {
            if     (i>>k<<k !=   i) pull(i>>k);
            if ((j+1)>>k<<k != j+1) pull(j>>k);
        }
    }
    i64 query() { return ar[1].v4; }
} segt;

struct edg_ { int x, y; i64 w; } edg[100005];
vector<pair<int, i64> > adj[100005];
array<int, 100005> par, st, fi;

void dfs(int px, int x, i64 d, int& clk) {
    par[x] = px;
    st[x] = clk++;
    segt.init_set(st[x], d);
    for (const auto& [y, w] : adj[x]) if (y != px) {
        dfs(x, y, d + w, clk);
        segt.init_set(clk++, d);
    }
    fi[x] = clk-1;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, q; i64 mod_w; cin >> n >> q >> mod_w;
    for (int i = 0; i < n-1; ++i) {
        auto& [x, y, w] = edg[i]; cin >> x >> y >> w;
        adj[x].emplace_back(y, w);
        adj[y].emplace_back(x, w);
    }

    segt.resize(2*n - 1);
    int clk = 0; dfs(0, 1, 0, clk);
    segt.init_build();
    for (int i = 0; i < n-1; ++i) {
        auto& [x, y, w] = edg[i];
        if (x == par[y]) swap(x, y);
    }

    i64 id, nw, ans = 0;
    while (q--) {
        cin >> id >> nw;
        id = (id + ans) % (n-1);
        nw = (nw + ans) % mod_w;

        int x = edg[id].x;
        i64 delta = nw - edg[id].w;
        edg[id].w = nw;
        segt.add(st[x], fi[x], delta);
        ans = segt.query();
        cout << ans << '\n';
    }

    return 0;
}
