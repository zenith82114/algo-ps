/*
 * Asia-Pacific Informatics Olympiad, APIO 2009 A. Digging for Oil
 * JUNGOL 2425
 *
 * prefix sum, case analysis
 * Date: 2026.5.23
 */

 #include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;
const int MAXN = 1504;
using arr2d = int[MAXN][MAXN];

arr2d a, psum, tl, tr, bl, br;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m, k; cin >> n >> m >> k;
    for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= m; ++j) cin >> a[i][j];

    for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= m; ++j) {
        psum[i][j] = a[i][j] + psum[i-1][j] + psum[i][j-1] - psum[i-1][j-1];
    }

    auto sqsum = [] (int i, int j, int k) -> int {
        assert(i >= k && j >= k);
        return psum[i][j] - psum[i-k][j] - psum[i][j-k] + psum[i-k][j-k];
    };

    for (int i = k; i <= n; ++i)
    for (int j = k; j <= m; ++j) {
        tl[i][j] = max({ tl[i-1][j], tl[i][j-1], sqsum(i, j, k) });
    }

    for (int i = k; i <= n; ++i)
    for (int j = m-k+1; j >= 1; --j) {
        tr[i][j] = max({ tr[i-1][j], tr[i][j+1], sqsum(i, j+k-1, k) });
    }

    for (int i = n-k+1; i >= 1; --i)
    for (int j = k; j <= m; ++j) {
        bl[i][j] = max({ bl[i+1][j], bl[i][j-1], sqsum(i+k-1, j, k) });
    }

    for (int i = n-k+1; i >= 1; --i)
    for (int j = m-k+1; j >= 1; --j) {
        br[i][j] = max({ br[i+1][j], br[i][j+1], sqsum(i+k-1, j+k-1, k) });
    }

    int ans = 0;

    for (int i = k+1; i+k+k-1 <= n; ++i) {
        int tmp = 0;
        for (int j = k; j <= m; ++j) tmp = max(tmp, sqsum(i+k-1, j, k));
        ans = max(ans, tl[i-1][m] + tmp + bl[i+k][m]);
    }

    for (int j = k+1; j+k+k-1 <= m; ++j) {
        int tmp = 0;
        for (int i = k; i <= n; ++i) tmp = max(tmp, sqsum(i, j+k-1, k));
        ans = max(ans, tl[n][j-1] + tmp + tr[n][j+k]);
    }

    for (int i = k+1; i+k-1 <= n; ++i)
    for (int j = k+1; j+k-1 <= m; ++j) {
        ans = max(ans, tl[i-1][m] + bl[i][j-1] + br[i][j]);
        ans = max(ans, tl[i-1][j-1] + tr[i-1][j] + bl[i][m]);
        ans = max(ans, tl[n][j-1] + tr[i-1][j] + br[i][j]);
        ans = max(ans, tl[i-1][j-1] + bl[i][j-1] + tr[n][j]);
    }

    cout << ans;
    return 0;
}
