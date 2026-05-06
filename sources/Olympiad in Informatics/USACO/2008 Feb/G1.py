"""
# USA Computing Olympiad, USACO February 2008 Contest, Gold 1. Making the Grade
# JUNGOL 4980
#
# greedy, DP
# Date: 2026.5.6
"""

def main() -> None:
    import sys
    rd = lambda: sys.stdin.readline().rstrip()

    n = int(rd())
    a = [int(rd()) for _ in range(n)]
    sa = sorted(a)

    f = [[0] * n for _ in range(n)]

    for j in range(n):
        f[0][j] = abs(a[0] - sa[j])

    for i in range(1, n):
        g = 2**60
        for j in range(n):
            g = min(g, f[i - 1][j])
            f[i][j] = g + abs(a[i] - sa[j])

    print(min(f[-1]))


if __name__ == "__main__":
    main()
