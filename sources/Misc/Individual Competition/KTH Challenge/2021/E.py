"""
# KTH Challenge, KTH Challenge 2021 E. Even Electricity
# Q22038 - greedy, binary search
# Date: 2026.2.3
"""

def main() -> None:
    import sys
    rd = lambda: sys.stdin.readline().rstrip()
    INF = 10**15

    n, r = map(int, rd().split())
    s = [0] * n
    I = [0] * n
    for i in range(n):
        s[i], w_i = map(int, rd().split())
        I[i] = I[i - 1] + s[i] + w_i

    def check(L, R):
        a, b = 0, 0
        for i in range(n):
            if R < s[i]: return False
            a = max(a + max(s[i], L), I[i] - (r if i < n - 1 else 0))
            b = min(b + R, I[i])
            if a > b: return False
        return True

    lo, hi = -1, INF
    while lo + 1 < hi:
        mid = (lo + hi) // 2
        if check(mid, INF): lo = mid
        else: hi = mid
    L = lo
    lo, hi = -1, INF
    while lo + 1 < hi:
        mid = (lo + hi) // 2
        if check(-INF, mid): hi = mid
        else: lo = mid
    R = hi

    assert L <= R
    print(R - L)


if __name__ == "__main__":
    main()
