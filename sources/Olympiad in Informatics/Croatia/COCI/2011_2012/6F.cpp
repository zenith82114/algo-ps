/*
 * Croatian Open Competition in Informatics, COCI 2011/2012, Contest #6 F. KOŠARE
 * BOJ 2803
 * JUNGOL 3658
 *
 * sum over subsets DP
 * Date: 2023.3.11
 */

#include<bits/stdc++.h>
using namespace std;

struct mint {
    static const int MOD = 1e9 + 7;
    int val;
    mint(): val(0) {}
    mint(int v) {
        val = (-MOD <= v && v < MOD)? v : v % MOD;
        if (val < 0) val += MOD;
    }

    mint operator-() const { return mint(-val); }

    mint operator+(const mint& x) const { return mint(*this) += x; }
    mint& operator+=(const mint& x) {
        if ((val += x.val) >= MOD) val -= MOD;
        return *this;
    }
    mint operator*(const mint& x) const { return mint(*this) *= x; }
    mint& operator*=(const mint& x) {
        val = (1ll * val * x.val) % MOD; return *this;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M; cin >> N >> M;

    vector<mint> pow2(N+1);
    pow2[0] = 1;
    for (int i = 0; i < N; ++i)
        pow2[i+1] = pow2[i] * 2;

    vector<mint> dp(1<<M);
    for (int i = 0; i < N; ++i) {
        int a = 0;
        int k; cin >> k;
        while (k--) {
            int j; cin >> j;
            a |= (1<<(j-1));
        }
        dp[a] += 1;
    }
    for (int j = 0; j < M; ++j)
    for (int i = 0; i < 1<<M; ++i)
        if (i & (1<<j)) dp[i] += dp[i ^ (1<<j)];

    mint ans(0);
    for (int i = 0; i < 1<<M; ++i) {
        mint& x = pow2[dp[~i & ~(-(1<<M))].val];
        ans += __builtin_popcount(i) & 1? -x : x;
    }
    cout << ans.val;
    return 0;
}
