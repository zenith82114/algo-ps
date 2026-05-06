/*
 * ICPC, Regionals, Europe, Southeastern Europe Regional Contest,
 * SEERC 2014 A. Banks
 * BOJ 10350 - math, prefix sum
 * Date: 2024.6.14
 */

#include<bits/stdc++.h>
using namespace std;

array<int, 20005> ps;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n; cin >> n;
    ps[0] = 0;
    for (int i = 1; i <= n; ++i) cin >> ps[i];
    copy(ps.begin() + 1, ps.begin() + n + 1, ps.begin() + n + 1);
    partial_sum(ps.begin(), ps.end(), ps.begin());

    int64_t ans = 0;
    for (int i = 0; i < n; ++i)
    for (int j = i+1; j < i+n; ++j) if (ps[i] > ps[j]) {
        ans += (ps[i] - ps[j] + ps[n] - 1) / ps[n];
    }
    cout << ans;
    return 0;
}
