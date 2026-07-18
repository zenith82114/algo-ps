/*
 * ICPC, Regionals, Europe, Southeastern Europe Regional Contest, SEERC 2019
 * F. Game on a Tree
 * QOJ 2376
 *
 * game theory, tree DP
 * Date: 2026.7.18
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;
using ii = pair<int, int>;
const int MAXN = 1e5+4;

vector<int> gph[MAXN];

int dp(int px, int x) {
    int s = 0;
    for (int y : gph[x]) if (y != px) s += dp(x, y);
    return s > 0 ? s-1 : 1;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n; cin >> n;
    for (int i = 1; i < n; ++i) {
        int x, y; cin >> x >> y;
        gph[x].push_back(y);
        gph[y].push_back(x);
    }

    cout << (dp(0, 1) > 0 ? "Alice" : "Bob");
    return 0;
}
