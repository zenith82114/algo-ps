/*
 * JOI Open Contest, JOI Open Contest 2016 C. Skyscraper
 * BOJ 16781
 * JUNGOL 4954
 *
 * connected component DP
 * Date: 2025.8.6
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;
constexpr int MOD = 1e9 + 7;

struct mint {
    int val;
    mint(): val(0) {}
    mint(int v): val(v) {}

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

int a[101];
mint dp[100][101][1001][3] {};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, L; cin >> n >> L;
    if (n == 1) { cout << 1; return 0; }
    for (int i = 1; i <= n; ++i) cin >> a[i];
    sort(a + 1, a + n + 1);
    dp[0][0][0][0] = 1;

    for (int i = 1; i < n; ++i)
    for (int j = 1; j <= i; ++j)
    for (int k = 0; k <= L; ++k)
    for (int h : {0, 1, 2}) {
        int dk = (2*j - h) * (a[i + 1] - a[i]);
        int kk = k - dk;
        if (kk < 0) continue;
        auto& acc = dp[i][j][k][h];

        /* create new comp. without an endpoint */
        acc += dp[i - 1][j - 1][kk][h];
        /* create new comp. with a new endpoint */
        if (h) acc += dp[i - 1][j - 1][kk][h - 1] * (3 - h);
        /* append to comp. not as a new endpoint */
        acc += dp[i - 1][j][kk][h] * (2*j - h);
        /* append to comp. as a new endpoint */
        if (h) acc += dp[i - 1][j][kk][h - 1] * (3 - h)*(j + 1 - h);
        /* merge two comp.s */
        acc += dp[i - 1][j + 1][kk][h] * j*(j + 1 - h);
    }

    /* treat i == n separately to avoid worrying about a[n + 1]
       we only need dp[n][1][*][2]
     */
    mint ans;
    for (int k = 0; k <= L; ++k) ans += dp[n - 1][1][k][1] + dp[n - 1][2][k][2];
    cout << ans.val;
    return 0;
}
