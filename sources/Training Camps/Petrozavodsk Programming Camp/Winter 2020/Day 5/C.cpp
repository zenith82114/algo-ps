/*
 * Petrozavodsk Programming Camp, Winter 2020, Day 5: Ja giellonian U Contest C. Bookface
 * BOJ 18720 - slope trick
 * Date: 2023.5.19
 */

#include<bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    using i64 = int64_t;

    int TC; cin >> TC;
    while (TC--) {
        int N; i64 D; cin >> N >> D;

        vector<i64> A(N); for (i64& a : A) cin >> a;
        sort(A.begin(), A.end());

        priority_queue<i64> pq;
        for (int i = 0; i < N; ++i) pq.emplace(N * -D);

        i64 iD = N * D;
        i64 ans = 0;
        for (i64 a : A) {
            a -= iD;
            iD += D;
            pq.emplace(a);
            pq.emplace(a);
            ans += pq.top() - a;
            pq.pop();
        }
        cout << ans << '\n';
    }

    return 0;
}
