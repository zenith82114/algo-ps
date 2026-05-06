/*
 * ICPC Japanese Alumni Group, JAG Practice Contest for ACM-ICPC Asia Regional 2015 K. Optimal Tournament
 * BOJ 13092 - Knuth's DP optimization
 * Date: 2023.9.23
 */

#include<bits/stdc++.h>
using namespace std;
constexpr int inf = (int)1e9;

int A[1000];
int dp0[1000][1000], dp1[1000][1000];
int opt[1000][1000];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);

    int N, M; cin >> N >> M;
    for (int i = 0; i < N; ++i) cin >> A[i];
    sort(A, A + N);

    for (int i = 0; i < N; ++i) {
        dp1[i][i] = 0;
        opt[i][i] = i;
        for (int j = i+1; j < N; ++j) {
            dp1[i][j] = inf;
            opt[i][j] = -1;
        }
    }

    for (int m = 0; m < M; ++m) {
        for (int i = 0; i < N; ++i)
        for (int j = i; j < N; ++j) {
            dp0[i][j] = dp1[i][j];
        }

        for (int d = 1; d < N; ++d) {
            for (int i = 0, j = d; j < N; ++i, ++j) {
                dp1[i][j] = inf;
                for (int k = opt[i][j-1]; k <= opt[i+1][j]; ++k) {
                    int tmp = dp0[i][k] + dp0[k+1][j] + A[j] - A[k];
                    if (dp1[i][j] > tmp) {
                        dp1[i][j] = tmp;
                        opt[i][j] = k;
                    }
                }
            }
        }
    }

    cout << dp1[0][N-1];
    return 0;
}
