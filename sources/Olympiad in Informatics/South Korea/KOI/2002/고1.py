"""
# 한국정보올림피아드, KOI 2002, 고등부 1. 경로찾기
# JUNGOL 1677
#
# DP
# Date: 2026.4.30
"""

def main() -> None:
    import sys
    rd = lambda: sys.stdin.readline().rstrip()

    n = int(rd())

    l = [0] * n
    r = [0] * n
    dp = [[-2**32] * n for _ in range(2)]
    dp[1][0] = 0

    for i in range(n):
        pre, now = ~i&1, i&1
        a = list(map(int, rd().split()))

        l[0] = a[0] + dp[pre][0]
        for j in range(1, n):
            l[j] = a[j] + max(dp[pre][j], l[j - 1])

        r[-1] = a[-1] + dp[pre][-1]
        for j in reversed(range(n - 1)):
            r[j] = a[j] + max(dp[pre][j], r[j + 1])

        for j in range(n):
            dp[now][j] = max(l[j], r[j])

    print(dp[now][-1])


if __name__ == "__main__":
    main()
