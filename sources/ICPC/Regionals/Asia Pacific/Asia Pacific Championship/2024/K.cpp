/*
 * ICPC, Regionals, Asia Pacific,
 * The 2024 ICPC Asia Pacific Championship K. Tree Quiz
 * BOJ 31603
 * JUNGOL 10914
 *
 * Euler tour, persistent segment tree
 * Date: 2025.7.3
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;

class persistent_seg_tree {
    struct node { int l = 0, r = 0, sum = 0; };
    int _n;
    vector<node> _nd;
    vector<int> _rt;

    int add_util(int p, int s, int e, int i) {
        _nd.emplace_back(_nd[p]);
        int u = _nd.size() - 1;
        if (s == e) _nd[u].sum = 1;
        else {
            int mid = (s + e)/2;
            if (i <= mid) _nd[u].l = add_util(_nd[p].l, s, mid, i);
            else _nd[u].r = add_util(_nd[p].r, mid + 1, e, i);
            _nd[u].sum = _nd[_nd[u].l].sum + _nd[_nd[u].r].sum;
        }
        return u;
    }
    int kth_util(int u1, int v1, int u2, int v2, int s, int e, int k) {
        if (s == e) return s;
        int mid = (s + e)/2;
        int b = _nd[_nd[v1].l].sum - _nd[_nd[u1].l].sum
            + _nd[_nd[v2].l].sum - _nd[_nd[u2].l].sum;
        return (k <= b
            ? kth_util(_nd[u1].l, _nd[v1].l, _nd[u2].l, _nd[v2].l, s, mid, k)
            : kth_util(_nd[u1].r, _nd[v1].r, _nd[u2].r, _nd[v2].r, mid + 1, e, k - b)
        );
    }
public:
    void init(int n) {
        _n = n;
        _nd.emplace_back();
        _rt.emplace_back(0);
    }
    void add(int i) {
        _rt.emplace_back(add_util(_rt.back(), 1, _n, i));
    }
    int kth(int t1, int t2, int k) {
        return kth_util(0, 0, _rt[t1 - 1], _rt[t2], 1, _n, k);
    }
    int kth(int t1, int t2, int t3, int t4, int k) {
        return kth_util(_rt[t1 - 1], _rt[t2], _rt[t3 - 1], _rt[t4], 1, _n, k);
    }
} psegt;

class seg_tree {
    int _n;
    vector<int> _a;
public:
    void init(int n) {
        _n = 1; while (_n <= n) _n *= 2;
        _a.resize(2*_n);
    }
    void upd(int i, int x) {
        for (_a[i |= _n] = x; i > 1; i /= 2) _a[i/2] = _a[i] + _a[i^1];
    }
    void kth(int& x, int& k) {
        int u = 1, s = 0, e = _n - 1;
        while (s < e) {
            int mid = (s + e)/2;
            if (_a[2*u] >= k) u = 2*u, e = mid;
            else k -= _a[2*u], u = 2*u + 1, s = mid + 1;
        }
        x = s;
    }
} segt;

int n;
vector<int> chd[100004];
array<int, 100004> sz, ord, nxt;
int clk = 0;
vector<pair<int, int> > que[100004];
i64 ans[100004];

void dfs1(int x) {
    sz[x] = 1;
    ord[x] = ++clk;
    psegt.add(x);
    for (int y : chd[x]) dfs1(y), sz[x] += sz[y];
}

void dfs2(int x) {
    segt.upd(x, sz[x]);
    for (auto& [id, k] : que[x]) {
        int z = 0; segt.kth(z, k);
        ans[id] += 1ll * (z - 1) * n;
        if (z == x) ans[id] += psegt.kth(ord[x], ord[x] + sz[x] - 1, k) - 1;
        else ans[id] += psegt.kth(
            ord[z], ord[nxt[z]] - 1,
            ord[nxt[z]] + sz[nxt[z]], ord[z] + sz[z] - 1, k) - 1;
    }
    for (int y : chd[x]) {
        segt.upd(x, sz[x] - sz[y]);
        nxt[x] = y;
        dfs2(y);
    }
    nxt[x] = 0;
    segt.upd(x, 0);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int q; cin >> n >> q;
    int root = 0;
    for (int x = 1; x <= n; ++x) {
        int px; cin >> px;
        if (!px) root = x;
        else chd[px].emplace_back(x);
    }
    for (int id = 0; id < q; ++id) {
        i64 k; cin >> k;
        int x = (k - 1) / n + 1;
        ans[id] = 1ll * (x - 1) * n * n;
        que[x].emplace_back(id, k - 1ll * (x - 1) * n);
    }

    psegt.init(n);
    dfs1(root);
    segt.init(n);
    dfs2(root);
    for (int i = 0; i < q; ++i) cout << ans[i] << '\n';
    return 0;
}
