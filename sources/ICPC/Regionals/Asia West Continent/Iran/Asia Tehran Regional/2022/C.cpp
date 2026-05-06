/*
 * ICPC, Regionals, Asia West Continent, Iran,
 * 2022 ICPC Asia Tehran Regional Contest C. Simplification
 * BOJ 28226 - geometry, DP
 * Date: 2025.8.29
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;

struct fraction {
    int a, b;
    fraction(int a, int b): a(a), b(b) { assert(b); }
    bool operator<(const fraction& rhs) const {
        return 1ll* a * rhs.b < 1ll* b * rhs.a;
    }
    bool operator<=(const fraction& rhs) const {
        return 1ll* a * rhs.b <= 1ll* b * rhs.a;
    }
};
pair<int, int> a[2000];
int dp[2000];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n; cin >> n;
    for (int i = 0; i < n; ++i) { auto& [x, y] = a[i]; cin >> x >> y; }
    sort(a, a + n);
    int delta; cin >> delta;

    memset(dp, 0x3f, sizeof dp);
    dp[0] = 1;
    for (int i = 0; i < n; ++i) {
        const auto& [xi, yi] = a[i];
        fraction lb(-1e9, 1), ub(1e9, 1);
        for (int j = i + 1; j < n; ++j) {
            const auto& [xj, yj] = a[j];
            fraction m(yj - yi, xj - xi);
            if (lb <= m && m <= ub) dp[j] = min(dp[j], dp[i] + 1);
            lb = max(lb, fraction(yj - delta - yi, xj - xi));
            ub = min(ub, fraction(yj + delta - yi, xj - xi));
        }
    }
    cout << dp[n - 1];

    return 0;
}
