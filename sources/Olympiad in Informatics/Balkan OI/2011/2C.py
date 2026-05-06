"""
# Balkan Olympiad in Informatics, BOI 2011 Day 2 C. trapezoid
# BOJ 5258
# JUNGOL 3629
#
# DP, segment tree, priority queue
# Date: 2025.4.9
"""

def main() -> None:
    import sys
    rd = sys.stdin.readline
    import bisect
    import heapq

    TN = 2**18
    segt = [(0, 0) for _ in range(2 * TN)]

    def merge(x: tuple, y: tuple) -> tuple:
        if x[0] != y[0]:
            return max(x, y)
        return (x[0], (x[1] + y[1]) % 30013)

    def update(i: int, x: tuple) -> None:
        i += TN
        segt[i] = x
        while i:
            segt[i // 2] = merge(segt[i], segt[i ^ 1])
            i //= 2

    def query(j: int) -> tuple:
        i, j = TN, TN + j
        ret = (0, 0)
        while i <= j:
            if i & 1:
                ret = merge(ret, segt[i])
                i += 1
            if ~j & 1:
                ret = merge(ret, segt[j])
                j -= 1
            i, j = i // 2, j // 2
        return ret

    INF = 10**9 + 1
    v = [(INF, INF, INF, INF)]
    cds = [INF]
    n = int(rd())
    for _ in range(n):
        a, b, c, d = map(int, rd().split())
        cds.append(c)
        cds.append(d)
        v.append((a, b, c, d))
    cds.sort()

    def enc(z: int) -> int:
        # ci, di ~> [1 .. 2n]
        # INF ~> 2n + 1
        return bisect.bisect(cds, z)

    update(0, (0, 1))
    pq = []

    for ai, bi, ci, di in sorted(v):
        while pq:
            bj, dj, fj, gj = pq[0]
            if bj < ai:
                heapq.heappop(pq)
                update(enc(dj), (fj, gj))
            else:
                break
        fi, gi = query(enc(ci))
        heapq.heappush(pq, (bi, di, fi + 1, gi))

    _, _, f, g = pq[0]
    print(f - 1, g)


if __name__ == "__main__":
    main()
