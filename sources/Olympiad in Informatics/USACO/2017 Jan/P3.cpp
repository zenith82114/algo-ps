/*
 * USA Computing Olympiad, USACO 2017 January Contest, Platinum 3. Subsequence Reversal
 * BOJ 14448
 * JUNGOL 4000
 *
 * DP
 * Date: 2023.6.21
 */

#include<bits/stdc++.h>
using namespace std;

int A[50];
int mem[50][50][50][50];

int dp(int l, int r, int x, int y) {
    if (l > r || x > y) return 0;
    if (l == r) return (x <= A[l] && A[l] <= y? 1 : 0);
    if (mem[l][r][x][y] != -1) return mem[l][r][x][y];

    int& ans = mem[l][r][x][y];
    // 1. not take A[l]
    ans = max(ans, dp(l+1, r, x, y));
    // 2. not take A[r]
    ans = max(ans, dp(l, r-1, x, y));
    // 3. take A[l]
    if (x <= A[l] && A[l] <= y)
        ans = max(ans, 1 + dp(l+1, r, A[l], y));
    // 4. take A[r]
    if (x <= A[r] && A[r] <= y)
        ans = max(ans, 1 + dp(l, r-1, x, A[r]));
    // 5. swap, then take both A[l] and A[r]
    if (x <= A[r] && A[r] < A[l] && A[l] <= y)
        ans = max(ans, 2 + dp(l+1, r-1, A[r], A[l]));
    // 6. swap, then take only A[r] (old A[l])
    if (x <= A[l] && A[l] <= y)
        ans = max(ans, 1 + dp(l+1, r-1, x, A[l]));
    // 7. swap, then take only A[l] (old A[r])
    if (x <= A[r] && A[r] <= y)
        ans = max(ans, 1 + dp(l+1, r-1, A[r], y));
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);

    int N; cin >> N;
    for (int i = 0; i < N; ++i) { cin >> A[i]; A[i]--; }
    memset(mem, -1, sizeof mem);
    cout << dp(0, N-1, 0, 49);
    return 0;
}
