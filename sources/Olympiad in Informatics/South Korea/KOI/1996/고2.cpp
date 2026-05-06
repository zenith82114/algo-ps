/*
 * 한국정보올림피아드, KOI 1996, 고등부 2. 교차하지 않는 원의 현들의 최대집합
 * BOJ 2673
 * JUNGOL 1769
 *
 * DP
 * Date: 2022.9.16
 */

#include<bits/stdc++.h>
using namespace std;

vector<pair<int, int>> chords;
int dp[101][101];

int solve(int i, int j) {
    int &ret = dp[i][j];
    if (ret != -1)
        return ret;
    if (i >= j)
        return ret = 0;
    ret = 0;
    bool flag = false;
    for (const auto& [c1, c2] : chords) {
        if (c1 == i && c2 == j)
            flag = true;
        else if (
            i <= c1 && c1 <= j &&
            i <= c2 && c2 <= j
        ) {
            ret = max(ret, solve(i, c1 -1) + solve(c1, j));
            ret = max(ret, solve(i, c2) + solve(c2 +1, j));
        }
    }
    return ret += flag;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int N; cin >> N;
    chords.resize(N);
    for (auto& [c1, c2] : chords) {
        cin >> c1 >> c2;
        if (c1 > c2) swap(c1, c2);
    }

    memset(dp, -1, sizeof dp);
    cout << solve(1, 100) << '\n';

    return 0;
}
