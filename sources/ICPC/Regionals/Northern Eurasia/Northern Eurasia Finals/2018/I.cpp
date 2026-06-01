/*
 * ICPC, Regionals, Northern Eurasia, Northern Eurasia Finals 2018 I. Interval-Free Permutations
 * JUNGOL 12708
 *
 * DP, combinatorics
 * Date: 2026.6.2
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;
const int MAXN = 400;

struct mint {
    static int MOD;
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
    mint operator-() const { return mint(val? MOD - val : 0); }
    mint pow(int e) const {
        mint y(1), x(*this);
        for (; e; e >>= 1) { if (e&1) { y *= x; } x *= x; }
        return y;
    }
    mint inv() const { return pow(MOD - 2); }
    mint& operator=(int v) { val = v; return *this; }

    bool operator==(const mint& x) const { return val == x.val; }
    bool operator!=(const mint& x) const { return val != x.val; }
    bool operator!() const { return !val; }
    mint operator+(const mint& x) const { return mint(*this) += x; }
    mint& operator+=(const mint& x) {
        if ((val += x.val) >= MOD) val -= MOD;
        return *this;
    }
    mint operator-(const mint& x) const { return mint(*this) -= x; }
    mint& operator-=(const mint& x) {
        if ((val -= x.val) < 0) val += MOD;
        return *this;
    }
    mint operator*(const mint& x) const { return mint(*this) *= x; }
    mint& operator*=(const mint& x) {
        val = (1LL * val * x.val) % MOD; return *this;
    }
    mint operator/(const mint& x) const { return mint(*this) /= x; }
    mint& operator/=(const mint& x) {
        return (*this) *= x.inv();
    }
};
int mint::MOD = 1;

mint fact[MAXN+1];
mint A[MAXN+1], B[MAXN+1][MAXN+1], I[MAXN+1];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t >> mint::MOD;

    fact[0] = 1;
    for (int n = 1; n <= MAXN; ++n) fact[n] = fact[n-1] * n;

    I[1] = 1;
    for (int n = 2; n <= MAXN; ++n) {
        I[n] = fact[n];
        for (int k = 1; k < n; ++k) I[n] -= I[k] * fact[n - k];
    }

    B[0][0] = 1;
    for (int k = 1; k <= MAXN; ++k) {
        B[k][k] = 1;
        for (int n = k+1; n <= MAXN; ++n) {
            for (int j = 1; j <= n; ++j) B[k][n] += B[k-1][n - j] * fact[j];
        }
    }

    A[1] = 1;
    A[2] = 2;
    A[4] = 2;
    for (int n = 5; n <= MAXN; ++n) {
        A[n] = fact[n];
        for (int k = 1; k < n; ++k) A[n] -= I[k] * fact[n - k] * 2;
        for (int k = 4; k < n; ++k) A[n] -= A[k] * B[k][n];
    }

    while (t--) {
        int n; cin >> n;
        cout << A[n] << '\n';
    }
    return 0;
}
