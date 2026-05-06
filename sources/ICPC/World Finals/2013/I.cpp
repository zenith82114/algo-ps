/*
 * ICPC, World Finals, ACM-ICPC World Finals 2013 I. Pirate Chest
 * BOJ 8885
 * JUNGOL 10773
 *
 * stack
 * Date: 2025.1.26
 */

#include<bits/stdc++.h>
using namespace std;

int x[512][512];
int y[512];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int a, b, n, m; cin >> a >> b >> n >> m;
    for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j) cin >> x[i][j];
    y[m] = -1;
    int64_t ans = 0;

    for (int u = 0; u < n; ++u) {
        for (int j = 0; j < m; ++j) y[j] = x[u][j];
        for (int d = u; d < n; ++d) {
            for (int j = 0; j < m; ++j) y[j] = min(y[j], x[d][j]);
            stack<pair<int, int> > sk;
            sk.emplace(-1, -1);
            for (int r = 0; r <= m; ++r) {
                while (sk.top().second > y[r]) {
                    int e = sk.top().second; sk.pop();
                    int l = sk.top().first;
                    int h = d - u + 1;
                    int w = r - l - 1;
                    int c = max(min(h, a) * min(w, b), min(w, a) * min(h, b));
                    int p = n * m - c;
                    int64_t q = 1ll * e * n * m;
                    ans = max(ans, ((q - 1) / p) * c);
                }
                sk.emplace(r, y[r]);
            }
        }
    }

    cout << ans;
    return 0;
}
