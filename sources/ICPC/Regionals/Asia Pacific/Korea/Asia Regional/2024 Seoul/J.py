"""
# ICPC, Regionals, Asia Pacific, Korea,
# 2024 ICPC Asia Seoul Regional J. Street Development
# JUNGOL 11261
#
# binary search, two pointers
# Date: 2026.5.6
"""

def main() -> None:
    import sys
    rd = lambda: sys.stdin.readline().rstrip()

    L, n = map(int, rd().split())
    a = list(map(int, rd().split()))

    def decide(m):
        l, r = 0, n - 1
        lpos, rpos = 0, L

        while l < r:
            if m < a[l] - lpos: return False
            next_lpos = min(a[l + 1], lpos + (m - a[l] + lpos))
            if m < rpos - a[r]: return False
            next_rpos = max(a[r - 1], rpos - (m - rpos + a[r]))

            if a[l + 1] - next_lpos < next_rpos - a[r - 1]:
                lpos, l = next_lpos, l + 1
            else:
                rpos, r = next_rpos, r - 1

        return m >= (rpos - lpos) + min(a[l] - lpos, rpos - a[l])

    lo, hi = 0, L
    while lo + 1 < hi:
        mid = (lo + hi) // 2
        if decide(mid): hi = mid
        else: lo = mid
    print(hi)


if __name__ == "__main__":
    main()
