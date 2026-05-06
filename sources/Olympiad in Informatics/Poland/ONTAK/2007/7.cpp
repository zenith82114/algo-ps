/*
 * POI Training Camp, ONTAK 2007 7. Races
 * BOJ 8526 - DP
 * Date: 2025.11.9
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;
constexpr int MAXN = 1e6 + 4, NEG_INF = INT_MIN / 2;

vector<int> g[MAXN];
bitset<MAXN> mark;

pair<int, int> dfs(int px, int x) {
    int base = 0;
    int c1 = NEG_INF, c2 = NEG_INF;
    for (int y : g[x]) if (y != px) {
        auto [ay, by] = dfs(x, y);
        base += ay;
        int cy = by - ay;
        if (c1 < cy) c2 = c1, c1 = cy;
        else c2 = max(c2, cy);
    }

    int ax = base + max(0, c1 + c2 + 1);
    if (mark[x]) ax = max(ax, base + c1 + 1);

    int bx = mark[x]? base : NEG_INF;
    if (c1 > NEG_INF) bx = max(bx, base + c1);

    return pair<int, int>(ax, bx);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n; cin >> n;
    for (int i = 1; i < n; ++i) {
        int x, y; cin >> x >> y;
        g[x].emplace_back(y);
        g[y].emplace_back(x);
    }
    int m; cin >> m;
    for (int i = 0; i < m; ++i) {
        int x; cin >> x;
        mark.set(x);
    }
    cout << dfs(0, 1).first;
    return 0;
}
