"""
# ICPC, Regionals, Europe, Southeastern Europe Regional Contest,
# SEERC 2020 A. Archeologists
# BOJ 21905
# JUNGOL 16169
#
# min cost flow, priority queue; slope trick
# Date: 2026.1.6
"""

def main() -> None:
    import sys
    rd = lambda: sys.stdin.readline().rstrip()
    import heapq as H

    n = int(rd())
    p = list(map(int, rd().split()))
    for i in range(1, n): p[i] += p[i - 1]

    pq = [0]
    ans = 0

    for i in range(n):
        H.heappush(pq, p[i])
        if p[i] > pq[0]:
            ans += p[i] - pq[0]
            H.heapreplace(pq, p[i])

    print(ans)


if __name__ == "__main__":
    main()
