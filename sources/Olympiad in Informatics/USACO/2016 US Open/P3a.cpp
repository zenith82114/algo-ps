/*
 * USA Computing Olympiad, USACO US Open 2016 Contest, Platinum 3. Landscaping
 * BOJ 12010
 * JUNGOL 3631
 *
 * slope trick
 * Date: 2023.6.27
 */

#include<bits/stdc++.h>
using namespace std;

int main() {
    int N, X, Y, Z; cin >> N >> X >> Y >> Z;
    deque<int> ql, qr;
    int iZ = 0;
    int64_t ans = 0;

    for (int i = 0; i < N; ++i) {
        int a, b; cin >> a >> b;
        int m = min(a, b); a -= m; b -= m;
        while (a--) {
            if (ql.empty()) ql.push_back(-Y + iZ);
            int t = ql.back() - iZ;
            ql.pop_back();
            t = max(t, -Y);
            ans -= t;
            qr.push_front(t - iZ);
        }
        while (b--) {
            if (qr.empty()) qr.push_front(X - iZ);
            int t = qr.front() + iZ;
            qr.pop_front();
            t = min(t, X);
            ans += t;
            ql.push_back(t + iZ);
        }
        iZ += Z;
    }
    cout << ans;
}
