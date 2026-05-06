/*
 * USA Computing Olympiad, USACO March 2012 Contest, Silver 3. Landscaping
 * BOJ 5892
 * JUNGOL 3776
 *
 * DP
 * Date: 2023.1.19
 */

#include<bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, X, Y, Z; cin >> N >> X >> Y >> Z;
    vector<int> A(1), B(1);
    for (int i = 1; i <= N; ++i) {
        int a, b; cin >> a >> b;
        while (a--) A.emplace_back(i);
        while (b--) B.emplace_back(i);
    }
    int nA = A.size() - 1;
    int nB = B.size() - 1;

    vector<int> dp0(nB+1), dp1(nB+1);
    dp1[0] = 0;
    for (int j = 1; j <= nB; ++j) dp1[j] = dp1[j-1] + X;

    for (int i = 1; i <= nA; ++i) {
        dp0.swap(dp1);
        dp1[0] = dp0[0] + Y;
        for (int j = 1; j <= nB; ++j)
            dp1[j] = min({dp1[j-1] + X, dp0[j] + Y, dp0[j-1] + Z * abs(A[i] - B[j])});
    }

    cout << dp1[nB];
    return 0;
}
