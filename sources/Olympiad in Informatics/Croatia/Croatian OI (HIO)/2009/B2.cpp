/*
 * Croatian Highschool Competitions in Informatics, 2009, Croatian Olympiad in Informatics 2009 B. OTOCI (modified)
 * BOJ 2927 - HLD, disjoint sets, segment tree
 * Date: 2024.1.13
 */

#include<bits/stdc++.h>
using namespace std;

array<vector<int>, 30001> adj;
array<int,30001> dep, par, sz, ch_no, ch_dep, segt_idx;

int dfs(int pu, int u) {
    dep[u] = dep[pu] + 1;
    par[u] = pu;
    sz[u]  = 1;
    for (int& v : adj[u]) if (v != pu)
        sz[u] += dfs(u, v);
    return sz[u];
}
void hld(int u, int cn, int cd, int& si) {
    ch_no[u]    = cn;
    ch_dep[u]   = cd;
    segt_idx[u] = si++;

    int hv = 0;
    for (int& v : adj[u])
        if (v != par[u] && (sz[hv] < sz[v]))
            hv = v;
    if (hv)
        hld(hv, cn, cd, si);
    for (int& v : adj[u])
        if (v != par[u] && v != hv)
            hld(v, v, cd+1, si);
}

class disjoint_sets {
    vector<int> ar;
    int find(int x) {
        return ar[x] < 0? x : ar[x] = find(ar[x]);
    }
public:
    disjoint_sets(int n): ar(n, -1) {}
    void init() { fill(ar.begin(), ar.end(), -1); }
    bool connected(int x, int y) {
        return find(x) == find(y);
    }
    bool link(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y) return false;
        if (ar[x] < ar[y]) ar[y] = x;
        else {
            if (ar[x] == ar[y]) ar[y]--;
            ar[x] = y;
        }
        return true;
    }
};

class seg_tree {
    vector<int> ar;
    int n;
public:
    seg_tree(const vector<int>& cnt) {
        int sz = cnt.size();
        n = 1; while (n < sz) n <<= 1;
        ar.resize(n<<1);
        copy(cnt.begin(), cnt.end(), ar.begin() + n);
        for (int i = n-1; i > 0; --i) ar[i] = ar[i<<1] + ar[i<<1|1];
    }
    void update(int i, int v) {
        ar[i |= n] = v;
        for (; i > 1; i >>= 1) ar[i>>1] = ar[i] + ar[i^1];
    }
    int query(int i, int j) {
        int ans = 0;
        for (i |= n, j |= n; i <= j; i >>= 1, j >>= 1) {
            if ( i&1) ans += ar[i++];
            if (~j&1) ans += ar[j--];
        }
        return ans;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int N; cin >> N;
    vector<int> cnt(N+1);
    for (int u = 1; u <= N; ++u) cin >> cnt[u];

    int M; cin >> M;
    struct query { int op, a, b; };
    vector<query> queries(M);

    disjoint_sets dsu(N+1);
    for (auto& [op, a, b] : queries) {
        string str;
        cin >> str >> a >> b;
        switch (str[0]) {
            case 'b':
                op = 0;
                if (dsu.link(a, b)) {
                    adj[a].emplace_back(b);
                    adj[b].emplace_back(a);
                }
                break;
            case 'p':
                op = 1;
                break;
            case 'e':
                op = 2;
        }
    }

    dep[0] = 0;
    sz.fill(0);
    for (int u = 1; u <= N; ++u) if (!sz[u]) dfs(0, u);
    ch_no.fill(0);
    int si = 0;
    for (int u = 1; u <= N; ++u) if (!ch_no[u]) hld(u, u, 0, si);

    vector<int> ncnt(N);
    for (int u = 1; u <= N; ++u) ncnt[segt_idx[u]] = cnt[u];
    seg_tree segt(ncnt);
    dsu.init();

    for (auto& [op, a, b] : queries) {
        switch (op) {
            case 0:
                cout << (dsu.link(a, b) ? "yes\n" : "no\n");
                break;
            case 1:
                segt.update(segt_idx[a], b);
                break;
            case 2:
                if (dsu.connected(a, b)) {
                    int ans = 0;
                    while (ch_no[a] != ch_no[b]) {
                        if (ch_dep[a] > ch_dep[b]) swap(a, b);
                        ans += segt.query(segt_idx[ch_no[b]], segt_idx[b]);
                        b = par[ch_no[b]];
                    }
                    if (dep[a] > dep[b]) swap(a, b);
                    ans += segt.query(segt_idx[a], segt_idx[b]);
                    cout << ans << '\n';
                }
                else cout << "impossible\n";
        }
    }

    return 0;
}
