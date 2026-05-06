/*
 * ICPC, Regionals, Asia Pacific, Korea,
 * Asia Regional - Daejeon 2012 K. Sports Reporters
 * BOJ 8898
 *
 * Dilworth's theorem, Konig's theorem
 * Date: 2025.9.1
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;

array<int, 1004> s, d;
array<int, 2008> m, v;
vector<int> g[1004];

int dfs_match(int i) {
    v[i] = 1;
    for (int j : g[i]) {
        int k = m[j];
        if (!k || (!v[k] && dfs_match(k))) {
            m[j] = i; m[i] = j;
            return 1;
        }
    }
    return 0;
}

void dfs_vc(int i) {
    v[i] = 1;
    for (int j : g[i]) if (!v[j] && j != m[i]) v[j] = 1, dfs_vc(m[j]);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int tc; cin >> tc; while (tc--) {
        int n; cin >> n;
        for (int i = 1; i <= n; ++i) g[i].clear();
        for (int i = 1; i <= n; ++i) cin >> s[i];
        for (int i = 1; i <= n; ++i) cin >> d[i];
        for (int i = 1; i <= n; ++i)
        for (int j = i; j <= n; ++j) {
            int t_ij; cin >> t_ij;
            if (s[i] + d[i] + t_ij <= s[j]) g[i].emplace_back(n + j);
            if (s[j] + d[j] + t_ij <= s[i]) g[j].emplace_back(n + i);
        }

        m.fill(0);
        for (int i = 1; i <= n; ++i) v.fill(0), dfs_match(i);
        v.fill(0);
        for (int i = 1; i <= n; ++i) if (!m[i]) dfs_vc(i);

        vector<int> ans;
        for (int x = 1; x <= n; ++x) {
            if ((m[x] && !v[x]) || (m[n + x] && v[n + x])) continue;
            ans.emplace_back(x);
        }
        cout << ans.size() << '\n';
        for (int x : ans) cout << x << ' ';
        cout << '\n';
    }

    return 0;
}
