"""
# Petrozavodsk Programming Camp, Winter 2017, Day 1: Jagiellonian U Contest F. Factory
# BOJ 19352 - gradient descent, ternary search
# Date: 2025.3.20
"""

def main() -> None:
    import sys
    rd = sys.stdin.readline
    from math import hypot as l2norm
    eps = 1e-9

    for _ in range(int(rd())):
        n = int(rd())
        p = list(tuple(map(int, rd().split())) for _ in range(n))

        def f(x, y):
            return sum(l2norm(x - xi, y - yi) for xi, yi in p)

        def grad_f(x, y):
            gx, gy = 0., 0.
            for xi, yi in p:
                n = l2norm(x - xi, y - yi)
                if n >= eps:
                    gx += (x - xi) / n
                    gy += (y - yi) / n
            n = l2norm(gx, gy)
            return (gx / n, gy / n) if n >= eps else None

        x0, y0 = 0., 0.
        f0 = f(x0, y0)
        delta = 1.
        while delta > eps:
            g = grad_f(x0, y0)
            if g is None:
                delta = 0.
                break
            gx, gy = g
            l, r = 0., 1e7
            while l + eps < r:
                m1 = (2 * l + r) / 3
                m2 = (l + 2 * r) / 3
                x1 = x0 - m1 * gx
                y1 = y0 - m1 * gy
                x2 = x0 - m2 * gx
                y2 = y0 - m2 * gy
                if f(x1, y1) > f(x2, y2):
                    l = m1
                else:
                    r = m2
            x1 = x0 - l * gx
            y1 = y0 - l * gy
            f1 = f(x1, y1)
            delta = (f0 - f1) / f0
            x0, y0, f0 = x1, y1, f1

        print(x0, y0)


if __name__ == "__main__":
    main()
