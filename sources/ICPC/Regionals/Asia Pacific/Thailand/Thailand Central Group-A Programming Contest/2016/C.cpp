/*
 * ICPC, Regionals, Asia Pacific, Thailand,
 * Thailand Central Group-A Programming Contest 2016 C. Weeping Fig
 * BOJ 13367 - Stoer-Wagner alg.
 * Date: 2026.3.21
 */

#include<bits/stdc++.h>
using namespace std;

int wei[512][512];
int f[512];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int tc; cin >> tc; while (tc--) {
        int n, m; cin >> n >> m;
        if (n == 1) { cout << 0; continue; }

        for (int x = 1; x <= n; ++x) {
            fill_n(wei[x] + 1, n, 0);
        }
        while (m--) {
            int x, y, w; cin >> x >> y >> w;
            wei[x][y] += w;
            wei[y][x] += w;
        }

        vector<int> alive(n); iota(alive.begin(), alive.end(), 1);
        int ans = INT32_MAX;

        while (alive.size() > 1) {
            auto unseen = alive;
            int s = 0, t = 0;
            fill_n(f + 1, n, 0);

            while (!unseen.empty()) {
                int x = -1, fx = -1; size_t x_pos = n;
                for (size_t i = 0; i < unseen.size(); ++i) {
                    int y = unseen[i];
                    if (fx < f[y]) x = y, fx = f[y], x_pos = i;
                }
                s = t; t = x;
                swap(unseen[x_pos], unseen.back()); unseen.pop_back();
                for (size_t i = 0; i < unseen.size(); ++i) {
                    int y = unseen[i];
                    f[y] += wei[x][y];
                }
            }

            ans = min(ans, f[t]); if (!ans) break;

            for (size_t i = 0; i < alive.size(); ++i) {
                int x = alive[i];
                if (x != s && x != t) {
                    wei[x][s] += wei[x][t];
                    wei[s][x] = wei[x][s];
                }
            }
            swap(*find(alive.begin(), alive.end(), t), alive.back()); alive.pop_back();
        }

        cout << ans << '\n';
    }

    return 0;
}
