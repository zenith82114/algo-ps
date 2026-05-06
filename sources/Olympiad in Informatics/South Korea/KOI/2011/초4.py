"""
# 한국정보올림피아드, KOI 2011, 초등부 4. 전구
# BOJ 2449
# JUNGOL 2500
#
# DP
# Date: 2025.6.21
"""

def main() -> None:
    import sys
    rd = lambda: sys.stdin.readline().rstrip()

    n, k = map(int, rd().split())
    a = list(map(int, rd().split()))

    mem = [[-1] * n for _ in range(n)]

    def dp(i, j):
        if mem[i][j] == -1:
            if i == j:
                mem[i][j] = 0
            else:
                t = 10**9
                for k in range(i, j):
                    t = min(t, dp(i, k) + dp(k + 1, j) + int(a[i] != a[k + 1]))
                mem[i][j] = t
        return mem[i][j]
    print(dp(0, n - 1))


if __name__ == "__main__":
    main()
