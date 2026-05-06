/*
 * USA Computing Olympiad, USACO 2022 December Contest, Gold 2. Mountains
 * BOJ 26970
 * JUNGOL 5411
 *
 * geometry, BBST
 * Date: 2023.12.30
 */

#include<bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int h[2001];
    set<int> s[2001];

    auto ccw = [&h] (int i, int j, int k) {
        return 1ll*(j - i)*(h[k] - h[i]) >= 1ll*(k - i)*(h[j] - h[i]);
    };

    int n; cin >> n;
    for (int i = 1; i <= n; ++i) cin >> h[i];

    size_t ans = 0;
    for (int i = 1; i < n; ++i) {
        int mj = i+1;
        s[i].emplace(mj);
        for (int j = i+2; j <= n; ++j) if (ccw(i, mj, j)) {
            s[i].emplace_hint(s[i].end(), j); mj = j;
        }
        ans += s[i].size();
    }

    int q; cin >> q;
    while (q--) {
        int x, y; cin >> x >> y; h[x] += y;
        for (int i = 1; i < x; ++i) {
            ans -= s[i].size();
            s[i].erase(x);
            auto lb = s[i].lower_bound(x);
            while (lb != s[i].end() && !ccw(i, x, *lb)) {
                lb = s[i].erase(lb);
            }
            if (lb == s[i].begin() || ccw(i, *prev(lb), x)) s[i].emplace(x);
            ans += s[i].size();
        }

        ans -= s[x].size();
        s[x].clear();
        int mj = x+1;
        if (x < n) s[x].emplace(mj);
        for (int j = x+2; j <= n; ++j) if (ccw(x, mj, j)) {
            s[x].emplace_hint(s[x].end(), j); mj = j;
        }
        ans += s[x].size();
        cout << ans << '\n';
    }

    return 0;
}
