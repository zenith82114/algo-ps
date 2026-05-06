"""
# ICPC, World Finals, ACM-ICPC World Finals 2013 B. Hey, Better Bettor
# JUNGOL 10766
#
# probability theory, coordinate descent, ternary search
# Date: 2026.5.6
"""

def main() -> None:
    import sys
    rd = lambda: sys.stdin.readline().rstrip()

    x, p = map(float, rd().split())
    if p == 0.:
        print(0.)
        return
    k = 1. - x / 100.
    r = (100. - p) / p

    def f(a, b):
        w = (pow(r, -b) - pow(r, -a-b)) / (1. - pow(r, -a-b))
        return b*w - k*a*(1 - w)

    a, b = 1, 1
    y_curr = 0.
    delta = float('inf')

    while delta > 1e-9:
        y_next = y_curr

        lo, hi = 1, 10**6
        while lo + 2 < hi:
            m1 = lo + (hi - lo) // 3; y1 = f(a, m1)
            m2 = hi - (hi - lo) // 3; y2 = f(a, m2)
            if y1 < y2: lo = m1
            else: hi = m2
        for m in range(lo, hi + 1):
            y_this = f(a, m)
            if y_next < y_this: y_next, b = y_this, m

        lo, hi = 1, 10**6
        while lo + 2 < hi:
            m1 = lo + (hi - lo) // 3; y1 = f(m1, b)
            m2 = hi - (hi - lo) // 3; y2 = f(m2, b)
            if y1 < y2: lo = m1
            else: hi = m2
        for m in range(lo, hi + 1):
            y_this = f(m, b)
            if y_next < y_this: y_next, a = y_this, m

        y_curr, delta = y_next, y_next - y_curr

    print(y_curr)


if __name__ == "__main__":
    main()
