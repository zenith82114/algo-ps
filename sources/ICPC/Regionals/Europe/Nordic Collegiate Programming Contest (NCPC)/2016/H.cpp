/*
 * ICPC, Regionals, Europe, Northwestern Europe Regional Contest,
 * Nordic Collegiate Programming Contest, NCPC 2016 H. Highest Tower
 * BOJ 13361
 * JUNGOL 3634
 *
 * ad-hoc; graph theory
 * Date: 2025.11.10
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;
constexpr int MAXN = 5e5;

array<vector<int>, MAXN> g;
bitset<MAXN> vis;
vector<int> f;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n; cin >> n;
    vector<pair<int, int> > rect(n);
    f.reserve(2*n);
    for (auto& [x, y] : rect) {
        cin >> x >> y;
        f.emplace_back(x); f.emplace_back(y);
    }
    sort(f.begin(), f.end());
    auto enc = [] (int x) -> int {
        return lower_bound(f.begin(), f.end(), x) - f.begin();
    };
    for (auto& [x, y] : rect) {
        x = enc(x), y = enc(y);
        g[x].emplace_back(y);
        g[y].emplace_back(x);
    }

    i64 ans = 0;
    queue<int> q;
    for (int i = 0; i < 2*n; i++) if (!g[i].empty() && !vis[i]) {
        int v = 0, e2 = 0;
        i64 s = 0;
        int m = 0;
        q.emplace(i); vis.set(i);
        while (!q.empty()) {
            int x = q.front(); q.pop();
            v++;
            e2 += g[x].size();
            s += (g[x].size() - 1) * f[x];
            m = max(m, f[x]);
            for (int y : g[x]) if (!vis[y]) {
                q.emplace(y); vis.set(y);
            }
        }
        ans += s + (e2 < 2*v) * m;
    }
    cout << ans;
    return 0;
}
