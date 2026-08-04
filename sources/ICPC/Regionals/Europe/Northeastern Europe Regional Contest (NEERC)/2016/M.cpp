/*
 * ICPC, Regionals, Europe, Northeastern Europe Regional Contest, NEERC 2016
 * M. Mole Tunnels
 * QOJ 12546
 *
 * min cost flow, tree DP
 * Date: 2026.8.4
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;
using ii = pair<int, int>;
const int MAXN = 1e5+4, INF = 1e9;

int n;
array<int, MAXN> food, flow, down, opt;

void pull(int i) {
    if (food[i] > 0) down[i] = 0, opt[i] = i;
    else down[i] = INF, opt[i] = 0;

    for (int j : {2*i, 2*i+1}) if (j <= n && down[j] != INF) {
        int cost = down[j] + (flow[j] > 0 ? -1 : +1);
        if (down[i] > cost) {
            down[i] = cost, opt[i] = opt[j];
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int m; cin >> n >> m;
    for (int i = 1; i <= n; ++i) cin >> food[i];

    flow.fill(0);
    for (int i = n; i > 0; --i) pull(i);

    i64 ans = 0;
    while (m--) {
        int p; cin >> p;
        int up = 0, cost = INF, lca = 0;

        for (int i = p; i > 0; i >>= 1) {
            if (cost > up + down[i] && down[i] != INF) {
                cost = up + down[i]; lca = i;
            }
            if (i > 1) up += (flow[i] < 0 ? -1 : +1);
        }

        int q = opt[lca];
        --food[q];
        for (int i = p; i > lca; i >>= 1) ++flow[i];
        for (int i = q; i > lca; i >>= 1) --flow[i];
        for (int i = p; i > 0; i >>= 1) pull(i);
        for (int i = q; i > 0; i >>= 1) pull(i);

        cout << (ans += cost) << ' ';
    }

    return 0;
}
