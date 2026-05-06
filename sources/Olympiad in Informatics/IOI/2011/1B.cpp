/*
 * International Olympiad in Informatics, IOI 2011, Day 1 B. Race
 * BOJ 5820
 * JUNGOL 2527
 *
 * centroid DnC
 * Date: 2025.8.12
 */

#include<bits/stdc++.h>
using namespace std;
constexpr int INF = 0x3f3f3f3f, MAXN = 200'000;

vector<pair<int, int> > g[MAXN];
int sz[MAXN], min_dep[1'000'004];
vector<int> dirty;
bool is_ct[MAXN] {};

int dfs_sz(int px, int x) {
    sz[x] = 1;
    for (auto [y, _] : g[x]) if (y != px && !is_ct[y]) {
        sz[x] += dfs_sz(x, y);
    }
    return sz[x];
}
int ct(int px, int x, int m) {
    for (auto [y, _] : g[x]) if (y != px && !is_ct[y] && sz[y] > m) {
        return ct(x, y, m);
    }
    return x;
}
int dfs_calc(int px, int x, int K, int d, int k) {
    int ret = INF;
    if (k <= K) {
        ret = min(ret, d + min_dep[K - k]);
        for (auto [y, w] : g[x]) if (y != px && !is_ct[y]) {
            ret = min(ret, dfs_calc(x, y, K, d + 1, k + w));
        }
    }
    return ret;
}
void dfs_upd(int px, int x, int K, int d, int k) {
    if (k <= K) {
        min_dep[k] = min(min_dep[k], d);
        dirty.emplace_back(k);
        for (auto [y, w] : g[x]) if (y != px && !is_ct[y]) {
            dfs_upd(x, y, K, d + 1, k + w);
        }
    }
}
int ctd_dnc(int x, int K) {
    int c = ct(-1, x, dfs_sz(-1, x) / 2);
    is_ct[c] = true;

    for (int x : dirty) min_dep[x] = INF;
    dirty.clear();

    int ret = INF;
    for (auto [y, w] : g[c]) if (!is_ct[y]) {
        ret = min(ret, dfs_calc(c, y, K, 1, w));
        dfs_upd(c, y, K, 1, w);
    }
    for (auto [y, w] : g[c]) if (!is_ct[y]) ret = min(ret, ctd_dnc(y, K));
    return ret;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, K; cin >> n >> K;
    for (int i = 1; i < n; ++i) {
        int x, y, w; cin >> x >> y >> w;
        g[x].emplace_back(y, w);
        g[y].emplace_back(x, w);
    }

    memset(min_dep, INF, sizeof min_dep);
    min_dep[0] = 0;
    int ans = ctd_dnc(0, K);
    cout << (ans < INF ? ans : -1);
    return 0;
}
