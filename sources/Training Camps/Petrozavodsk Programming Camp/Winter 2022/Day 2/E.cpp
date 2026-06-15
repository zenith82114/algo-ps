/*
 * Petrozavodsk Programming Camp, Winter 2022, Day 2: KAIST Contest + KOI TST 2021 E. Yet Another Interval Graph Problem
 * QOJ 2556
 *
 * DP, priority queue
 * Date: 2026.6.15
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;
using ii = pair<int, int>;
const int MAXN = 2500;

array<int, MAXN> s, e, w;
vector<int> ends_at[2*MAXN + 1];
i64 dp[2*MAXN + 1];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n; size_t k; cin >> n >> k;
    for (int i = 0; i < n; ++i) cin >> s[i] >> e[i] >> w[i];

    vector<int> X { -1 };
    for (int i = 0; i < n; ++i) X.push_back(s[i]), X.push_back(e[i]);
    sort(begin(X), end(X));
    X.erase(unique(begin(X), end(X)), end(X));

    for (int i = 0; i < n; ++i) {
        int a = lower_bound(begin(X), end(X), e[i]) - begin(X);
        ends_at[a].push_back(i);
    }

    const int m = X.size() - 1;

    for (int a = 0; a < m; ++a) {
        priority_queue<ii, vector<ii>, greater<>> pq;
        i64 topk = 0;

        for (int b = a+1; b <= m; ++b) {
            for (int i : ends_at[b]) if (s[i] > X[a]) {
                pq.emplace(w[i], i);
                topk += w[i];
                if (pq.size() > k) topk -= pq.top().first, pq.pop();
            }

            dp[b] = max(dp[b], dp[a] + topk);
        }
    }

    i64 ans = -dp[m];
    for (int i = 0; i < n; ++i) ans += w[i];
    cout << ans;
    return 0;
}
