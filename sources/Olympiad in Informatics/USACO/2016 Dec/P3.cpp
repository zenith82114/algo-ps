/*
 * USA Computing Olympiad, USACO 2016 December Contest, Platinum 3. Robotic Cow Herd
 * BOJ 14166
 * JUNGOL 4534
 *
 * Dijkstra's
 * Date: 2024.12.15
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;

vector<vector<int> > x;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, k; cin >> n >> k;
    i64 c0 = 0;
    while (n--) {
        int m; cin >> m;
        vector<int> xi(m); for (int& xij : xi) cin >> xij;
        sort(xi.begin(), xi.end());
        int xi0 = xi[0];
        c0 += xi0;
        for (int& xij : xi) xij -= xi0;
        if (xi.size() > 1) x.emplace_back(xi);
    }
    sort(x.begin(), x.end());

    using ty = tuple<i64, size_t, size_t>;
    priority_queue<ty, vector<ty>, greater<ty> > pq;
    pq.emplace(0, 0, 0);
    i64 ans = 0;

    while (k--) {
        auto [c, i, j] = pq.top(); pq.pop();
        ans += c0 + c;
        if (j + 1 < x[i].size()) {
            pq.emplace(c - x[i][j] + x[i][j + 1], i, j + 1);
        }
        if (i + 1 < x.size()) {
            if (j) pq.emplace(c + x[i + 1][1], i + 1, 1);
            if (j == 1) pq.emplace(c - x[i][1] + x[i + 1][1], i + 1, 1);
        }
    }

    cout << ans;
    return 0;
}
