/*
 * ICPC, Regionals, Northern Eurasia, Northern Eurasia Finals 2018 K. King Kog's Reception
 * BOJ 16670 - lazy segment tree
 * Date: 2023.8.26
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;

class lazy_seg_tree {
    int N, lgN;
    vector<i64> ar;
    vector<i64> lz;

    void apply(int i, i64 x) {
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
    lazy_seg_tree(): N(1<<20), lgN(20) {
        ar.resize(N<<1); iota(ar.begin() + N, ar.end(), 0);
        lz.resize(N, 0);
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
    i64 query(int i, int j) {
        i |= N, j |= N;
        for (int k = lgN; k; --k) {
            if (    i>>k<<k !=   i) push(i>>k);
            if ((j+1)>>k<<k != j+1) push(j>>k);
        }
        i64 ans = 0;
        for (int l = i, r = j; l <= r; l >>= 1, r >>= 1) {
            if ( l&1) ans = max(ans, ar[l++]);
            if (~r&1) ans = max(ans, ar[r--]);
        }
        return ans;
    }
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);

    lazy_seg_tree segt;

    int Q; cin >> Q;
    vector<pair<int, int> > log(Q+1);

    for (int q = 1; q <= Q; ++q) {
        char op; cin >> op;
        if (op == '+') {
            int t, d; cin >> t >> d;
            log[q] = {t, d};
            segt.add(0, t, d);
        } else if (op == '-') {
            int i; cin >> i;
            const auto& [t, d] = log[i];
            segt.add(0, t, -d);
        } else {
            int t; cin >> t;
            cout << segt.query(0, t) - segt.query(t+1, t+1) + 1 << '\n';
        }
    }

    return 0;
}
