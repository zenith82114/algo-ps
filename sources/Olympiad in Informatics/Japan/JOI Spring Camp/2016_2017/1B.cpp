/*
 * JOI 2016/2017 Spring Camp Day 1 B. Port Facility
 * QOJ 361
 *
 * segment tree, bipartite graph recognition
 * Date: 2026.6.14
 */

#include<bits/stdc++.h>
using namespace std;
using ii = pair<int, int>;
const int MOD = 1e9 + 7;

class seg_tree {
    ii (*comp)(const ii&, const ii&);
    vector<ii> ar;
    int n, nil;
public:
    seg_tree(int sz, int val, ii (*func)(const ii&, const ii&))
    : comp{func}, nil{val} {
        n = 1; while (n < sz) n <<= 1;
        ar.resize(n<<1, ii(nil, -1));
    }
    void ins(int i, ii x) {
        ar[i |= n] = x;
        for (i >>= 1; i; i >>= 1) {
            ar[i] = comp(ar[i<<1], ar[i<<1|1]);
        }
    }
    void del(int i) {
        ar[i |= n] = ii(nil, -1);
        for (i >>= 1; i; i >>= 1) {
            ar[i] = comp(ar[i<<1], ar[i<<1|1]);
        }
    }
    ii qry(int i, int j) {
        ii ans(nil, -1);
        for (i |= n, j |= n; i <= j; i >>= 1, j >>= 1) {
            if ( i&1) ans = comp(ans, ar[i++]);
            if (~j&1) ans = comp(ans, ar[j--]);
        }
        return ans;
    }
};

ii ii_min(const ii& a, const ii& b) { return min(a, b); }
ii ii_max(const ii& a, const ii& b) { return max(a, b); }

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n; cin >> n;
    vector<int> seq(2*n), L(n), R(n);
    for (int i = 0; i < n; ++i) {
        cin >> L[i] >> R[i];
        seq[--L[i]] = i;
        seq[--R[i]] = i;
    }

    seg_tree max_segt(2*n, INT32_MIN, ii_max);
    seg_tree min_segt(2*n, INT32_MAX, ii_min);

    for (int i = 0; i < n; ++i) {
        max_segt.ins(L[i], ii(R[i], i));
        min_segt.ins(R[i], ii(L[i], i));
    }

    stack<int> stk;
    vector<int> vis(n);
    int ans = 1;

    for (int i = 0; i < n; ++i) if (!vis[i]) {
        ans = (ans<<1)%MOD;

        stk.emplace(i); vis[i] = 1;
        max_segt.del(L[i]);
        min_segt.del(R[i]);
        while (!stk.empty()) {
            int x = stk.top();
            auto [yr, y] = max_segt.qry(L[x], R[x]);
            if (R[x] < yr) {
                stk.emplace(y); vis[y] = vis[x]^3;
                max_segt.del(L[y]);
                min_segt.del(R[y]);
                continue;
            }
            auto [zl, z] = min_segt.qry(L[x], R[x]);
            if (zl < L[x]) {
                stk.emplace(z); vis[z] = vis[x]^3;
                max_segt.del(L[z]);
                min_segt.del(R[z]);
                continue;
            }
            stk.pop();
        }
    }

    for (int x : seq) if (vis[x] & 1) {
        if (stk.empty() || stk.top() != x) stk.emplace(x);
        else stk.pop();
    }
    if (!stk.empty()) { cout << 0; return 0; }
    for (int x : seq) if (vis[x] & 2) {
        if (stk.empty() || stk.top() != x) stk.emplace(x);
        else stk.pop();
    }
    if (!stk.empty()) { cout << 0; return 0; }
    cout << ans;
    return 0;
}
