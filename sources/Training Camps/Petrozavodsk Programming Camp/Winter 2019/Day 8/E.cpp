/*
 * Petrozavodsk Programming Camp, Winter 2019, Day 8: Petrozavodsk SU Contest E. 5-Path
 * BOJ 18551 - meet in the middle
 * Date: 2025.3.9
 */

#include<bits/stdc++.h>
using namespace std;
constexpr int MAXN = 100004;
constexpr int MAXM = 200004;

int n, m, a, b;
pair<int, int> edg[MAXM];
vector<pair<int, int> > adj[MAXN], fa[MAXN], fb[MAXN];
int ta[MAXN] {}, tb[MAXN] {};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m;
    for (int i = 1; i <= m; ++i) {
        auto& [x, y] = edg[i];
        cin >> x >> y;
        adj[x].emplace_back(i, y);
        adj[y].emplace_back(i, x);
    }
    cin >> a >> b;

    for (const auto& [i, y] : adj[a]) ta[y] = i;
    for (const auto& [i, y] : adj[b]) tb[y] = i;

    for (int x = 1; x <= n; ++x) if (x != a && x != b) {
        for (const auto& [i, y] : adj[x]) {
            if (ta[y] && y != b) fa[x].emplace_back(max(i, ta[y]), y);
            if (tb[y] && y != a) fb[x].emplace_back(max(i, tb[y]), y);
        }
        sort(fa[x].begin(), fa[x].end());
        fa[x].resize(min<size_t>(fa[x].size(), 3));
        sort(fb[x].begin(), fb[x].end());
        fb[x].resize(min<size_t>(fb[x].size(), 3));
    }

    int ans = m + 1;

    for (int i = 1; i <= m; ++i) {
        auto& [x, y] = edg[i];
        for (const auto& [j, u] : fa[x])
        for (const auto& [k, v] : fb[y]) {
            if (u != v && u != y && v != x) ans = min(ans, max({i, j, k}));
        }
        swap(x, y);
        for (const auto& [j, u] : fa[x])
        for (const auto& [k, v] : fb[y]) {
            if (u != v && u != y && v != x) ans = min(ans, max({i, j, k}));
        }
    }

    cout << (ans > m? -1 : ans);
    return 0;
}
