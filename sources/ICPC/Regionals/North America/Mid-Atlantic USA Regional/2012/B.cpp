/*
 * ICPC, Regionals, North America,
 * 2012 Mid-Atlantic USA Regional Programming Contest B. Component Testing
 * 2012 Southeast USA Regional Programming Contest B. Component Testing
 * BOJ 4698
 * JUNGOL 13934
 *
 * greedy, max-flow min-cut duality
 * Date: 2024.11.14
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m;
    for (cin >> n >> m; n | m; cin >> n >> m) {
        vector<pair<int, int> > X(n), Y(m);
        i64 nX = 0, nY = 0;
        i64 fX = 0, fY = 0;
        for (auto& [cx, nx] : X) {
            cin >> nx >> cx;
            nX += nx;
            fX += (i64)cx * nx;
        }
        for (auto& [cy, ny] : Y) {
            cin >> ny >> cy;
            nY += ny;
            fY += (i64)cy * ny;
        }

        sort(X.begin(), X.end(), greater<pair<int, int> >());
        sort(Y.begin(), Y.end());

        i64 ans = min(fX, fY);
        i64 cur = fX;
        const int plim = min<i64>(nX, Y.back().first + 1);
        int i = 0, j = 0;
        i64 q = 0;
        for (int p = 1; p <= plim; ++p) {
            cur -= X[i].first;
            if (--X[i].second == 0) ++i;
            while (j < m && Y[j].first < p) {
                q += Y[j].second;
                cur += (i64)Y[j].first * Y[j].second;
                ++j;
            }
            ans = min(ans, cur + p * (nY - q));
        }

        cout << (ans >= fX) << '\n';
    }

    return 0;
}
