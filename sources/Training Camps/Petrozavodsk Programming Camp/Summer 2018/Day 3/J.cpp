/*
 * Petrozavodsk Programming Camp, Summer 2018, Day 3: MIPT Contest J. Jaw-Dropping Set
 * BOJ 18975 - greedy
 * Date: 2023.7.18
 */

#include<iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    using i64 = int64_t;

    int tc; cin >> tc;
    while (tc--) {
        i64 n; cin >> n;
        i64 ans = 0;
        int i = 0;
        while (n > 0) {
            if (~n&1) --n;
            i64 m = n/3;
            if (~m&1) --m;
            ans += ((n-m)*(n+m+2))>>2<<i;
            n = m;
            ++i;
        }
        cout << ans << '\n';
    }
    return 0;
}
