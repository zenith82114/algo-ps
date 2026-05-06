/*
 * UCPC 2019 F. 공의 합집합
 * BOJ 17378
 *
 * convex hull, calculus
 * Date: 2024.1.28
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;

struct mint {
    constexpr static int MOD = 1e9 + 7;
    int val;
    mint(): val(0) {}
    mint(i64 v): val(v % MOD) { if (val < 0) val += MOD; }
    mint(const mint& x): val(x.val) {}

    friend ostream& operator<<(ostream& os, const mint& x) {
        return os << x.val;
    }
    mint operator-() const { return mint(val? MOD-val : 0); }
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
    cin.tie(0)->sync_with_stdio(0);

    int n; cin >> n;
    vector<pair<i64, i64> > sph(n);
    for (auto& [x, r] : sph) cin >> x >> r;
    sort(sph.begin(), sph.end());

    auto chk = [&] (int i, int j, int k) {
        auto [xi, ri] = sph[i]; i64 yi = ri*ri - xi*xi;
        auto [xj, rj] = sph[j]; i64 yj = rj*rj - xj*xj;
        auto [xk, rk] = sph[k]; i64 yk = rk*rk - xk*xk;
        return (yj-yk)*(xj-xi) <= (yi-yj)*(xk-xj);
    };

    vector<int> h; int sz = 0;
    for (int i = 0; i < n; ++i) {
        if (sz > 0 && sph[h[sz-1]].first == sph[i].first) {
            h.pop_back(); --sz;
        }
        while (sz > 1 && chk(h[sz-2], h[sz-1], i)) {
            h.pop_back(); --sz;
        }
        h.emplace_back(i); ++sz;
    }

    auto lt_cx = [&] (i64 x, int i, int j) {
        auto [xi, ri] = sph[i];
        auto [xj, rj] = sph[j];
        return 2*x*(xj-xi) < ri*ri - rj*rj - xi*xi + xj*xj;
    };

    mint ans;
    for (auto it = h.begin(); it != h.end(); ++it) {
        int j = *it;
        auto [xj, rj] = sph[j];
        mint sj, ej;
        if (it != h.begin()) {
            int i = *prev(it);
            auto [xi, ri] = sph[i];
            if (lt_cx(xj + rj, i, j)) continue;
            if (lt_cx(xj - rj, i, j)) {
                sj = ri*ri - rj*rj - xi*xi + xj*xj;
                sj /= 2*(xj - xi);
            } else sj = xj - rj;
        } else sj = xj - rj;
        if (next(it) != h.end()) {
            int k = *next(it);
            auto [xk, rk] = sph[k];
            if (!lt_cx(xj - rj, j, k)) continue;
            if (!lt_cx(xj + rj, j, k)) {
                ej = rj*rj - rk*rk - xj*xj + xk*xk;
                ej /= 2*(xk - xj);
            } else ej = xj + rj;
        } else ej = xj + rj;

        ans += (ej - sj)*(rj*rj - xj*xj);
        ans += (ej*ej - sj*sj)*xj;
        ans -= (ej.pow(3) - sj.pow(3))/3;
    }
    cout << ans;
    return 0;
}
