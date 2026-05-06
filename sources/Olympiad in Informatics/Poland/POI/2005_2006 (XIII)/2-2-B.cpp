/*
 * Polish Olympiad in Informatics, POI 2005/2006, Stage 2 Day 2 B. Ploughing
 * BOJ 8131 - greedy, two pointers
 * Date: 2023.12.26
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;

int k, m, n;
int x[2048][2048] {};
i64 s[2048][2048] {};

i64 sum(int i1, int i2, int j1, int j2) {
    return s[i2][j2] - s[i1-1][j2] - s[i2][j1-1] + s[i1-1][j1-1];
}

bool check(int l, int r) {
    int i1 = 1, i2 = n, j1 = 1, j2 = m;
    int t = n + m - r + l - 2;
    while (t--) {
        if (i1 < i2 && sum(i1, i1, j1, j2) <= k) ++i1; else
        if (i1 < i2 && sum(i2, i2, j1, j2) <= k) --i2; else
        if (j1 < l  && sum(i1, i2, j1, j1) <= k) ++j1; else
        if (j2 > r  && sum(i1, i2, j2, j2) <= k) --j2;
        else return false;
    }
    return sum(i1, i1, l, r) <= k;
}

int solve() {
    for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= m; ++j) {
        s[i][j] = x[i][j] + s[i-1][j] + s[i][j-1] - s[i-1][j-1];
    }

    int l = 1, r = 1;
    int d = 0;
    while (l <= m) {
        if (check(l, r)) {
            d = max(d, r - l + 1);
            ++(r < m? r : l);
        } else ++(l < r? l : r);
    }
    return d? (m + n - d) : INT32_MAX;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> k >> m >> n;
    for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= m; ++j) cin >> x[i][j];
    int ans = solve();

    int p = min(n, m), q = max(n, m);
    for (int i = 1; i <= p; ++i)
    for (int j = i+1; j <= q; ++j) {
        swap(x[i][j], x[j][i]);
    }
    swap(n, m);

    ans = min(ans, solve());
    cout << ans;
    return 0;
}
