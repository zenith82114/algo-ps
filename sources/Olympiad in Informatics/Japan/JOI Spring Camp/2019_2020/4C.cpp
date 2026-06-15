/*
 * JOI 2019/2020 Spring Camp Day 4 C. Treatment Project
 * QOJ 3563
 *
 * Dijkstra's, segment tree
 * Date: 2026.6.15
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;
const int MAXM = 1e5 + 4;

array<int, MAXM> T, L, R, C, X;
array<i64, MAXM> dist;
vector<int> ord, loc, sortX, segt;
int N;
priority_queue<pair<i64, int> > pq;

void update(int node, int s, int e, int qe, int y, int i) {
    if (qe <= s || segt[node] > y) return;

    if (s + 1 == e) {
        int j = ord[s];
        assert(dist[j] == INT64_MAX);
        dist[j] = dist[i] + C[j];
        pq.emplace(-dist[j], j);
        segt[node] = INT32_MAX;
        return;
    }

    int mid = (s + e) / 2;
    update(2*node,   s, mid, qe, y, i);
    update(2*node+1, mid, e, qe, y, i);
    segt[node] = min(segt[2*node], segt[2*node+1]);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m; cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        cin >> T[i] >> L[i] >> R[i] >> C[i];
        X[i] = L[i] - T[i];
    }

    ord.assign(m, 0);
    iota(begin(ord), end(ord), 0);
    sort(begin(ord), end(ord), [](int i, int j) { return X[i] < X[j]; });

    loc.assign(m, 0);
    for (int i = 0; i < m; ++i) loc[ord[i]] = i;

    sortX.assign(m, 0);
    for (int i = 0; i < m; ++i) sortX[i] = X[ord[i]];

    N = 1; while (N < m) N *= 2;
    segt.assign(2*N, INT32_MAX);
    for (int i = 0; i < m; ++i) segt[loc[i]|N] = L[i] + T[i];

    dist.fill(INT64_MAX);
    for (int i = 0; i < m; ++i) if (L[i] == 1) {
        dist[i] = C[i];
        pq.emplace(-C[i], i);
        segt[loc[i]|N] = INT32_MAX;
    }
    for (int i = N-1; i; --i) segt[i] = min(segt[2*i], segt[2*i+1]);

    while (!pq.empty()) {
        int i = pq.top().second; pq.pop();
        int qe = upper_bound(begin(sortX), end(sortX), R[i] - T[i] + 1) - begin(sortX);
        int y = R[i] + T[i] + 1;
        update(1, 0, N, qe, y, i);
    }

    i64 ans = INT64_MAX;
    for (int i = 0; i < m; ++i) if (R[i] == n) ans = min(ans, dist[i]);
    cout << (ans < INT64_MAX ? ans : -1);
    return 0;
}
