/*
 * Polish Olympiad in Informatics, POI 2011/2012, Stage 2 Day 1 B. Cloakroom
 * BOJ 8227 - sweep line, knapsack DP
 * Date: 2025.1.18
 */

#include<bits/stdc++.h>
using namespace std;

struct item { int c, a, b; };
struct query { int id, m, k, s; };
constexpr int MAXK = 100'000;
int dp[MAXK + 1] {};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n; cin >> n;
    vector<item> itm(n);
    for (auto& [c, a, b] : itm) cin >> c >> a >> b;
    int p; cin >> p;
    vector<query> que(p);
    vector<bool> ans(p);
    for (int i = 0; i < p; ++i) {
        auto& [id, m, k, s]  = que[i];
        id = i;
        cin >> m >> k >> s;
    }
    sort(itm.begin(), itm.end(),
        [] (const item& x, const item& y) { return x.a < y.a; }
    );
    sort(que.begin(), que.end(),
        [] (const query& x, const query& y) { return x.m < y.m; }
    );

    dp[0] = INT32_MAX;
    for (int i = 0, j = 0; i < p; ++i) {
        const auto& [id, m, k, s] = que[i];
        while (j < n && itm[j].a <= m) {
            const auto& [c, a, b] = itm[j];
            for (int z = MAXK; z >= c; --z) {
                dp[z] = max(dp[z], min(dp[z - c], b));
            }
            ++j;
        }
        ans[id] = (m + s < dp[k]);
    }

    for (bool ansi : ans) cout << (ansi? "TAK\n" : "NIE\n");
    return 0;
}
