"""
# USA Computing Olympiad, USACO 2023 US Open Contest, Platinum
# 2. Good Bitstrings
# QOJ 6266
#
# Euclidean algorithm
# Date: 2026.8.27
"""

def solve(a, b):
    if a == b:
        return 2*a - 1
    elif a < b:
        q, r = divmod(b, a)
        if r == 0:
            return 2*a + q - 2
        return q + solve(a, r)
    else:
        q, r = divmod(a, b)
        if r == 0:
            return 2*b + q - 2
        return (q-1) + (b+r-1)//r + solve(r, b)


def main() -> None:
    import sys
    rd = lambda: sys.stdin.readline().rstrip()

    for _ in range(int(rd())):
        a, b = map(int, rd().split())
        print(solve(a, b))


if __name__ == "__main__":
    main()
