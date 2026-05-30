"""
# ICPC, Regionals, Northern Eurasia, Northern Eurasia Finals 2018 F. Fractions
# BOJ 16665
# JUNGOL 12705
#
# number theory
# Date: 2024.5.20
"""

from math import gcd

def main() -> None:
    n = int(input())

    phi = list(range(32000))
    for i in range(1, 32000):
        for j in range(2*i, 32000, i):
            phi[j] -= phi[i]

    for x in range(2, 32000):
        if x*x >= n:
            break
        if n%x:
            continue
        y = n//x
        if gcd(x, y) > 1:
            continue
        c = pow(x - y%x, phi[x]-1, x)
        if (n-1-c*y)%x:
            continue
        d = (n-1-c*y)//x
        print(f"YES\n2\n{c} {x}\n{d} {y}")
        return

    print("NO")

if __name__ == "__main__":
    main()
