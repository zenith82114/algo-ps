"""
# ICPC, Regionals, Europe, Southeastern Europe Regional Contest,
# SEERC 2010 C. Largest Empty Circle on a Segment
# BOJ 3726 - geometry, calculus, binary search, sweep line
# Date: 2025.8.30
"""

def main() -> None:
    import sys
    rd = lambda: sys.stdin.readline().rstrip()
    from math import sqrt
    eps = 1e-9

    def c_range(r: float, s: tuple) -> tuple|None:
        (x0, y0), (x1, y1) = s
        dx, dy = x1 - x0, y1 - y0

        if dy == 0:
            if abs(y0) <= r:
                h = sqrt(max(0., r*r - y0*y0))
                return (x0 - h, x1 + h)
            else:
                return None

        def c(t, sgn):
            xt, yt = x0 + t*dx, y0 + t*dy
            return xt + sgn * sqrt(max(0., r*r - yt*yt))

        t_lo = max(0., (-y0/dy) - r/abs(dy))
        t_hi = min(1., (-y0/dy) + r/abs(dy))
        if t_lo > t_hi:
            return None

        c_lo = min(c(t_lo, -1), c(t_hi, -1))
        c_hi = max(c(t_lo, +1), c(t_hi, +1))

        y_star = r * abs(dx) / sqrt(dx*dx + dy*dy)
        for t_star in [(-y0 + y_star)/dy, (-y0 - y_star)/dy]:
            if t_lo + eps < t_star < t_hi - eps:
                c_lo = min(c_lo, c(t_star, -1))
                c_hi = max(c_hi, c(t_star, +1))

        return (c_lo, c_hi)


    for _ in range(int(rd())):
        n, L = map(int, rd().split())
        seg = []
        for _ in range(n):
            x0, y0, x1, y1 = map(int, rd().split())
            p0, p1 = (x0, y0), (x1, y1)
            if p0 > p1: p0, p1 = p1, p0
            seg.append((p0, p1))

        r_lo, r_hi = 0., 1e6
        while r_lo + eps < r_hi:
            r = (r_lo + r_hi) / 2
            q = [c_range(r, s) for s in seg]
            q = sorted(_ for _ in q if _ is not None)

            c = 0.
            for c_lo, c_hi in q:
                if c_lo < c - eps:
                    c = max(c, c_hi)
                else: break
            if c <= L:
                r_lo = r
            else:
                r_hi = r

        print(f"{r_lo:.3f}")


if __name__ == "__main__":
    main()
