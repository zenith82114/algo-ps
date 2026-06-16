/*
 * Petrozavodsk Programming Camp, Winter 2020, Day 3: 300iq Contest 3 D. Disjoint LIS
 * QOJ 834
 *
 * combinatorics; RSK correspondence, Greene's theorem
 * Date: 2026.6.16
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;

struct mint {
    constexpr static int MOD = 998244353;
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

int num_rows = 0;
int row_len[100], col_len[100];
mint n_fact(1), ans;

void go(int rem) {
    if (rem == 0) {
        if (num_rows < 2) return;

        int t = num_rows;
        for (int j = 1; j <= row_len[1]; ++j) {
            while (row_len[t] < j) --t;
            col_len[j] = t;
        }

        mint denom(1);
        for (int i = 1; i <= num_rows; ++i) {
            for (int j = 1; j <= row_len[i]; ++j) {
                int hook = col_len[j] - i + row_len[i] - j + 1;
                denom *= hook;
            }
        }

        ans += (n_fact / denom).pow(2);
        return;
    }

    if (num_rows == 1) {
        if (rem < row_len[1]) return;
        row_len[++num_rows] = row_len[1];
        go(rem - row_len[1]);
        --num_rows;
    }
    else {
        int max_val = row_len[num_rows++];
        for (int v = 1; v <= min(rem, max_val); ++v) {
            row_len[num_rows] = v;
            go(rem - v);
        }
        --num_rows;
    }

}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n; cin >> n;
    for (int i = 2; i <= n; ++i) n_fact *= i;

    row_len[0] = INT32_MAX;
    go(n);
    cout << ans;
    return 0;
}
