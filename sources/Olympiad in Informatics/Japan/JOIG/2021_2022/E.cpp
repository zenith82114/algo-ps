/*
 * Japanese Olympiad in Informatics, Japanese Olympiad in Informatics for Girls, JOIG 2021/2022 E. EGOI Exhibition
 * BOJ 24424
 *
 * DP, pigeonhole principle
 * Date: 2024.10.29
 */

#include<bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int N, M; cin >> N >> M;
    vector<pair<int, int> > dp;
    dp.emplace_back(0, 0);
    dp.emplace_back(0, 0);
    for (int i = 0; i < N; ++i) {
        int a, v; cin >> a >> v;
        for (int i : {0, 1}) if (dp[i].second != a) {
            dp.emplace_back(dp[i].first + v, a);
        }
        sort(dp.begin(), dp.end(), greater<pair<int, int> >());
        int j = 1;
        while (dp[j].second == dp[0].second) ++j;
        swap(dp[1], dp[j]);
        while (dp.size() > 2) dp.pop_back();
    }
    cout << dp[0].first;
    return 0;
}
