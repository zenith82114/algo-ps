/*
 * Russia Open Olympiad in Informatics 2021/2022 Day 1 A. Good arrays
 * BOJ 30668 - DP, combinatorics
 * Date: 2024.5.27
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;

constexpr int MOD = 998'244'353;
constexpr int MAXC = 5e7 + 4;

struct mint {
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

array<pair<int, int>, MAXC> spf;
vector<int> primes;
array<mint, MAXC> f;
array<mint, 32> g;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, c; cin >> n >> c;

    for (int x = 2; x <= c; ++x) {
        auto& [p, k] = spf[x];
        if (!k) {
            p = x, k = 1;
            primes.emplace_back(x);
        }
        for (int q : primes) {
            if (q < p && 1ll * x * q <= c) {
                spf[x * q] = {q, 1};
            }
            else break;
        }
        if (1ll * x * p <= c) {
            spf[x * p] = {p, k + 1};
        }
    }

    g[0] = 1;
    for (int k = 1; k < 32; ++k) g[k] = g[k - 1] * (n + k - 1) / k;

    mint ans(1);
    f[1] = 1;
    for (int x = 2; x <= c; ++x) {
        auto [p, k] = spf[x];
        int q = 1; for (int _ = 0; _ < k; ++_) q *= p;
        ans += (f[x] = f[x / q] * g[k]);
    }
    cout << ans;
    return 0;
}
