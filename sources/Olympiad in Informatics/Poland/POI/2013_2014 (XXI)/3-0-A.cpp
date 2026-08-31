/*
 * Polish Olympiad in Informatics, POI 2013/2014, Stage 3 Day 0
 * A. FarmCraft
 * QOJ 304
 *
 * tree DP, greedy
 * Date: 2026.8.30
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;
using ii = pair<int, int>;
const int MAXN = 5e5+4;

vector<int> gph[MAXN];
array<int, MAXN> c, sz, f;

void dfs(int px, int x) {
    sz[x] = 1;
    f[x] = c[x];

    for (int y : gph[x]) if (y != px) {
        dfs(x, y);
        sz[x] += sz[y];
    }

    if (px) gph[x].erase(find(begin(gph[x]), end(gph[x]), px));
    sort(begin(gph[x]), end(gph[x]),
        [](int a, int b) { return f[a] - 2*sz[a] > f[b] - 2*sz[b]; });

    int s = 0;
    for (int y : gph[x]) {
        f[x] = max(f[x], s + 1 + f[y]);
        s += 2*sz[y];
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n; cin >> n;
    for (int x = 1; x <= n; ++x) cin >> c[x];
    for (int i = 1; i < n; ++i) {
        int x, y; cin >> x >> y;
        gph[x].push_back(y);
        gph[y].push_back(x);
    }

    dfs(0, 1);
    cout << max(f[1], c[1] + 2*(n-1));
    return 0;
}
