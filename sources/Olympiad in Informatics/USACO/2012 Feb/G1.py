"""
# USA Computing Olympiad, USACO February 2012 Contest, Gold 1. Cow Coupons
# BOJ 5896
# JUNGOL 3762
#
# min cost flow, priority queue
# Date: 2025.12.26
"""

def main() -> None:
    import sys
    import heapq as H
    INF = 10**10

    it = iter(sys.stdin.read().split())
    N = int(next(it))
    K = int(next(it))
    M = int(next(it))
    P, C = [], []
    for _ in range(N):
        P.append(int(next(it)))
        C.append(int(next(it)))

    buy = [0] * N
    q0 = [(P[i], i) for i in range(N)]; H.heapify(q0)
    q1 = [(C[i], i) for i in range(N)]; H.heapify(q1)
    q2 = []
    k = 0

    for _ in range(N):
        opt = [INF] * 3
        opt[0] = q0[0][0]
        if k < K: opt[1] = q1[0][0]
        if k > 0: opt[2] = q2[0][0] + q1[0][0]

        x = opt.index(min(opt))
        if x == 0:
            i = q0[0][1]
            M -= P[i]
            if M < 0: break
            buy[i] = 1
        elif x == 1:
            i = q1[0][1]
            M -= C[i]
            if M < 0: break
            k += 1
            buy[i] = 1
            H.heappush(q2, (P[i] - C[i], i))
        else:
            i, j = q2[0][1], q1[0][1]
            M -= P[i] - C[i] + C[j]
            if M < 0: break
            buy[j] = 1
            H.heappop(q2)
            H.heappush(q2, (P[j] - C[j], j))

        while q0 and buy[q0[0][1]]: H.heappop(q0)
        while q1 and buy[q1[0][1]]: H.heappop(q1)

    print(sum(buy))


if __name__ == "__main__":
    main()
