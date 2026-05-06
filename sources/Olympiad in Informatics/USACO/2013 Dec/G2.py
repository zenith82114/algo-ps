"""
# USA Computing Olympiad, USACO December 2013 Contest, Gold 2. Optimal Milking
# BOJ 9867
# JUNGOL 3855
#
# DnC, segment tree
# Date: 2025.7.24
"""

def main() -> None:
    import sys
    rd = lambda: sys.stdin.readline().rstrip()
    inf = 10**20

    n, d = map(int, rd().split())
    tn = 1
    while tn <= n:
        tn *= 2
    segt = [[0, 0, 0, -inf] for _ in range(2 * tn)]
    for i in range(1, n + 1):
        segt[tn + i][3] = int(rd())

    def pull(i):
        lc, rc = segt[2*i], segt[2*i + 1]
        segt[i][0] = max(lc[0] + rc[0], lc[0] + rc[2], lc[1] + rc[0])
        segt[i][1] = max(lc[0] + rc[1], lc[0] + rc[3], lc[1] + rc[1])
        segt[i][2] = max(lc[2] + rc[0], lc[2] + rc[2], lc[3] + rc[0])
        segt[i][3] = max(lc[2] + rc[1], lc[2] + rc[3], lc[3] + rc[1])

    for i in reversed(range(1, tn)):
        pull(i)

    ans = 0
    for _ in range(d):
        i, m = map(int, rd().split())
        i += tn
        segt[i][3] = m
        i //= 2
        while i:
            pull(i)
            i //= 2
        ans += max(segt[1])
    print(ans)


if __name__ == "__main__":
    main()
