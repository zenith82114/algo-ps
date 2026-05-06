/*
 * Croatian Open Competition in Informatics, COCI 2006/2007, Contest #6 E. V
 * BOJ 3026
 * JUNGOL 2124
 *
 * DP
 * Date: 2024.1.11
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;

i64 x;
bool given[10];

i64 ten[10][16];
i64 memo[16][100'000];

i64 dp(int n, i64 m) {
    i64& ret = memo[n][m];
    if (ret != -1) return ret;
    if (!n) return ret = (m? 0 : 1);
    ret = 0;
    for (int d = 0; d < 10; ++d) if (given[d]) {
        ret += dp(n-1, (m + x-ten[d][n-1]) % x);
    }
    return ret;
}

i64 solve(i64 a) {
    string sa = to_string(a);
    int n = sa.size();
    i64 ans = 0;
    i64 mod = 0;
    if (!given[0]) {
        for (int i = 0; i < n; ++i) ans += dp(i, 0);
    }
    for (int i = 0; i < n; ++i) {
        int ci = sa[i] - '0';
        for (int d = 0; d < ci; ++d) if (given[d]) {
            ans += dp(n-1-i, (x-mod + x-ten[d][n-1-i]) % x);
        }
        if (given[ci]) {
            mod = (mod + ten[ci][n-1-i]) % x;
        }
        else return ans;
    }
    if (!mod) ++ans;
    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    i64 a, b; cin >> x >> a >> b;
    string u; cin >> u;
    for (char c : u) given[c - '0'] = true;

    if (x < 100'000) {
        for (int d = 0; d < 10; ++d) {
            ten[d][0] = d % x;
            for (int i = 1; i < 16; ++i) ten[d][i] = (ten[d][i-1] * 10) % x;
        }
        for (int i = 0; i < 16; ++i) {
            memset(memo[i], -1, x * sizeof(i64));
        }
        cout << solve(b) - solve(a-1);
    } else {
        auto chk = [] (i64 y) {
            for (; y; y /= 10) if (!given[y%10]) return 0;
            return 1;
        };
        i64 ans = 0;
        for (i64 y = (a+x-1)/x*x; y <= b; y += x) {
            ans += chk(y);
        }
        cout << ans;
    }

    return 0;
}
