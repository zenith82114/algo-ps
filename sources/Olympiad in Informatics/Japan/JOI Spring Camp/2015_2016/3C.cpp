/*
 * JOI 2015/2016 Spring Camp Day 3 C. Telegraph
 * BOJ 17712
 * JUNGOL 4564
 *
 * functional graph, greedy
 * Date: 2024.6.20
 */

#include<bits/stdc++.h>
using namespace std;

array<int, 100004> A, C, vis, mx, mx_nc;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    using i64 = int64_t;

    int n; cin >> n;
    i64 ans = 0;
    for (int x = 1; x <= n; ++x) {
        cin >> A[x] >> C[x];
        vis[x] = 0;
        ans += C[x];
    }
    for (int x = 1; x <= n; ++x) if (!vis[x]) {
        int y = x;
        for (; !vis[y]; y = A[y]) vis[y] = x;
        if (vis[y] == x) {
            int len = 0;
            for (; vis[y] != -1; y = A[y]) vis[y] = -1, ++len;
            if (len == n) { cout << 0; return 0; }
        }
    }

    mx.fill(0), mx_nc.fill(0);
    for (int x = 1; x <= n; ++x) {
        mx[A[x]] = max(mx[A[x]], C[x]);
        if (vis[x] != -1) mx_nc[A[x]] = max(mx_nc[A[x]], C[x]);
    }

    for (int x = 1; x <= n; ++x) {
        ans -= mx[x];
        if (vis[x] == -1) {
            i64 delta = INT64_MAX;
            for (int y = x; vis[y] == -1; y = A[y]) {
                delta = min<i64>(delta, mx[y] - mx_nc[y]);
                vis[y] = 0;
            }
            ans += delta;
        }
    }

    cout << ans;
    return 0;
}
