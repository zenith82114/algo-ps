"""
# POI Training Camp, ONTAK 2010 3-3. Vacation
# BOJ 8472 - min cost flow
# Date: 2025.11.22
"""

def main() -> None:
    import sys
    rd = lambda: sys.stdin.readline().rstrip()
    from collections import deque
    INF = 10**9

    n, k = map(int, rd().split())
    a = list(map(int, rd().split()))
    s, t = 2*n + 2, 2*n + 3
    v = t + 1

    g = [[] for _ in range(v)]
    capa, cost = [], []

    def add_edge(x, y, c, w):
        g[x].append((y, len(capa)))
        capa.append(c)
        cost.append(w)
        g[y].append((x, len(capa)))
        capa.append(0)
        cost.append(-w)

    add_edge(s, 0, k, 0)
    add_edge(2*n + 1, t, k, 0)
    for j in range(2*n + 1):
        add_edge(j, j + 1, k, 0)
    for i in range(3*n):
        add_edge(max(0, i - n + 1), min(i, 2*n) + 1, 1, -a[i])

    dist, pred = [], []

    def spfa():
        dist[:] = [INF] * v
        dist[s] = 0
        pred[:] = [None] * v
        q = deque([s])
        inq = [0] * v
        while q:
            x = q.popleft()
            inq[x] = 0
            for y, e in g[x]:
                if capa[e] and dist[y] > dist[x] + cost[e]:
                    dist[y] = dist[x] + cost[e]
                    pred[y] = (x, e)
                    if not inq[y]:
                        q.append(y)
                        inq[y] = 1
        return pred[t] is not None

    ans = 0
    while spfa():
        flow = INF
        y = t
        while y != s:
            x, e = pred[y]
            flow = min(flow, capa[e])
            y = x
        y = t
        while y != s:
            x, e = pred[y]
            ans += flow * cost[e]
            capa[e] -= flow
            capa[e^1] += flow
            y = x

    print(-ans)


if __name__ == "__main__":
    main()
