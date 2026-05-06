"""
# USA Computing Olympiad, USACO 2023 December Contest, Gold 2. Minimum Longest Trip
# BOJ 31058
# JUNGOL 6097
#
# DAG DP
# Date: 2025.1.12
"""

def main() -> None:
    import sys
    rd = sys.stdin.readline
    from bisect import bisect

    n, m = map(int, rd().split())
    gr = [[] for _ in range(n + 1)]
    deg = [0] * (n + 1)
    for _ in range(m):
        x, y, w = map(int, rd().split())
        gr[y].append((x, w))
        deg[x] += 1
    layer = [0] * (n + 1)
    w_sum = [0] * (n + 1)
    dp = [(1, 0, 0) for _ in range(n + 1)]
    rank = [0] * (n + 1)

    q = [x for x in range(1, n + 1) if deg[x] == 0]
    while q:
        nq = []
        v = []
        for x in q:
            for y, w in gr[x]:
                layer[y] = layer[x] + 1
                t = (-layer[x], w, rank[x])
                if dp[y] > t:
                    dp[y] = t
                    w_sum[y] = w + w_sum[x]
                deg[y] -= 1
                if deg[y] == 0:
                    nq.append(y)
                    v.append(dp[y][1:])
        v.sort()
        for y in nq:
            rank[y] = bisect(v, dp[y][1:])
        q = nq

    for x in range(1, n + 1):
        print(layer[x], w_sum[x])


if __name__ == "__main__":
    main()
