/*
 * 한국정보올림피아드, KOI 2008, 중등부 2/고등부 1. 채점
 * BOJ 6989
 * JUNGOL 1734
 *
 * DP, bitset
 * Date: 2024.4.17
 */

#include<bits/stdc++.h>
using namespace std;

constexpr int SZ = 1133333;
array<int, 151> val;
array<bitset<SZ>, 151> dp;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n; cin >> n;
    for (int i = 1; i <= n; ++i) cin >> val[i];

    dp[0].set(0);
    for (int i = 1; i <= n; ++i) {
        int offset = 0;
        int mult = 0;

        dp[i] |= dp[i-1];
        for (int j = i; j > 1; --j) {
            offset += val[j] * (++mult);
            dp[i] |= (dp[j-2] << offset);
        }
        offset += val[1] * (++mult);
        dp[i].set(offset);
    }

    int k; cin >> k;
    while (k < SZ && dp[n][k]) ++k;
    cout << k;

    return 0;
}
