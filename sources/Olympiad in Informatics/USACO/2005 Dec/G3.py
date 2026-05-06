"""
# USA Computing Olympiad, USACO December 2005 Contest, Gold 3. Layout
# BOJ 7040
#
# system of difference constraints
# Date: 2026.3.17
"""

def main() -> None:
    import sys
    rd = lambda: sys.stdin.readline().rstrip()
    INF = 10**10

    n, ml, md = map(int, rd().split())
    edges = []
    for _ in range(ml):
        i, j, d = map(int, rd().split())
        edges.append((i, j, d))
    for _ in range(md):
        i, j, d = map(int, rd().split())
        edges.append((j, i, -d))
    for i in range(1, n):
        edges.append((i + 1, i, 0))

    x = [0] * (n + 1)
    for _ in range(n - 1):
        for i, j, d in edges:
            x[j] = min(x[j], x[i] + d)
    for i, j, d in edges:
        if x[j] > x[i] + d:
            print(-1)
            return

    x[:] = [INF] * (n + 1); x[1] = 0
    for _ in range(n - 1):
        for i, j, d in edges:
            if x[i] < INF:
                x[j] = min(x[j], x[i] + d)
    print(x[n] if x[n] < INF else -2)


if __name__ == "__main__":
    main()
