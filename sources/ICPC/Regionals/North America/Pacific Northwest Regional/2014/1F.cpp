/*
 * ICPC, Regionals, North America,
 * 2014 Pacific Northwest Region Programming Contest, Division 1 F. Knights
 * BOJ 10562 - bitmask DP by matrix exponentiation
 * Date: 2023.1.21
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;
constexpr i64 MOD = 1'000'000'009ll;

int A[256][256], P[256][256], temp[256][256];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int T; cin >> T;
    while (T--) {
        int M, N; cin >> M >> N;
        const int W = 1<<(2*M);

        for (int i = 0; i < W; ++i)
        for (int j = 0; j < W; ++j)
            A[i][j] = 0;

        for (int i = 0; i < W; ++i) {
            int m0 = i>>M;
            int m1 = i ^ (m0<<M);
            int m2 = ((1<<M) -1) & ~((m0<<1) | (m0>>1) | (m1<<2) | (m1>>2));

            int t = 0;
            do {
                int j = (m1<<M) | t;
                A[j][i] = 1;
            } while ((t = (t - m2) & m2));
        }

        for (int i = 0; i < W; ++i)
        for (int j = 0; j < W; ++j)
            P[i][j] = i == j? 1 : 0;

        while (N) {
            if (N & 1) {
                for (int i = 0; i < W; ++i)
                for (int j = 0; j < W; ++j)
                    temp[i][j] = 0;

                for (int k = 0; k < W; ++k)
                for (int i = 0; i < W; ++i)
                for (int j = 0; j < W; ++j) {
                    int x = ((i64)P[i][k] * A[k][j]) % MOD;
                    temp[i][j] = (temp[i][j] + x) % MOD;
                }

                for (int i = 0; i < W; ++i)
                for (int j = 0; j < W; ++j)
                    P[i][j] = temp[i][j];
            }

            N >>= 1;

            for (int i = 0; i < W; ++i)
            for (int j = 0; j < W; ++j)
                temp[i][j] = 0;

            for (int k = 0; k < W; ++k)
            for (int i = 0; i < W; ++i)
            for (int j = 0; j < W; ++j) {
                int x = ((i64)A[i][k] * A[k][j]) % MOD;
                temp[i][j] = (temp[i][j] + x) % MOD;
            }

            for (int i = 0; i < W; ++i)
            for (int j = 0; j < W; ++j)
                A[i][j] = temp[i][j];
        }

        int ans = 0;
        for (int i = 0; i < W; ++i) ans = (ans + P[i][0]) % MOD;
        cout << ans << '\n';
    }

    return 0;
}
