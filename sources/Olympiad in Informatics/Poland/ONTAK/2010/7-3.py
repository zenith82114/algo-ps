"""
# POI Training Camp, ONTAK 2010 7-3. Earthquake
# BOJ 8483 - floor sum of arithmetic progression
# Date: 2025.9.7
"""

def main() -> None:
    import sys
    rd = lambda: sys.stdin.readline().rstrip()

    def f(a, b, c):
        if a + b > c:
            return 0
        if a < b:
            a, b = b, a
        q, r = divmod(a, b)
        t = (q*c + r) // a
        s = (t - 1) // q
        return t*s - q*s*(s+1)//2 + f(b, r, c - b*t)

    a, b, c = map(int, rd().split())
    print(f(a, b, c) + c//a + c//b + 1)


if __name__ == "__main__":
    main()
