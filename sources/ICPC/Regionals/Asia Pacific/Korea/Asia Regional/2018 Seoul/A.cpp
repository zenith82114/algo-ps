/*
 * ICPC, Regionals, Asia Pacific, Korea,
 * Asia Regional - Seoul 2018 A. Circuits
 * BOJ 16357
 * JUNGOL 3392
 *
 * sweep line, lazy segment tree
 * Date: 2025.1.4
 */

#include<bits/stdc++.h>
using namespace std;

class lazy_seg_tree {
    int N, lgN;
    vector<int> ar, lz;
    void apply(int i, int x) {
        ar[i] += x;
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
        for (N = 1, lgN = 0; N < sz; N <<= 1, ++lgN);
        ar.resize(N<<1, 0);
        for (int i = N-1; i; --i) ar[i] = ar[i<<1];
        lz.resize(N, 0);
    }
    void add(int i, int j, int x) {
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
            if (    i>>k<<k != i  ) pull(i>>k);
            if ((j+1)>>k<<k != j+1) pull(j>>k);
        }
    }
    int query(int i, int j) {
        i |= N, j |= N;
        for (int k = lgN; k; --k) {
            if (    i>>k<<k !=   i) push(i>>k);
            if ((j+1)>>k<<k != j+1) push(j>>k);
        }
        int ans = 0;
        for (int l = i, r = j; l <= r; l >>= 1, r >>= 1) {
            if ( l&1) ans = max(ans, ar[l++]);
            if (~r&1) ans = max(ans, ar[r--]);
        }
        return ans;
    }
};

int memo[100005];
vector<int> links[200005];
int expire[200005] {};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n; cin >> n;
    vector<pair<int, int> > v;
    for (int i = 0; i < n; ++i) {
        int yh, yl;
        cin >> yh >> yh >> yl >> yl;
        v.emplace_back(yl, i<<1);
        v.emplace_back(yh, i<<1|1);
    }
    sort(v.begin(), v.end());

    lazy_seg_tree segt(2 * n);

    int y_pred = INT_MIN;
    int m = -1;

    for (const auto& [y, id] : v) {
        if (y_pred < y) { y_pred = y; ++m; }
        if (id & 1) {
            int yl = memo[id>>1];
            links[yl].emplace_back(m);
            ++expire[m + 1];
            segt.add(yl, m, 1);
        }
        else memo[id>>1] = m;
    }

    int ans = 0, cnt = 0;
    for (int i = 0; i <= m; ++i) {
        for (int j : links[i]) {
            ++cnt;
            segt.add(i, j, -1);
        }
        cnt -= expire[i];
        ans = max(ans, cnt + segt.query(i, m));
    }

    cout << ans;
    return 0;
}
