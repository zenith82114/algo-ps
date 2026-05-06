"""
# ICPC, Regionals, Asia Pacific, Taiwan,
# Taiwan Online Programming Contest, TOPC 2019 F. Factorization
# Q17603 - Tonelli-Shanks alg.
# Date: 2024.6.28
"""

import sys


def sqrt_mod(n, p) -> int:
    q, m = p-1, 0
    while q % 2 == 0:
        q, m = q//2, m+1
    c = 1
    while pow(c, p//2, p) == 1:
        c = c+1
    c = pow(c, q, p)
    t = pow(n, q, p)
    r = pow(n, (q+1)//2, p)

    while t != 1:
        i, u = 0, t
        while u != 1:
            i, u = i+1, u*u%p
        b = c
        for _ in range(m-1-i):
            b = b*b%p
        m, c, t, r = i, b*b%p, t*b*b%p, r*b%p
    return r


def main() -> None:
    rd = sys.stdin.readline
    for _ in range(int(rd())):
        p, a0, a1 = map(int, rd().split())
        if p == 2:
            if a0 & a1:
                print(-1)
            else:
                print(a0, a0 | a1)
        else:
            d = (a1*a1 + (p-1)*4*a0) % p
            half = pow(2, p-2, p)
            if d == 0:
                b = a1*half % p
                print(b, b)
            elif pow(d, p//2, p) == 1:
                r = sqrt_mod(d, p)
                b0, b1 = (a1 + r)*half % p, (a1 + p - r)*half % p
                if b0 > b1:
                    b0, b1 = b1, b0
                print(b0, b1)
            else:
                print(-1)


if __name__ == "__main__":
    main()
