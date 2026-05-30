/*
 * ICPC, Regionals, Europe, Northwestern Europe Regional Contest,
 * NWERC 2013 A. Absurdistan Roads
 * JUNGOL 15618
 *
 * greedy, minimum spanning tree (O(n^2) for dense graph)
 * Date: 2026.5.31
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;
using edge = tuple<int, int, int>;
const int MAXN = 2004;

int w[MAXN][MAXN], wt[MAXN][MAXN];
int min_w[MAXN], argmin_w[MAXN];
bitset<MAXN> sel;
vector<edge> ans;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    for (int n; cin >> n; ) {
        for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j) cin >> w[i][j];

        for (int j = 2; j <= n; ++j) min_w[j] = w[1][j], argmin_w[j] = 1;
        sel.reset(); sel.set(1);
        ans.clear();

        for (int t = 1; t < n; ++t) {
            int w0 = INT32_MAX, j = -1;
            for (int k = 2; k <= n; ++k) if (!sel[k] && w0 > min_w[k]) {
                w0 = min_w[k], j = k;
            }

            int i = argmin_w[j];
            ans.emplace_back(w0, i, j);

            for (int k = 1; k <= n; ++k) if (sel[k]) {
                wt[k][j] = wt[j][k] = wt[i][k] + w0;
            }
            sel.set(j);
            for (int k = 2; k <= n; ++k) if (!sel[k] && min_w[k] > w[j][k]) {
                min_w[k] = w[j][k];
                argmin_w[k] = j;
            }
        }

        edge last(INT32_MAX, 0, 0);
        for (int i = 1; i <= n; ++i)
        for (int j = i+1; j <= n; ++j) if (wt[i][j] > w[i][j]) {
            last = min(last, edge(w[i][j], i, j));
        }
        ans.emplace_back(get<0>(last) < INT32_MAX? last : ans[0]);

        for (auto& [w0, i, j] : ans) cout << i << ' ' << j << ' ' << w0 << '\n';
        cout << '\n';
    }

    return 0;
}
