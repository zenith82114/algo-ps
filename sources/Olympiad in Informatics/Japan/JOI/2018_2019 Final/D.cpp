/*
 * Japanese Olympiad in Informatics, JOI 2018/2019 Final
 * D. Coin Collecting
 * QOJ 2765
 *
 * greedy
 * Date: 2026.8.15
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;
using ii = pair<int, int>;
const int MAXN = 1e5+4;

int cnt[2][MAXN];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n; cin >> n;
    i64 ans = 0;
    for (int i = 0; i < 2*n; ++i) {
        int x, y; cin >> x >> y;
        int nx = min(max(x, 1), n);
        int ny = min(max(y, 1), 2);

        ans += abs(nx - x) + abs(ny - y);
        ++cnt[ny-1][nx];
    }

    int d0 = 0, d1 = 0;
    for (int x = 1; x <= n; ++x) {
        d0 += cnt[0][x] - 1;
        d1 += cnt[1][x] - 1;

        if (d1 < 0 && 0 < d0) {
            int t = min(d0, -d1);
            ans += t;
            d0 -= t, d1 += t;
        }
        if (d0 < 0 && 0 < d1) {
            int t = min(-d0, d1);
            ans += t;
            d0 += t, d1 -= t;
        }

        ans += abs(d0) + abs(d1);
    }

    cout << ans;
    return 0;
}
