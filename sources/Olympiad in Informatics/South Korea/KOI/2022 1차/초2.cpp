/*
 * 한국정보올림피아드, KOI 2022 1차대회, 초등부 2. 조약돌
 * BOJ 25378
 * JUNGOL 5122
 *
 * DP
 * Date: 2023.1.13
 */

#include<bits/stdc++.h>
using namespace std;

int a[2500];
bool good[2500][2500];
int memo[2500];

int dp(int r) {
    if (r < 0) return 0;
    int& mem = memo[r];
    if (mem) return mem;

    mem = r+1;
    for (int l = 0; l < r; ++l) if (good[l][r])
        mem = min(mem, dp(l-1) + r - l);
    mem = min(mem, dp(r-1) + 1);

    return mem;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int n; cin >> n;
    for (int i = 0; i < n; ++i) cin >> a[i];

    for (int l = 0; l < n; ++l) {
        int s = a[l];
        for (int r = l+1; r < n; ++r) {
            good[l][r] = s == a[r];
            if (s > a[r]) break;
            s = a[r] - s;
        }
    }

    cout << dp(n-1) << '\n';
    return 0;
}
