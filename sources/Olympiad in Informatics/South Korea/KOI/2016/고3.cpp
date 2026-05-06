/*
 * 한국정보올림피아드, KOI 2016, 고등부 3. 트리
 * BOJ 13309
 * JUNGOL 3000
 *
 * Euler tour, LCA, segment tree
 * Date: 2025.7.18
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;
constexpr int MAXN = 2e5 + 4, MAXLOGN = 18;

class seg_tree {
    vector<int> tr;
    int n;
public:
    seg_tree(int sz) {
        n = 1; while (n < sz) n *= 2;
        tr.resize(2*n);
    }
    void upd(int i, int x) {
        tr[i |= n] = x;
        for (; i > 1; i /= 2) tr[i/2] = tr[i] + tr[i^1];
    }
    int qry(int j) {
        int i = n; j |= n;
        int ans = 0;
        for (; i <= j; i /= 2, j /= 2) {
            if ( i&1) ans += tr[i++];
            if (~j&1) ans += tr[j--];
        }
        return ans;
    }
};

vector<int> g[MAXN];
int rmq[MAXLOGN + 1][2 * MAXN];
array<int, MAXN> dep, ts, te;

void dfs(int x, int& clk) {
    ts[x] = clk;
    rmq[0][clk++] = x;
    for (int y : g[x]) {
        dep[y] = dep[x] + 1;
        dfs(y, clk);
        rmq[0][clk++] = x;
    }
    te[x] = clk;
}

int lca(int x, int y) {
    int l = ts[x], r = ts[y]; if (l > r) swap(l, r);
    int t = r - l + 1;
    int i = MAXLOGN; while (~t & (1<<i)) --i;
    int x1 = rmq[i][l], x2 = rmq[i][r - (1<<i) + 1];
    return dep[x1] < dep[x2]? x1 : x2;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, q; cin >> n >> q;
    for (int x = 2; x <= n; ++x) {
        int px; cin >> px;
        g[px].emplace_back(x);
    }
    dep[1] = 0;
    int clk = 0; dfs(1, clk);

    for (int i = 1; i <= MAXLOGN; ++i)
    for (int j = 0; j + (1<<i>>1) < 2*n; ++j) {
        int x1 = rmq[i - 1][j], x2 = rmq[i - 1][j + (1<<i>>1)];
        rmq[i][j] = dep[x1] < dep[x2]? x1 : x2;
    }

    seg_tree segt(2*n);

    while (q--) {
        int x, y, op; cin >> x >> y >> op;
        int r = segt.qry(ts[x]) + segt.qry(ts[y]) - 2*segt.qry(ts[lca(x, y)]);
        cout << (r? "NO" : "YES") << '\n';
        if (op) {
            int z = r? y : x;
            segt.upd(ts[z], +1);
            segt.upd(te[z], -1);
        }
    }

    return 0;
}
