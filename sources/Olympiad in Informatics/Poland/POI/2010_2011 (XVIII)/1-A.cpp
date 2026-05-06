/*
 * Polish Olympiad in Informatics, POI 2010/2011, Stage 1 A. Conspiracy
 * BOJ 8202 - graph theory; degree sequence
 * Date: 2025.1.10
 */

#include<bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n; cin >> n;
    vector<int> d(n);
    array<int, 5000> c; c.fill(0);
    int s = 0;
    for (int& di : d) {
        cin >> di;
        ++c[di];
        s += di;
        for (int _, t = di; t--; cin >> _);
    }
    sort(d.rbegin(), d.rend());

    int p = 0;
    int ans = 0;
    for (int i = 0; i + 1 < n; ++i) {
        p += d[i];
        if (p == i * (i + 1) + s - p) {
            ans += d[i] > d[i + 1] ? 1 : c[d[i]];
        }
    }
    cout << ans;
    return 0;
}
