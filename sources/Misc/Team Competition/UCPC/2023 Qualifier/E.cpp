/*
 * UCPC 2023 Qualifier E. 반전수
 * BOJ 28299
 *
 * probability theory, combinatorics
 * Date: 2023.8.15
 */

#include<bits/stdc++.h>
using namespace std;

struct mint {
    static const int MOD = 998'244'353;
    int val;
    mint(): val(0) {}
    mint(int v) {
        val = (-MOD <= v && v < MOD)? v : v % MOD;
        if (val < 0) val += MOD;
    }
    mint(const mint& x): val(x.val) {}

    friend istream& operator>>(istream& is, mint& x) {
        return is >> x.val;
    }
    friend ostream& operator<<(ostream& os, const mint& x) {
        return os << x.val;
    }
    mint operator-() const { return mint(-val); }
    mint pow(int e) const {
        mint y(1), x(*this);
        for (; e; e >>= 1) { if (e&1) { y *= x; } x *= x; }
        return y;
    }
    mint inv() const { return pow(MOD - 2); }

    bool operator==(const mint& x) const { return val == x.val; }
    bool operator!=(const mint& x) const { return val != x.val; }
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
        val = (1ll * val * x.val) % MOD; return *this;
    }
    mint operator/(const mint& x) const { return mint(*this) /= x; }
    mint& operator/=(const mint& x) {
        return (*this) *= x.inv();
    }
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);

    int N; cin >> N;
    vector<mint> A(N); for (mint& a : A) cin >> a;
    mint b = accumulate(A.begin(), A.end(), mint());
    mint es, es2;

    for (const mint& a : A) {
        b -= a;
        mint ex = a*b/2;
        mint ex2 = a*(a-1)*b*(b-1)/4 + a*b*(a+b-2)/3 + ex;
        es2 += es*ex*2 + ex2;
        es += ex;
    }
    cout << es2;
    return 0;
}
