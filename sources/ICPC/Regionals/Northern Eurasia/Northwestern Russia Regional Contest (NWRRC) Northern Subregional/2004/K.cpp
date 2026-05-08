/*
 * ICPC, Regionals, Northern Eurasia,
 * Northwestern Russia Regional Contest Northern Subregional 2004 K. K-th Number
 * JUNGOL 7088
 *
 * merge sort tree, binary search
 * Date: 2026.5.8
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;
const int MAXLGN = 19;
const int MAXN = 1<<MAXLGN;

int ms[1 + MAXLGN][MAXN];

int count_le(int i, int j, int x) {
    int cnt = 0;
    for (int h = 0; i <= j; i >>= 1, j >>= 1, ++h) {
        if (i&1) {
            cnt += distance(
                ms[h] + (i << h),
                upper_bound(ms[h] + (i << h), ms[h] + ((i + 1) << h), x)
            );
            ++i;
        }
        if (~j&1) {
            cnt += distance(
                ms[h] + (j << h),
                upper_bound(ms[h] + (j << h), ms[h] + ((j + 1) << h), x)
            );
            --j;
        }
    }
    return cnt;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m; cin >> n >> m;
    int N = 1, lgN = 0;
    while (N <= n) N *= 2, ++lgN;

    memset(ms[0], 0x3f, N * sizeof(int));
    ms[0][0] = int(-1e9) - 1;
    for (int i = 1; i <= n; ++i) cin >> ms[0][i];

    for (int h = 0; h < lgN; ++h) {
        int d = 1<<h;
        for (int i = 0; i < N; i += 2*d) {
            int p = i, q = i + d, r = i;
            while (p < i + d && q < i + 2*d) {
                ms[h + 1][r++] = ms[h][ms[h][p] < ms[h][q] ? p++ : q++];
            }
            while (p < i + d)   ms[h + 1][r++] = ms[h][p++];
            while (q < i + 2*d) ms[h + 1][r++] = ms[h][q++];
        }
    }

    while (m--) {
        int i, j, k; cin >> i >> j >> k;
        int lo = 0, hi = n;
        while (lo + 1 < hi) {
            int mid = (lo + hi) / 2;
            (count_le(i, j, ms[lgN][mid]) < k ? lo : hi) = mid;
        }
        cout << ms[lgN][hi] << '\n';
    }

    return 0;
}
