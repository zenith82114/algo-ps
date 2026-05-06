/*
 * Bergen Open, Bergen Open 2019 G. Great GDP
 * BOJ 17986 - binary search, tree DP
 * Date: 2025.3.6
 */

#include<bits/stdc++.h>
using namespace std;

array<int, 100004> c, k;
vector<int> g[100004];

double dp(int px, int x, double m) {
    double ret = c[x] - k[x] * m;
    for (int y : g[x]) if (y != px) {
        ret += max(0., dp(x, y, m));
    }
    return ret;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n; cin >> n;
    for (int x = 1; x <= n; ++x) cin >> c[x];
    for (int x = 1; x <= n; ++x) cin >> k[x];
    for (int e = n - 1; e--;) {
        int x, y; cin >> x >> y;
        g[x].emplace_back(y);
        g[y].emplace_back(x);
    }

    constexpr double eps = 1e-9;
    double lo = 0., hi = 1e6;
    while (lo + eps < hi) {
        double mid = (lo + hi) / 2.;
        (dp(0, 1, mid) >= 0.? lo : hi) = mid;
    }

    cout << fixed << setprecision(9) << ((lo + hi) / 2.);
    return 0;
}
