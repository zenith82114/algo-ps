/*
 * ICPC, Regionals, Northern Eurasia,
 * Northwestern Russia Regional Contest Northern Subregional 2012 C. Chemistry
 * BOJ 7772 - DP, combinatorics
 * Date: 2024.5.18
 */

#include<bits/stdc++.h>
using namespace std;
using u64 = uint64_t;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    // dp[m] = # unlabeled rooted trees with m nodes,
    // none of which having more than 3 children
    u64 dp[32] { 1, };
    int ar[5] { 0, };
    auto ways = [&dp, &ar] (int k) -> u64 {
        u64 ans = 1;
        u64 streak = 0;
        for (int i = 1; i <= k; ++i) {
            if (ar[i-1] < ar[i]) {
                streak = 0;
            }
            ans *= dp[ar[i]] + streak;
            ans /= ++streak;
        }
        return ans;
    };

    int n; cin >> n;

    for (int m = 1; m <= n/2; ++m) {
        for (int x = 0; x < m; ++x) {
            ar[1] = x;
            for (int y = x; y < m; ++y) {
                ar[2] = y;
                int z = m - 1 - x - y;
                if (y <= z) {
                    ar[3] = z;
                    dp[m] += ways(3);
                }
            }
        }
    }

    u64 ans = 0;
    for (int w = 0; w <= (n-1)/2; ++w) {
        ar[1] = w;
        for (int x = w; x <= (n-1)/2; ++x) {
            ar[2] = x;
            for (int y = x; y <= (n-1)/2; ++y) {
                ar[3] = y;
                int z = n - 1 - w - x - y;
                if (y <= z && z <= (n-1)/2) {
                    ar[4] = z;
                    ans += ways(4);
                }
            }
        }
    }
    if (~n&1) ans += dp[n/2]*(dp[n/2] + 1)/2;
    cout << ans;

    return 0;
}
