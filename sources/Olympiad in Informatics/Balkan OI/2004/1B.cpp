/*
 * Balkan Olympiad in Informatics, BOI 2004 Day 1 B. Team Selection
 * BOJ 2336
 *
 * segment tree
 * Date: 2025.1.27
 */

#include<bits/stdc++.h>
using namespace std;

constexpr int TN = 1<<19, inf = 1e9;
array<int, 2*TN> segt;

void upd(int i, int x) {
    for (segt[i |= TN] = x; i; i >>= 1) segt[i>>1] = min(segt[i], segt[i^1]);
}

int qry(int j) {
    int i = TN; j |= TN;
    int ans = inf;
    for (; i <= j; i >>= 1, j >>= 1) {
        if ( i & 1) ans = min(ans, segt[i++]);
        if (~j & 1) ans = min(ans, segt[j--]);
    }
    return ans;
}

array<int, TN> a, b;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n; cin >> n;
    for (int i = 0; i < n; ++i) { int s; cin >> s; a[s] = i; }
    for (int i = 0; i < n; ++i) { int s; cin >> s; b[s] = i; }

    segt.fill(inf);
    int cnt = 0;
    while (n--) {
        int s; cin >> s;
        if (qry(a[s]) > b[s]) ++cnt;
        upd(a[s], b[s]);
    }

    cout << cnt << '\n';
    return 0;
}
