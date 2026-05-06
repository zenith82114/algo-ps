"""
# ICPC Japanese Alumni Group, JAG Summer Camp 2011 Day 2 E. Entangled with Lottery
# BOJ 22498 - DP, probability
# Date: 2024.7.30
"""

import sys


def main() -> None:
    rd = sys.stdin.readline
    H, N, P, M, K = map(int, rd().split())
    t = [0 for _ in range(H + 1)]
    for _ in range(M):
        a, b = map(int, rd().split())
        t[a] = b
    st = [0 for _ in range(H + 1)]
    for i in range(1, H + 1):
        st[i] = st[i - 1] + (t[i] == 0)

    dp = [[[0. for _ in range(K + 1)]
           for _ in range(N + 1)]
           for _ in range(H + 1)]
    dp[H][P][0] = 1.

    for i in range(H, 0, -1):
        for j in range(1, N + 1):
            for k in range(0, K + 1):

                if t[i] == 0:
                    q = (K - k) / st[i]
                    dp[i - 1][j][k] += dp[i][j][k] * (1 - q)
                    if k != K:
                        if j != 1:
                            dp[i - 1][j - 1][k + 1] += dp[i][j][k] * q / (N - 1)
                        if j != N:
                            dp[i - 1][j + 1][k + 1] += dp[i][j][k] * q / (N - 1)
                        if j in [1, N]:
                            dp[i - 1][j][k + 1] += dp[i][j][k] * q * (1 - 1 / (N - 1))
                        else:
                            dp[i - 1][j][k + 1] += dp[i][j][k] * q * (1 - 2 / (N - 1))
                else:
                    if j == t[i]:
                        dp[i - 1][j + 1][k] += dp[i][j][k]
                    elif j == t[i] + 1:
                        dp[i - 1][j - 1][k] += dp[i][j][k]
                    else:
                        dp[i - 1][j][k] += dp[i][j][k]

    ans = 0.
    for j in range(1, N + 1):
        ans = max(ans, dp[0][j][K])
    print(ans)


if __name__ == "__main__":
    main()
