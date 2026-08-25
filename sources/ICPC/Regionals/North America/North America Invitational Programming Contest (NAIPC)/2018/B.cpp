/*
 * North American Invitational Programming Contest, NAIPC 2018
 * B. Double Clique
 * QOJ 3015
 *
 * graph theory
 * Date: 2026.8.25
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;
using ii = pair<int, int>;
const int MAXN = 2e5+4;

int deg[MAXN], sdeg[MAXN];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m; cin >> n >> m;
    while (m--) {
        int x, y; cin >> x >> y;
        ++deg[x], ++deg[y];
    }

    copy_n(deg+1, n, sdeg+1);
    sort(sdeg+1, sdeg+n+1, greater<>());
    int k = -1;
    for (int i = n; i > 0; --i) if (sdeg[i] >= i-1) { k = i; break; }

    int a = accumulate(sdeg+1, sdeg+k+1, 0);
    int b = accumulate(sdeg+k+1, sdeg+n+1, 0);
    if (a != (i64)k*(k-1) + b) { cout << 0; return 0; }

    a = 0, b = 0;
    for (int i = 1; i <= k; ++i) if (sdeg[i] == k-1) ++a;
    for (int i = k+1; i <= n; ++i) if (sdeg[i] == k-1) ++b;
    cout << (1 + a + (a == 1 ? b : 0));
    return 0;
}
