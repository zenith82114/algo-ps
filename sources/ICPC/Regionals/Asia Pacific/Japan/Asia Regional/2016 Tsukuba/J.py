"""
# ICPC, Regionals, Asia Pacific, Japan,
# Asia Regional Contest 2016 in Tsukuba J. Cover the Polygon with Your Disk
# JUNGOL 13765
#
# geometry, gradient descent(ascent), ternary search
# Date: 2026.5.30
"""

from math import atan2, pi, sqrt

def eval_area(p, x, y, r):
    n = len(p)
    h = []
    for i in range(n):
        (x1, y1), (x2, y2) = p[i], p[(i+1)%n]
        x1, y1, x2, y2 = x1-x, y1-y, x2-x, y2-y
        if x1*x1 + y1*y1 <= r*r:
            h.append( (x1, y1, 0) )

        a = (x2-x1)**2 + (y2-y1)**2
        b = x1*(x2-x1) + y1*(y2-y1)
        c = x1*x1 + y1*y1 - r*r
        d = b*b - a*c
        if d < 0: continue
        rtd = sqrt(d)
        t1, t2 = (-b-rtd)/a, (-b+rtd)/a
        if 0 < t1 < 1:
            h.append( ((1-t1)*x1 + t1*x2, (1-t1)*y1 + t1*y2, 0) )
        if 0 < t2 < 1:
            h.append( ((1-t2)*x1 + t2*x2, (1-t2)*y1 + t2*y2, 1) )

    m = len(h)
    if m == 0: return pi*r*r
    area = 0.
    for i in range(m):
        x1, y1, s = h[i]
        x2, y2, _ = h[(i+1)%m]
        if s == 0:
            area += .5 * (x1*y2 - x2*y1)
        else:
            theta = atan2(y2, x2) - atan2(y1, x1)
            if theta < -1e-5: theta += 2*pi
            area += .5 * r*r * theta
    return area


def eval_grad(p, x, y, r):
    eps = 1e-5
    fx1 = eval_area(p, x+eps, y, r)
    fx2 = eval_area(p, x-eps, y, r)
    fy1 = eval_area(p, x, y+eps, r)
    fy2 = eval_area(p, x, y-eps, r)
    gx = (fx1-fx2) / (2*eps)
    gy = (fy1-fy2) / (2*eps)

    mag = sqrt(gx**2 + gy**2)
    if mag < eps: return None, None
    return gx/mag, gy/mag


def ccw(a, b, c):
    (ax, ay), (bx, by), (cx, cy) = a, b, c
    x1, x2, y1, y2 = bx-ax, cx-ax, by-ay, cy-ay
    return x1*y2 - x2*y1


def find_bound(p, x, y, gx, gy):
    n = len(p)
    x, y = x + 1e-5*gx, y + 1e-5*gy
    a, b = (x, y), (x+gx, y+gy)
    i = 0
    while ccw(a, b, p[i]) > 0 or ccw(a, b, p[(i+1)%n]) < 0: i += 1
    (x1, y1), (x2, y2) = p[i], p[(i+1)%n]
    x1, y1, x2, y2 = x-x1, y-y1, x2-x1, y2-y1
    return (x2*y1 - x1*y2) / (gx*y2 - gy*x2)


def main() -> None:
    n, r = map(int, input().split())
    p = []
    for _ in range(n):
        xi, yi = map(int, input().split())
        p.append( (xi, yi) )

    ans = 0.
    for i in range(n):
        x, y = p[i]
        max_f = f = eval_area(p, x, y, r)
        delta_f = 1e9
        while delta_f > 1e-6:
            gx, gy = eval_grad(p, x, y, r)
            if gx is None: break

            lo, hi = 0, find_bound(p, x, y, gx, gy)
            while hi - lo > 1e-4:
                m1, m2 = (2*lo + hi)/3, (lo + 2*hi)/3
                f1 = eval_area(p, x + m1*gx, y + m1*gy, r)
                f2 = eval_area(p, x + m2*gx, y + m2*gy, r)
                if f1 < f2: lo = m1
                else: hi = m2
            nx, ny = x + lo*gx, y + lo*gy
            nf = eval_area(p, nx, ny, r)
            max_f = max(max_f, nf)
            delta_f = nf - f
            x, y, f = nx, ny, nf
        ans = max(ans, max_f)

    print(ans)


if __name__ == "__main__":
    main()
