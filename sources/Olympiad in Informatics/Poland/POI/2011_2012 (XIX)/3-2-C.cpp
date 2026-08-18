/*
 * Polish Olympiad in Informatics, POI 2011/2012, Stage 3 Day 2
 * C. Prefixuffix
 *
 * QOJ 13311
 * Manacher's
 * Date: 2026.8.18
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;
using ii = pair<int, int>;

class manacher {
    vector<int> rad;

public:
    manacher(const string& s) {
        string t; t.push_back('$');
        for (char c : s) t.push_back(c), t.push_back('$');

        int n = t.size();
        rad.assign(n, 0);

        int p = 1;
        for (int i = 1; i < n; ++i) {
            rad[i] = min(rad[2*p - i], max(0, p + rad[p] - i));

            while (
                0 <= i - rad[i] - 1 && i + rad[i] + 1 < n &&
                t[i - rad[i] - 1] == t[i + rad[i] + 1]
            ) ++rad[i];

            if (p + rad[p] < i + rad[i]) p = i;
        }
    }

    int even_rad(int i) { return rad[2*i]/2; }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n; cin >> n;
    string t; cin >> t;

    string q;
    for (int i = 0; i < n/2; ++i) {
        q.push_back(t[i]);
        q.push_back(t[n-1-i]);
    }
    manacher m(q);
    n ^= (n&1);

    vector<int> nearest(n+1, 1e9);
    nearest[0] = 0;
    for (int i = 1; i <= n/2; ++i) {
        if (m.even_rad(i) == i) nearest[2*i] = 2*i;
    }
    for (int i = n-1; i > 0; --i) {
        nearest[i] = min(nearest[i], nearest[i+1]);
    }

    int ans = 0;
    for (int i = 1; i < n; ++i) {
        int k = nearest[i - m.even_rad(i)];
        if (k <= i) ans = max(ans, 2*i - k);
    }
    cout << ans/2;
    return 0;
}
