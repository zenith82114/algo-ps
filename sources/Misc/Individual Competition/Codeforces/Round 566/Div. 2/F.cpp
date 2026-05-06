/*
 * Codeforces, Codeforces Round 566 (Div. 2) F. Maximum Sine
 * BOJ 30166 - baby-step giant-step
 * Date: 2024.7.14
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int tc; cin >> tc;
    while (tc--) {
        i64 a, b, p, q; cin >> a >> b >> p >> q;

        if (b - a < 10) {
            i64 x_best = -1, gx_best = 2*q;
            for (i64 x = a; x <= b; ++x) {
                i64 gx = abs(2*p*x % (2*q) - q);
                if (gx_best > gx) {
                    x_best = x;
                    gx_best = gx;
                }
            }
            cout << x_best << '\n';
            continue;
        }

        i64 d = (i64)floor(sqrt(b - a));
        assert(a + d*d <= b);
        set<i64> s;
        vector<pair<i64, i64> > v;
        for (i64 x = a; x < a + d; ++x) {
            i64 hx = 2*p*x % (2*q);
            if (s.insert(hx).second) {
                v.emplace_back(hx, x);
            }
        }
        sort(v.begin(), v.end());
        auto t = v.front(); t.first += 2*q;
        v.insert(v.begin(), {v.back().first - 2*q, v.back().second});
        v.emplace_back(t);

        i64 x_best = -1, gx_best = 2*q;
        for (i64 k = 0; k < d; ++k) {
            i64 gy = ((2*p*k) % (2*q)) * d % (2*q);
            gy = (q - gy + 2*q) % (2*q);
            auto lb = lower_bound(v.begin(), v.end(), make_pair(gy, (i64)0));

            i64 x = lb->second + k*d;
            i64 gx = abs(2*p*x % (2*q) - q);
            if (gx_best > gx || (gx_best == gx && x_best > x)) {
                x_best = x;
                gx_best = gx;
            }
            --lb;
            x = lb->second + k*d;
            gx = abs(2*p*x % (2*q) - q);
            if (gx_best > gx || (gx_best == gx && x_best > x)) {
                x_best = x;
                gx_best = gx;
            }
        }

        for (i64 x = a + d*d; x <= b; ++x) {
            i64 gx = abs(2*p*x % (2*q) - q);
            if (gx_best > gx) {
                x_best = x;
                gx_best = gx;
            }
        }

        cout << x_best << '\n';
    }

    return 0;
}
