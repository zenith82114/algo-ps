/*
 * ICPC, Regionals, Asia Pacific, Korea,
 * 2024 ICPC Asia Seoul Regional K. String Rank
 * JUNGOL 11262
 *
 * DP
 * Date: 2026.5.5
 */

#include<bits/stdc++.h>
using namespace std;
const int ALPH = 26;

int run_min[ALPH];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    string s; cin >> s;
    int ans = 0;

    reverse(begin(s), end(s));
    for (char c : s) {
        int x = c - 'a';
        ++run_min[x];
        for (int y = 0; y < ALPH; ++y) {
            run_min[y] = min(run_min[y], run_min[x]);
        }
        ans = max(ans, run_min[x]);
    }
    cout << ans;
    return 0;
}
