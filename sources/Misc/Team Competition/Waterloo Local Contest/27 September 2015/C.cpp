/*
 * Waterloo's local Programming Contests, 27 September, 2015 C. Power Eggs
 * BOJ 11309 - DP
 * Date: 2023.11.6
 */

#include<bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    using u32 = uint32_t;

    u32 dp[33][33] {};

    for (int k = 1; k <= 32; ++k)
    for (int t = 1; t <= 32; ++t) {
        dp[k][t] = dp[k-1][t-1] + dp[k][t-1] + 1;
    }

    int tc; cin >> tc;
    while (tc--) {
        u32 n; int k; cin >> n >> k;
        if (n > dp[k][32]) {
            cout << "Impossible\n"; continue;
        }
        int l = 1, r = 32;
        while (l < r) {
            int mid = (l + r)>>1;
            if (dp[k][mid] < n) l = mid+1;
            else r = mid;
        }
        cout << l << '\n';
    }

    return 0;
}
