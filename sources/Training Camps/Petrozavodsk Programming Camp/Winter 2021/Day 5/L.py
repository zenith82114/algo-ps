"""
# Petrozavodsk Programming Camp, Winter 2021, Day 5: Almost Retired Dandelion Contest, ICPC Camp Contest 2 L. Extreme Wealth
# Open Cup 2020/2021 Stage 11: Grand Prix of Nizhny Novgorod L. Extreme Wealth
# BOJ 21093 - probability theory
# Date: 2025.8.26
"""

def main() -> None:
    import sys
    rd = lambda: sys.stdin.readline().rstrip()
    from fractions import Fraction
    from math import pi, sqrt

    n, m = map(int, rd().split())
    if n > m:
        n, m = m, n

    if n < 10**7:
        ans = Fraction(1)
        for k in range(1, n + 1):
            ans *= 4 * k * k / (2*k - 1) / (2*k)
    else:
        ans = sqrt(pi * n) * (1 + 1/(8*n))
    if ans > 1e9:
        print('Extreme Wealth')
        return

    for k in range(n + 1, m + 1):
        ans *= 2 * k / (n + k)
        if ans > 1e9:
            print('Extreme Wealth')
            return
    print(ans)


if __name__ == "__main__":
    main()
