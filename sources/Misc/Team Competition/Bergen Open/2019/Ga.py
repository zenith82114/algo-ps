"""
# Bergen Open, Bergen Open 2019 G. Great GDP
# QOJ 3950
#
# greedy, disjoint sets, priority queue
# Date: 2026.6.11
"""

def main() -> None:
    import sys
    rd = lambda: sys.stdin.readline().rstrip()
    sys.setrecursionlimit(101010)
    import heapq as H
    from fractions import Fraction

    n = int(rd())
    c = list(map(int, rd().split()))
    k = list(map(int, rd().split()))
    tr = [[] for _ in range(n)]
    for _ in range(n-1):
        x, y = map(int, rd().split())
        tr[x-1].append(y-1)
        tr[y-1].append(x-1)

    par = [-1] * n

    def dfs(x):
        for y in tr[x]:
            if y == par[x]: continue
            par[y] = x
            dfs(y)

    dfs(0)

    dsu = [-1] * n

    def _find(x) -> int:
        if dsu[x] < 0: return x
        dsu[x] = _find(dsu[x])
        return dsu[x]

    pq = [(Fraction(-c[x], k[x]), x) for x in range(n)]
    H.heapify(pq)
    seen = [False] * n

    while pq:
        fx, x = H.heappop(pq)
        if x == 0:
            print(float(-fx))
            return

        if seen[x]: continue
        seen[x] = True
        y = _find(par[x])
        c[y] += c[x]
        k[y] += k[x]
        dsu[x] = y
        H.heappush(pq, (Fraction(-c[y], k[y]), y))


if __name__ == "__main__":
    main()
