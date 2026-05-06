"""
# 한국정보올림피아드, KOI 1999, 고등부 1. 검은점과 하얀점 연결
# BOJ 2647
# JUNGOL 1703
#
# DP
# Date: 2026.3.26
"""

def main() -> None:
    import sys
    rd = lambda: sys.stdin.readline().rstrip()
    INF = 10**9

    n = int(rd()) // 2
    a = rd()

    memo = [[[-1] * (n + 1) for _ in range(2*n)] for _ in range(2*n)]
    ans = []

    def dp(i, j, h):
        if j < i: return 0
        if h <= 0: return INF
        if (j - i + 1) & 1: return INF

        if memo[i][j][h] == -1:
            res = dp(i, j, h - 1)
            if a[i] != a[j]:
                res = min(res, (j - i + 2*h) + dp(i + 1, j - 1, h - 1))
            for k in range(i + 1, j, 2):
                res = min(res, dp(i, k, h) + dp(k + 1, j, h))

            memo[i][j][h] = res
        return memo[i][j][h]

    def trace(i, j, h):
        if j < i or h <= 0 or (j - i + 1) & 1: return

        opt = dp(i, j, h)
        if opt == dp(i, j, h - 1):
            trace(i, j, h - 1)
            return
        if a[i] != a[j] and opt == (j - i + 2*h) + dp(i + 1, j - 1, h - 1):
            ans.append((i, j))
            trace(i + 1, j - 1, h - 1)
            return
        for k in range(i + 1, j, 2):
            if opt == dp(i, k, h) + dp(k + 1, j, h):
                trace(i, k, h)
                trace(k + 1, j, h)
                return

    trace(0, 2*n - 1, n)
    print(dp(0, 2*n - 1, n))
    for i, j in sorted(ans):
        print(i + 1, j + 1)


if __name__ == "__main__":
    main()
