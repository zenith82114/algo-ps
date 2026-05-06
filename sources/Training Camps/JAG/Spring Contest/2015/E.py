"""
# ICPC Japanese Alumni Group, JAG Spring Contest 2015 E. Cost Performance Flow
# BOJ 11710 - min cost flow
# Date: 2025.11.18
"""

def main() -> None:
    import sys
    rd = lambda: sys.stdin.readline().rstrip()
    from collections import deque
    from fractions import Fraction
    INF = 10**9

    n, m = map(int, rd().split())
    s, t = map(int, rd().split())
    g = [[] for _ in range(n + 1)]
    capa, cost = [], []

    def add_edge(x, y, u, c):
        g[x].append((y, len(capa)))
        capa.append(u)
        cost.append(c)
        g[y].append((x, len(capa)))
        capa.append(0)
        cost.append(-c)

    for _ in range(m):
        add_edge(*map(int, rd().split()))

    dist, pred = [], []

    def spfa():
        dist[:] = [INF] * (n + 1)
        dist[s] = 0
        pred[:] = [None] * (n + 1)
        q = deque([s])
        inq = [0] * (n + 1)
        while q:
            x = q.popleft()
            inq[x] = 0
            for y, e in g[x]:
                if capa[e] > 0 and dist[y] > dist[x] + cost[e]:
                    dist[y] = dist[x] + cost[e]
                    pred[y] = (x, e)
                    if not inq[y]:
                        q.append(y)
                        inq[y] = 1
        return dist[t] < INF

    M = 0
    pieces = []
    while spfa():
        df = INF
        y = t
        while y != s:
            x, e = pred[y]
            df = min(df, capa[e])
            y = x
        y = t
        while y != s:
            x, e = pred[y]
            capa[e] -= df
            capa[e^1] += df
            y = x
        M += df
        pieces.append((df, dist[t]))

    x, y, ans = 0, 0, Fraction(M**2)
    for fi, ci in pieces:
        x_star = Fraction(M - ci*y + ci*ci*x, 1 + ci*ci)
        if x < x_star < x + fi:
            y_star = y + ci * (x_star - x)
            ans = y_star**2 + (M - x_star)**2
            break
        x += fi
        y += fi * ci
        ans = min(ans, y**2 + (M - x)**2)

    print(f"{ans.numerator}/{ans.denominator}")


if __name__ == "__main__":
    main()
