"""
# ICPC, Regionals, Europe, Southeastern Europe Regional Contest,
# SEERC 2013 E. A+B
# BOJ 9267 - number theory
# Date: 2025.11.1
"""

def main() -> None:
    import sys
    rd = lambda: sys.stdin.readline().rstrip()
    from math import gcd

    def egcd(a, b):
        if b == 0:
            return 1, 0
        q, r = divmod(a, b)
        x, y = egcd(b, r)
        return y, x - q*y

    a, b, s = map(int, rd().split())
    if (a, b) == (0, 0):
        print("YES" if s == 0 else "NO")
        return
    if b == 0:
        a, b = b, a
    g = gcd(a, b)
    if s % g:
        print("NO")
        return
    a //= g; b //= g; s //= g

    x, y = egcd(a, b)
    x *= s; y *= s
    k, x0 = divmod(x, b)
    y0 = y + a*k
    x, y = x0, y0

    # this loop does not exceed 2**15 iterations
    # a fantastic analysis can be found at https://rkm0959.tistory.com/96
    while y >= 0:
        if gcd(x, y) == 1:
            print("YES")
            return
        x += b; y -= a
    print("NO")


if __name__ == "__main__":
    main()
