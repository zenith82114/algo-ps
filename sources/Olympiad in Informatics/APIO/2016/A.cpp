/*
 * Asia-Pacific Informatics Olympiad, APIO 2016 A. Boat
 * JUNGOL 3007
 *
 * DP, combinatorics
 * Date: 2026.5.6
 */

#include<bits/stdc++.h>
using namespace std;

struct mint {
    constexpr static int MOD = 1e9 + 7;
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

int l[512], r[512];
mint p[512], delta_p[512];
mint f[2][512];
mint inv_cache[512];
bitset<512> active;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n; cin >> n;
    vector<int> x;
    for (int i = 1; i <= n; ++i) {
        cin >> l[i] >> r[i]; ++r[i];
        x.emplace_back(l[i]);
        x.emplace_back(r[i]);
    }
    sort(begin(x), end(x));
    x.erase(unique(begin(x), end(x)), end(x));

    p[0] = 1;
    inv_cache[0] = 1;
    for (int i = 1; i <= n; ++i) inv_cache[i] = mint(i).inv();

    for (size_t m = 0; m + 1 < x.size(); ++m) {
        active.reset();
        for (int i = 1; i <= n; ++i) if (l[i] <= x[m] && x[m + 1] <= r[i]) active.set(i);
        int K = active.count();
        int L = x[m + 1] - x[m];

        f[1][0] = 0;
        for (int i = 1; i <= n; ++i) {
            f[1][i] = f[1][i - 1] + p[i - 1];
            delta_p[i] = active[i] ? (f[1][i] * L) : 0;
        }

        mint binom(L);
        for (int k = 2; k <= min(K, L); ++k) {
            int now = k&1, pre = ~k&1;
            binom *= inv_cache[k] * (L - k + 1);
            f[now][0] = 0;
            mint fsum(0);
            for (int i = 1; i <= n; ++i) {
                f[now][i] = fsum;
                if (active[i]) {
                    delta_p[i] += fsum * binom;
                    fsum += f[pre][i];
                }
            }
        }

        for (int i = 1; i <= n; ++i) p[i] += delta_p[i];
    }

    mint ans(0);
    for (int i = 1; i <= n; ++i) ans += p[i];
    cout << ans;
    return 0;
}
