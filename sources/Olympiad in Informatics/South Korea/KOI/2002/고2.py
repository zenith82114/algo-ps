"""
# 한국정보올림피아드, KOI 2002, 고등부 2. 헬기착륙장
# BOJ 2626
# JUNGOL 1585
#
# minimum enclosing circle; Welzl's algorithm
# Date: 2025.6.14
"""

def main() -> None:
    import sys
    rd = lambda: sys.stdin.readline().rstrip()
    sys.setrecursionlimit(4096)
    import random
    from math import hypot as l2norm
    eps = 1e-9

    n = int(rd())
    p = [tuple(map(float, rd().split())) for _ in range(n)]
    random.shuffle(p)
    s = []

    def solve():
        if len(p) == 0:
            if len(s) == 0:
                return 0.0, 0.0, -1.0
            if len(s) == 1:
                return s[0][0], s[0][1], 0.0
            if len(s) == 2:
                x0, y0 = s[0]
                x1, y1 = s[1]
                return (x0 + x1) / 2, (y0 + y1) / 2, l2norm(x1 - x0, y1 - y0) / 2
        if len(s) == 3:
            x0, y0 = s[0]
            x1, y1 = s[1]
            x2, y2 = s[2]
            bx, by = x1 - x0, y1 - y0
            cx, cy = x2 - x0, y2 - y0
            d = 2 * (bx * cy - by * cx)
            assert abs(d) > eps
            x = ((bx * bx + by * by) * cy - (cx * cx + cy * cy) * by) / d
            y = ((cx * cx + cy * cy) * bx - (bx * bx + by * by) * cx) / d
            r = l2norm(x, y)
            return x + x0, y + y0, r

        u = p.pop()
        x, y, r = solve()
        if l2norm(u[0] - x, u[1] - y) < r + eps:
            p.append(u)
            return x, y, r
        s.append(u)
        x, y, r = solve()
        p.append(s.pop())
        return x, y, r

    x, y, r = solve()
    print(f"{x:.3f} {y:.3f}")
    print(f"{r:.3f}")


if __name__ == "__main__":
    main()
