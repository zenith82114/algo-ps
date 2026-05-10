"""
# Baltic Olympiad in Informatics, BOI 2011 Day 2 A. Meeting
# JUNGOL 1189
#
# mathematics
# Date: 2026.5.10
"""

def main() -> None:
    import sys
    rd = lambda: sys.stdin.readline().rstrip()
    import math

    n, P, V = map(int, rd().split())
    if n == 1:
        print(0)
        return

    ans = P*n + V
    k = 2
    while 2**k <= n:
        m = math.floor(pow(n, 1/k))
        prod = m**k
        l = 0
        while prod < n:
            prod = (prod // m) * (m + 1)
            l += 1
        ans = min(ans, P*(k*m + l) + V*k)
        k += 1

    print(ans)


if __name__ == "__main__":
    main()
