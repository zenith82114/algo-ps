/*
 * Asia-Pacific Informatics Olympiad, APIO 2012 A. Dispatching
 * BOJ 4002
 * JUNGOL 2556
 *
 * DP, smaller to larger
 * Date: 2025.11.18
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;
constexpr int MAXN = 1e5 + 4;

array<int, MAXN> par, wgt, val;
array<i64, MAXN> sum_wgt;

struct comp {
    bool operator()(int x, int y) { return wgt[x] < wgt[y]; }
};
array<priority_queue<int, vector<int>, comp>, MAXN> pq;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n; i64 m; cin >> n >> m;
    for (int x = 1; x <= n; ++x) cin >> par[x] >> wgt[x] >> val[x];
    sum_wgt.fill(0);

    i64 ans = 0;
    for (int x = n; x > 0; --x) {
        pq[x].emplace(x);
        sum_wgt[x] += wgt[x];
        for (; sum_wgt[x] > m; pq[x].pop()) sum_wgt[x] -= wgt[pq[x].top()];
        ans = max(ans, val[x] * (i64)pq[x].size());

        int u = par[x];
        if (pq[u].size() < pq[x].size()) {
            swap(pq[u], pq[x]);
            swap(sum_wgt[u], sum_wgt[x]);
        }
        for (; !pq[x].empty(); pq[x].pop()) {
            sum_wgt[u] += wgt[pq[x].top()];
            pq[u].emplace(pq[x].top());
        }
    }
    cout << ans;
    return 0;
}
