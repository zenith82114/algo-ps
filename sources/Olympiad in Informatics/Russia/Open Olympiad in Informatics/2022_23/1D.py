"""
# Russia Open Olympiad in Informatics 2022/2023 Day 1 DOOM. Музыкальный фестиваль
# BOJ 30635 - DP
# Date: 2025.11.7
"""

def main() -> None:
    import sys
    rd = lambda: sys.stdin.readline().rstrip()

    n = int(rd())
    g = [[] for _ in range(200_001)]
    m = [0] * n

    for i in range(n):
        rd()
        for x in map(int, rd().split()):
            if m[i] < x:
                m[i] = x
                g[x].append(i)

    dp = [0] * n
    z = 0
    for x in range(1, 200_001):
        nz = z
        for i in g[x]:
            dp[i] = max(dp[i], z) + 1
            if x == m[i]:
                nz = max(nz, dp[i])
        z = nz
    print(max(dp))


if __name__ == "__main__":
    main()
