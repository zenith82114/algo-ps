/*
 * 2018 KAIST RUN Spring Contest T. Touch The Sky
 * BOJ 15773 - slope trick
 * Date: 2023.7.8
 */

#include<bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    using i64 = int64_t;
    using ii = pair<i64, i64>;

    int N; cin >> N;
    vector<ii> ar(N);
    for (auto& [l, d] : ar) cin >> l >> d;
    sort(ar.begin(), ar.end(), [] (const ii& a, const ii& b) {
        return a.first + a.second < b.first + b.second;
    });

    i64 h = ar[0].second;
    priority_queue<i64> pq; pq.emplace(ar[0].second);
    for (int i = 1; i < N; ++i) {
        const auto& [l, d] = ar[i];
        const auto m = pq.top();
        if (h <= l) {
            h += d;
            pq.emplace(d);
        }
        else if (h - m <= l && d < m) {
            h += d - m;
            pq.pop();
            pq.emplace(d);
        }
    }

    cout << pq.size();
    return 0;
}
