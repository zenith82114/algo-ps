/*
 * International Olympiad in Informatics, IOI 2009, Day 2 C. Regions
 * BOJ 22316
 * JUNGOL 2545
 *
 * Regions trick, Euler tour
 * Date: 2025.8.14
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;
constexpr int MAXN = 250'004, MAXR = 25'004;

vector<int> g[MAXN];
int region[MAXN], depth[MAXR] {};
vector<int> loc[MAXR];
int ed[MAXN];
vector<pair<int, int> > ckpt[MAXR];
map<pair<int, int>, i64> cache;

void dfs(int x, int& clk) {
    int rx = region[x];
    int save = clk;
    loc[rx].emplace_back(clk);
    ckpt[rx].emplace_back(clk, ++depth[rx]);
    ++clk;
    for (int y : g[x]) dfs(y, clk);
    ed[save] = clk;
    ckpt[rx].emplace_back(clk, --depth[rx]);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, r, q; cin >> n >> r >> q;
    const int k = round((n / sqrt(q * log2(n))) + .5);
    cin >> region[1];
    for (int x = 2; x <= n; ++x) {
        int px; cin >> px >> region[x];
        g[px].emplace_back(x);
    }
    int clk = 0; dfs(1, clk);

    while (q--) {
        int a, b; cin >> a >> b;
        auto key = make_pair(a, b);
        if (cache.find(key) == end(cache)) {
            int na = loc[a].size(), nb = loc[b].size();
            i64 ans = 0;

            if (min(na, nb) >= k) { // O(na + nb)
                auto iter = ckpt[a].begin();
                for (int x : loc[b]) {
                    while (iter != end(ckpt[a]) && iter->first <= x) ++iter;
                    if (iter != begin(ckpt[a])) ans += prev(iter)->second;
                }
            }
            else if (na < nb) { // O(na log nb)
                for (int x : loc[a]) {
                    auto lp = lower_bound(begin(loc[b]), end(loc[b]), x);
                    auto rp = lower_bound(begin(loc[b]), end(loc[b]), ed[x]);
                    ans += rp - lp;
                }
            }
            else { // O(nb log na)
                for (int x : loc[b]) {
                    auto p = upper_bound(begin(ckpt[a]), end(ckpt[a]), make_pair(x, INT32_MAX));
                    if (p != begin(ckpt[a])) ans += prev(p)->second;
                }
            }
            cache.emplace(key, ans);
        }
        cout << cache[key] << '\n';
    }

    return 0;
}
