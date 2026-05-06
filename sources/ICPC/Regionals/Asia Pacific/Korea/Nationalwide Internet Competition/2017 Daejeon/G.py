"""
# ICPC, Regionals, Asia Pacific, Korea,
# Daejeon Nationalwide Internet Competition 2017 G. Map Labeling
# BOJ 14752
#
# DP
# Date: 2024.10.8
"""

import sys


def main() -> None:
    rd = sys.stdin.readline
    n = int(rd())
    a = list(int(rd()) for _ in range(n))
    w = list(int(rd()) for _ in range(n))
    v = sorted(list(zip(a, w)))

    dp = [n] * n
    dp[-1] = 0
    for i in reversed(range(n - 1)):
        x, cnt = v[i][0], 0
        for j in range(i + 1, n):
            aj, wj = v[j]
            if x + wj <= aj:
                dp[i] = min(dp[i], cnt + dp[j])
            if not (x <= aj <= x + wj):
                cnt += 1
            x += wj
        dp[i] = min(dp[i], cnt)

    print(min(i + dp[i] for i in range(n)))


if __name__ == "__main__":
    main()
