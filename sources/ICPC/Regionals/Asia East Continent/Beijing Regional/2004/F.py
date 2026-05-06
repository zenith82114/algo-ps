"""
# ICPC, Regionals, Asia East Continent, China, Beijing,
# Beijing Regional Contest 2004 F. Color a Tree
# BOJ 1763 - greedy
# Date: 2026.4.13
"""

def main() -> None:
    import sys
    rd = lambda: sys.stdin.readline().rstrip()

    n, root = map(int, rd().split())
    c = [0] + list(map(int, rd().split()))
    par = [-1] * (n + 1)
    for _ in range(n - 1):
        x, y = map(int, rd().split())
        par[y] = x

    dsu = list(range(n + 1))

    def _find(x):
        if dsu[x] == x: return x
        dsu[x] = _find(dsu[x])
        return dsu[x]

    sz = [1] * (n + 1)
    ans = sum(c)

    for _ in range(n - 1):
        x = 0
        for y in range(1, n + 1):
            if y == root or _find(y) != y: continue
            if c[x]*sz[y] < c[y]*sz[x]: x = y
        p = _find(par[x])
        ans += c[x]*sz[p]
        c[p] += c[x]
        sz[p] += sz[x]
        dsu[x] = p

    print(ans)


if __name__ == "__main__":
    main()
