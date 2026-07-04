/*
 * 수열과 쿼리 13
 * QOJ 18771
 *
 * lazy segment tree
 * Date: 2026.7.4
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;
using ii = pair<int, int>;

struct mint {
    const static int MOD = 1e9 + 7;
    int val;
    mint(): val(0) {}
    mint(int v): val(v) {}
    mint(const mint& x): val(x.val) {}

    friend istream& operator>>(istream& is, mint& x) {
        return is >> x.val;
    }
    friend ostream& operator<<(ostream& os, const mint& x) {
        return os << x.val;
    }

    mint operator+(const mint& x) const { return mint(*this) += x; }
    mint& operator+=(const mint& x) {
        if ((val += x.val) >= MOD) val -= MOD;
        return *this;
    }
    mint operator*(const mint& x) const { return mint(*this) *= x; }
    mint& operator*=(const mint& x) {
        val = (1LL * val * x.val) % MOD; return *this;
    }
};
using mm = pair<mint, mint>;

class lazy_seg_tree {
    int N, lgN;
    vector<mint> ar;
    vector<mm> lz;

    void _apply(int i, mm op) {
        ar[i] = ar[i] * op.first + op.second * (N >> __lg(i));
        if (i < N) {
            lz[i].first *= op.first;
            lz[i].second = lz[i].second * op.first + op.second;
        }
    }
    void _push(int i) {
        _apply(i<<1, lz[i]), _apply(i<<1|1, lz[i]);
        lz[i] = mm(1, 0);
    }
    void _pull(int i) {
        ar[i] = ar[i<<1] + ar[i<<1|1];
    }

public:
    lazy_seg_tree(const vector<mint>& inp) {
        int sz = inp.size();
        N = 1, lgN = 0;
        while (N < sz) N *= 2, ++lgN;

        ar.resize(2*N, 0);
        copy(begin(inp), end(inp), begin(ar) + N);
        for (int i = N-1; i > 0; --i) _pull(i);
        lz.assign(N, mm(1, 0));
    }
    void update(int i, int j, mm op) {
        i |= N, j |= N;
        for (int k = lgN; k; --k) {
            if (    i>>k<<k !=   i) _push(i>>k);
            if ((j+1)>>k<<k != j+1) _push(j>>k);
        }
        for (int l = i, r = j; l <= r; l >>= 1, r >>= 1) {
            if ( l&1) _apply(l++, op);
            if (~r&1) _apply(r--, op);
        }
        for (int k = 1; k <= lgN; ++k) {
            if (    i>>k<<k !=   i) _pull(i>>k);
            if ((j+1)>>k<<k != j+1) _pull(j>>k);
        }
    }
    mint query(int i, int j) {
        i |= N, j |= N;
        for (int k = lgN; k; --k) {
            if (    i>>k<<k !=   i) _push(i>>k);
            if ((j+1)>>k<<k != j+1) _push(j>>k);
        }
        mint ans(0);
        for (int l = i, r = j; l <= r; l >>= 1, r >>= 1) {
            if ( l&1) ans += ar[l++];
            if (~r&1) ans += ar[r--];
        }
        return ans;
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n; cin >> n;
    vector<mint> inp(n); for (mint& x : inp) cin >> x;
    lazy_seg_tree segt(inp);

    int m; cin >> m;
    while (m--) {
        int op, i, j, v; cin >> op >> i >> j; --i; --j;
        if (op < 4) cin >> v;

        switch(op) {
            case 1: segt.update(i, j, mm(1, v)); break;
            case 2: segt.update(i, j, mm(v, 0)); break;
            case 3: segt.update(i, j, mm(0, v)); break;
            case 4: cout << segt.query(i, j) << '\n';
        }
    }

    return 0;
}
