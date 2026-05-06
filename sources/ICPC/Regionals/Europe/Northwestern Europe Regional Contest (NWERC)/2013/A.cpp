/*
 * ICPC, Regionals, Europe, Northwestern Europe Regional Contest,
 * NWERC 2013 A. Absurdistan Roads
 * BOJ 9643 - greedy, minimum spanning tree
 * Date: 2025.10.6
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;
using edge = tuple<int, int, int>;

int w[2004][2004];
bitset<2004> sel;
vector<pair<int, int> > g[2004];
priority_queue<edge, vector<edge>, greater<edge> > pq;
int d[2004];
vector<edge> ans;

void dfs(int p, int i) {
    for (auto [j, w0] : g[i]) if (j != p) {
        d[j] = d[i] + w0;
        dfs(i, j);
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    for (int n; cin >> n; ) {
        for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j) cin >> w[i][j];

        sel.reset();
        sel.set(1);
        for (int i = 1; i <= n; ++i) g[i].clear();
        for (int j = 2; j <= n; ++j) pq.emplace(w[1][j], 1, j);
        ans.clear();
        while (!pq.empty()) {
            auto e = pq.top(); pq.pop();
            auto& [w0, i, j] = e;
            if (!sel[j]) {
                sel.set(j);
                g[i].emplace_back(j, w0);
                g[j].emplace_back(i, w0);
                for (int k = 1; k <= n; ++k) if (!sel[k]) pq.emplace(w[j][k], j, k);
                ans.emplace_back(e);
            }
        }

        edge last(INT32_MAX, 0, 0);
        for (int i = 1; i <= n; ++i) {
            d[i] = 0;
            dfs(0, i);
            for (int j = 1; j <= n; ++j) if (d[j] > w[i][j]) {
                last = min(last, edge(w[i][j], i, j));
            }
        }
        ans.emplace_back(get<0>(last) < INT32_MAX? last : ans[0]);

        for (auto& [w0, i, j] : ans) cout << i << ' ' << j << ' ' << w0 << '\n';
        cout << '\n';
    }

    return 0;
}
