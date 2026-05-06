/*
 * Petrozavodsk Programming Camp, Summer 2019, Day 1: Songyang Chen Contest 2 A. Salty Fish
 * BOJ 18586 - maximum flow, smaller to larger
 * Date: 2026.1.21
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;
const int MAXN = 3e5 + 4;

int par[MAXN], dep[MAXN], a[MAXN];
vector<int> g[MAXN];
vector<pair<int, int> > cam[MAXN];
map<int, i64> mp[MAXN];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int tc; cin >> tc;
    while (tc--) {
        int n, m; cin >> n >> m;
        for (int x = 1; x <= n; ++x) {
            g[x].clear();
            cam[x].clear();
        }
        for (int x = 2; x <= n; ++x) {
            cin >> par[x];
            g[par[x]].push_back(x);
        }
        i64 ans = 0;
        for (int x = 1; x <= n; ++x) { cin >> a[x]; ans += a[x]; }
        while (m--) {
            int x, k, c; cin >> x >> k >> c;
            cam[x].emplace_back(k, c);
        }

        for (int x = 1; x <= n; ++x) {
            for (int y : g[x]) dep[y] = dep[x] + 1;
        }
        for (int x = n; x > 0; --x) {
            mp[x][dep[x]] += a[x];

            for (auto [k, c] : cam[x]) {
                while (c && !mp[x].empty()) {
                    auto it = mp[x].lower_bound(dep[x] + k + 1);
                    if (it == mp[x].begin()) break;
                    it = prev(it);
                    i64& p = it->second;
                    int delta = min((i64)c, p);
                    ans -= delta; c -= delta; p -= delta;
                    if (!p) mp[x].erase(it);
                }
            }

            if (mp[par[x]].size() < mp[x].size()) mp[x].swap(mp[par[x]]);
            for (auto it : mp[x]) mp[par[x]][it.first] += it.second;
            mp[x].clear();
        }
        mp[0].clear();

        cout << ans << '\n';
    }

    return 0;
}
