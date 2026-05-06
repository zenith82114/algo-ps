/*
 * USA Computing Olympiad, USACO 2017 February Contest, Silver 1. Why Did the Cow Cross the Road
 * BOJ 14464
 * JUNGOL 4016
 *
 * greedy
 * Date: 2023.4.22
 */

#include<bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int C, N; cin >> C >> N;

    vector<int> T(C);
    for (int& t : T) cin >> t;
    sort(T.begin(), T.end());

    vector<pair<int, int> > U(N);
    for (auto& [a, b] : U) cin >> a >> b;
    sort(U.begin(), U.end());

    priority_queue<int, vector<int>, greater<int> > pq;

    int ans = 0;
    for (int i = 0, j = 0; i < C; ++i) {
        while (j < N) {
            auto& [aj, bj] = U[j];
            if (bj < T[i]) ++j;
            else if (aj <= T[i]) { pq.emplace(bj); ++j; }
            else break;
        }
        while (!pq.empty() && pq.top() < T[i]) pq.pop();
        if (!pq.empty()) { ++ans; pq.pop(); }
    }
    cout << ans;
    return 0;
}
