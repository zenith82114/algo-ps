/*
 * ICPC, Regionals, Europe, Central Europe Regional Contest,
 * CERC 2017 I. Intrinsic Interval
 * BOJ 15266
 * JUNGOL 11583
 *
 * lazy segment tree, sweep line
 * Date: 2024.6.13
 */

#include<bits/stdc++.h>
using namespace std;
using ii = pair<int, int>;

class lazy_seg_tree {
    int N, lgN;
    vector<ii> ar;
    vector<int> lz;

    void apply(int i, int x) {
        ar[i].first += x;
        if (~i & N) lz[i] += x;
    }
    void push(int i) {
        apply(i<<1,   lz[i]);
        apply(i<<1|1, lz[i]);
        lz[i] = 0;
    }
    void pull(int i) {
        ar[i] = max(ar[i<<1], ar[i<<1|1]);
    }
public:
    lazy_seg_tree(int sz) {
        for (N = 1, lgN = 0; N < sz; N <<= 1, ++lgN);
        ar.resize(N<<1);
        lz.resize(N);
        for (int i = 0; i < sz; ++i) ar[N|i] = make_pair(i, i);
        for (int i = N-1; i; --i) pull(i);
    }
    void add(int i, int j, int x) {
        i |= N; j |= N;
        for (int k = lgN; k; --k) {
            if (    i>>k<<k !=   i) push(i>>k);
            if ((j+1)>>k<<k != j+1) push(j>>k);
        }
        for (int l = i, r = j; l <= r; l >>= 1, r >>= 1) {
            if ( l&1) apply(l++, x);
            if (~r&1) apply(r--, x);
        }
        for (int k = 1; k <= lgN; ++k) {
            if (    i>>k<<k !=   i) pull(i>>k);
            if ((j+1)>>k<<k != j+1) pull(j>>k);
        }
    }
    ii query(int i, int j) {
        i |= N; j |= N;
        for (int k = lgN; k; --k) {
            if (    i>>k<<k !=   i) push(i>>k);
            if ((j+1)>>k<<k != j+1) push(j>>k);
        }
        ii ret(-1, 0);
        for (int l = i, r = j; l <= r; l >>= 1, r >>= 1) {
            if ( l&1) ret = max(ret, ar[l++]);
            if (~r&1) ret = max(ret, ar[r--]);
        }
        return ret;
    }
};

array<int, 100005> p, ip;
array<vector<ii>, 100005> q;
array<ii, 100005> ans;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n; cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> p[i];
        ip[p[i]] = i;
    }
    int m; cin >> m;
    for (int j = 1; j <= m; ++j) {
        int l, r; cin >> l >> r;
        q[r].emplace_back(l, j);
    }

    lazy_seg_tree segt(n+1);
    priority_queue<ii> pq;
    for (int i = 1; i <= n; ++i) {
        if (p[i] > 1 && ip[p[i]-1] < i) segt.add(1, ip[p[i]-1], 1);
        if (p[i] < n && ip[p[i]+1] < i) segt.add(1, ip[p[i]+1], 1);

        for (const ii& lj : q[i]) pq.emplace(lj);
        while (!pq.empty()) {
            auto [l, j] = pq.top();
            auto [mx, amx] = segt.query(1, l);
            if (mx != i) break;
            ans[j] = make_pair(amx, i);
            pq.pop();
        }
    }

    for (int j = 1; j <= m; ++j) {
        const auto& [l, r] = ans[j];
        cout << l << ' ' << r << '\n';
    }
    return 0;
}
