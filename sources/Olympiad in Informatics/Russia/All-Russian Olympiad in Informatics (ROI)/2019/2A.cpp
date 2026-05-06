/*
 * All-Russian Olympiad in Informatics 2019 Day 2 A. Гирлянда
 * BOJ 19910 - prefix sum, binary search
 * Date: 2025.3.13
 */

#include<bits/stdc++.h>
using namespace std;

int zc[500004];
int f[500004];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n; cin >> n;
    string s; cin >> s;
    s.insert(s.begin(), '#');

    zc[0] = 0;
    for (int i = 1; i <= n; ++i) zc[i] = zc[i - 1] + (s[i] == '0'? 1 : 0);
    zc[n + 1] = zc[n];

    f[n + 1] = f[n] = n + 1;
    for (int i = n - 1; i >= 0; --i) {
        f[i] = (s[i + 1] == '1'? (i + 1) : f[i + 1]);
    }

    auto bs = [&n] (int i, int k) -> int {
        int lo = i, hi = n + 1;
        while (lo + 1 < hi) {
            int mid = (lo + hi) >> 1;
            if (zc[mid] - zc[i] < k) lo = mid;
            else hi = mid;
        }
        return hi;
    };

    int ans = n - zc[n], ansk = 0, ansc = n - zc[n] + 1;
    for (int k = 1; k < zc[n]; ++k) {
        int i = bs(0, k);
        int cnt = 1;
        while (i <= n) {
            i = f[i];
            if (i > n) break;
            int ni = bs(i, k);
            if (zc[ni] - zc[i] == k) ++cnt;
            i = ni;
        }
        int tmp = (k + 1) * cnt - 1;
        if (ans < tmp && cnt > 1) ans = tmp, ansk = k, ansc = cnt;
    }

    cout << ans << '\n';
    while (ansc--) {
        for (int i = ansk; i--;) cout << '0';
        if (ansc) cout << '1';
    }
    return 0;
}
