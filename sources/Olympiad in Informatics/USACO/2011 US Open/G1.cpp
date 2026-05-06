/*
 * USA Computing Olympiad, USACO US Open 2011 Contest, Gold 1. Mowing the Lawn
 * JUNGOL 3621
 *
 * DP, sliding window min/max with deque
 * Date: 2026.5.1
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, k; cin >> n >> k;
    i64 psum = 0;
    i64 ans = 0;

    deque<pair<int64_t, int> > dq;
    dq.emplace_back(0, -1);
    for (int i = 0; i < n; ++i) {
        int e; cin >> e;
        psum += e;
        i64 x = ans - psum;
        while (!dq.empty() && dq.back().first <= x) dq.pop_back();
        if (!dq.empty() && dq.front().second + k < i) dq.pop_front();
        ans = max(ans, psum + dq.front().first);
        dq.emplace_back(x, i);
    }

    cout << ans;
    return 0;
}
