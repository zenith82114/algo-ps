/*
 * 한국정보올림피아드, KOI 2013, 고등부 4. 수족관 3
 * BOJ 8987
 * JUNGOL 2637
 *
 * greedy, Euler tour, lazy segment tree
 * Date: 2023.6.14
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;
using ii = pair<int, int>;
using lli = pair<i64, int>;

vector<ii> rp;
vector<i64> val;
vector<int> sz, par;

class RMQ {
    vector<ii> ar;
    int N;
public:
    void init() {
        int sz = rp.size();
        N = 1; while (N < sz) N *= 2;
        ar.resize(2*N);
        for (int i = 0; i < sz; ++i)
            ar[N|i] = { rp[i].second, i };
        for (int i = sz; i < N; ++i)
            ar[N|i] = { INT_MAX, -1 };
        for (int i = N-1; i; --i)
            ar[i] = min(ar[i<<1], ar[i<<1|1]);
    }
    ii query(int i, int j) {
        ii ans { INT_MAX, -1 };
        for (i |= N, j |= N; i <= j; i >>= 1, j >>= 1) {
            if ( i&1) ans = min(ans, ar[i++]);
            if (~j&1) ans = min(ans, ar[j--]);
        }
        return ans;
    }
} rmq;

class lazy_seg_tree {
    int N, lgN;
    int M;
    vector<lli> ar;
    vector<i64> lz;

    void apply(int i, i64 x) {
        ar[i].first += x;
        if (i < N) lz[i] += x;
    }
    void push(int i) {
        apply(i<<1, lz[i]);
        apply(i<<1|1, lz[i]);
        lz[i] = 0;
    }
    void pull(int i) {
        ar[i] = max(ar[i<<1], ar[i<<1|1]);
    }
public:
    lazy_seg_tree(int sz) {
        M = sz;
        for (N = 1, lgN = 0; N < M; N <<= 1, ++lgN);
        ar.resize(N<<1);
        lz.resize(N, 0);

        for (int i = 0; i < M; ++i) ar[N|i].second = i;
        for (int i = M; i < N; ++i) ar[N|i].second = -1;
        for (int i = N-1; i; --i) pull(i);
    }
    void add(int i, int j, i64 x) {
        i |= N, j |= N;
        for (int k = lgN; k; --k) {
            if (    i>>k<<k !=   i) push(i>>k);
            if ((j+1)>>k<<k != j+1) push(j>>k);
        }
        for (int l = i, r = j; l <= r; l >>= 1, r >>= 1) {
            if ( l&1) apply(l++, x);
            if (~r&1) apply(r--, x);
        }
        for (int k = 1; k <= lgN; ++k) {
            if     (i>>k<<k !=   i) pull(i>>k);
            if ((j+1)>>k<<k != j+1) pull(j>>k);
        }
    }
    lli query() {
        const int i = N, j = N|(M-1);
        for (int k = lgN; k; --k) {
            if (    i>>k<<k !=   i) push(i>>k);
            if ((j+1)>>k<<k != j+1) push(j>>k);
        }
        lli ans { 0, -1 };
        for (int l = i, r = j; l <= r; l >>= 1, r >>= 1) {
            if ( l&1) ans = max(ans, ar[l++]);
            if (~r&1) ans = max(ans, ar[r--]);
        }
        return ans;
    }
};

void dfs(int& id, int l, int r, int y_prev) {
    int u = id++;
    auto [y_min, k] = rmq.query(l, r);
    val[u] = (i64)(y_min - y_prev) * (rp[r].first - (l? rp[l-1].first : 0));

    sz[u] = 1;
    if (l < k) {
        int v = id;
        dfs(id, l, k-1, y_min);
        sz[u] += sz[v];
        par[v] = u;
    }
    if (k < r) {
        int v = id;
        dfs(id, k+1, r, y_min);
        sz[u] += sz[v];
        par[v] = u;
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);

    int N; cin >> N;
    int x, y; cin >> x >> y; // (0, 0), ignore
    for (int i = 3; i < N; i += 2) {
        cin >> x >> y >> x >> y;
        rp.emplace_back(x, y);
    }
    cin >> x >> y; // (x_end, 0), ignore
    N = rp.size();

    rmq.init();

    val.resize(N);
    sz .resize(N);
    par.resize(N); par[0] = -1;

    int id = 0; dfs(id, 0, N-1, 0);

    lazy_seg_tree lsegt(N);
    for (int u = 0; u < N; ++u) lsegt.add(u, u + sz[u] - 1, val[u]);

    int K; cin >> K;
    i64 ans = 0;
    while (K--) {
        auto [t, u] = lsegt.query();
        ans += t;
        for (; u != -1 && val[u] != -1; u = par[u]) {
            lsegt.add(u, u + sz[u] - 1, -val[u]);
            val[u] = -1;
        }
    }
    cout << ans;
    return 0;
}
