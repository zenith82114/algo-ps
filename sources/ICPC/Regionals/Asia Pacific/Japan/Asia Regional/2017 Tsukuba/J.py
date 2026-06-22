"""
# ICPC, Regionals, Asia Pacific, Japan, 2017 ACM-ICPC Asia Tsukuba Regional Contest
# J. String Puzzle
# QOJ 3291
#
# ad-hoc
# Date: 2026.6.22
"""

def main() -> None:
    import sys
    rd = lambda: sys.stdin.readline().rstrip()

    n, a, b, q = map(int, rd().split())

    xc = []
    for _ in range(a):
        x, c = rd().split()
        xc.append((int(x), c))

    y, h = [0], [0]
    for _ in range(b):
        yi, hi = map(int, rd().split())
        y.append(yi)
        h.append(hi)

    def _find_root(x):
        i = b
        while True:
            while i > 0 and x < y[i]: i -= 1
            if h[i] == 0: break
            x = h[i] + ((x - y[i]) % (y[i] - h[i]))
        return x

    lut = {_find_root(x) : c for x, c in xc}

    print(''.join(
        lut.get(_find_root(int(rd())), '?') for _ in range(q)
    ))


if __name__ == "__main__":
    main()
