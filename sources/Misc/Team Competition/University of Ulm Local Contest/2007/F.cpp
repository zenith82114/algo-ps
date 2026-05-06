/*
 * University of Ulm Local Contest 2007 F. Frequent values
 * BOJ 6515 - binary search, segment tree
 * Date: 2025.8.28
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;
constexpr int TN = 1<<17;

vector<int> loc;
int segt[2*TN];

int segt_qry(int i, int j) {
    int ans = 0;
    for (i |= TN, j |= TN; i <= j; i >>= 1, j >>= 1) {
        if ( i&1) ans = max(ans, segt[i++]);
        if (~j&1) ans = max(ans, segt[j--]);
    }
    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, q;
    for (cin >> n; n; cin >> n) {
        cin >> q;
        int px = 0xc0ffee;
        loc.clear();
        for (int i = 0; i < n; ++i) {
            int x; cin >> x;
            if (px != x) {
                px = x;
                loc.emplace_back(i);
            }
        }
        loc.emplace_back(n);
        n = loc.size() - 1;

        for (int i = 0; i < n; ++i) segt[i|TN] = loc[i + 1] - loc[i];
        for (int i = TN - 1; i; --i) segt[i] = max(segt[i<<1], segt[i<<1|1]);

        while (q--) {
            int i, j; cin >> i >> j; --i; --j;
            int a = --upper_bound(begin(loc), end(loc), i) - begin(loc);
            int b = --upper_bound(begin(loc), end(loc), j) - begin(loc);
            if (a == b) cout << (j - i + 1) << '\n';
            else cout << max({ loc[a + 1] - i, j - loc[b] + 1, segt_qry(a + 1, b - 1) }) << '\n';
        }
    }

    return 0;
}
