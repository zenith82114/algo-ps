"""
# ICPC, Regionals, Europe, Southwestern Europe Regional Contest, Télécom ParisTech Internal Selection,
# Concours interne de programmation Télécom ParisTech 2018 G. The Total is Right
# Q16093 - bitmask DP; submask enumeration
# Date: 2024.11.10
"""

import sys


def main() -> None:
    rd = sys.stdin.readline
    for _ in range(int(rd())):
        X = list(map(int, rd().split()))
        n = X.pop(0)
        S = [set() for _ in range(64)]
        for i in range(6):
            S[1 << i].add(X[i])
        for m in range(3, 64):
            m1 = (~m + 1) & m
            m2 = m ^ m1
            while m1 < m2:
                for a1 in S[m1]:
                    for a2 in S[m2]:
                        x, y = max(a1, a2), min(a1, a2)
                        S[m].add(x + y)
                        if x != y:
                            S[m].add(x - y)
                        S[m].add(x * y)
                        if x % y == 0:
                            S[m].add(x // y)
                m1 = ((~m | m1) + 1) & m
                m2 = m ^ m1
        if any(n in Si for Si in S):
            print("The total is right")
        else:
            print("Impossible")


if __name__ == "__main__":
    main()
