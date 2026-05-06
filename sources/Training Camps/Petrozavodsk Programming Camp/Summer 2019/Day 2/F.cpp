/*
 * Petrozavodsk Programming Camp, Summer 2019, Day 2: 300iq Contest 2 F. Fast Spanning Tree
 * BOJ 18473 - smaller to larger, binary jumping
 * Date: 2026.4.1
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;
using ii = pair<int, int>;
constexpr int
    MAXN = 3e5 +4,
    MAXM = 3e5 +4;

int par[MAXN];
i64 wgt[MAXN];
int dsu_find(int x) {
    return (par[x] == x ? x : par[x] = dsu_find(par[x]));
}

struct { int x, y, s; } edges[MAXM];
int target[MAXM][2];
priority_queue<int, vector<int>, greater<> > ready;
priority_queue<ii, vector<ii>, greater<> > pqs[MAXN];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m; cin >> n >> m;
    for (int x = 1; x <= n; ++x) { par[x] = x; cin >> wgt[x]; }
    for (int i = 0; i < m; ++i) {
        auto& [x, y, s] = edges[i]; cin >> x >> y >> s;
        if (wgt[x] + wgt[y] >= s) {
            target[i][0] = target[i][1] = -1;
            ready.push(i);
        } else {
            int rem = s - wgt[x] - wgt[y];
            target[i][0] = wgt[x] + (rem + 1)/2;
            target[i][1] = wgt[y] + (rem + 1)/2;
            pqs[x].emplace(target[i][0], i);
            pqs[y].emplace(target[i][1], i);
        }
    }

    vector<int> ans;
    while (!ready.empty()) {
        int i = ready.top(); ready.pop();
        auto [x, y, _] = edges[i];
        x = dsu_find(x), y = dsu_find(y);
        if (x == y) continue;

        ans.push_back(i);

        wgt[x] += wgt[y]; par[y] = x;
        if (pqs[x].size() < pqs[y].size()) pqs[x].swap(pqs[y]);
        while (!pqs[y].empty()) {
            pqs[x].emplace(pqs[y].top()); pqs[y].pop();
        }

        while (!pqs[x].empty() && pqs[x].top().first <= wgt[x]) {
            auto [t, j] = pqs[x].top(); pqs[x].pop();
            auto [a, b, s] = edges[j];
            a = dsu_find(a), b = dsu_find(b);
            if (a == b) continue;
            if (t != target[j][0] && t != target[j][1]) continue;

            if (wgt[a] + wgt[b] >= s) {
                target[j][0] = target[j][1] = -1;
                ready.push(j);
            } else {
                int rem = s - wgt[a] - wgt[b];
                target[j][0] = wgt[a] + (rem + 1)/2;
                target[j][1] = wgt[b] + (rem + 1)/2;
                pqs[a].emplace(target[j][0], j);
                pqs[b].emplace(target[j][1], j);
            }
        }
    }

    cout << ans.size() << '\n';
    for (int i : ans) cout << (i + 1) << ' ';
    return 0;
}
