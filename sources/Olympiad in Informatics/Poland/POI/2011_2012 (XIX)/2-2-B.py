"""
# Polish Olympiad in Informatics, POI 2011/2012, Stage 2 Day 2 B. Fibonacci Representation
# BOJ 8229 - math
# Date: 2024.12.14
"""

def main() -> None:
    import sys
    rd = lambda: sys.stdin.readline().rstrip()

    for _ in range(int(rd())):
        k = int(rd())
        x, y = 1, 1
        while y <= k:
            x, y = y, x + y
        ans = 0
        while k > 0:
            ans += 1
            k = min(k - x, y - k)
            while k < x:
                x, y = y - x, x
        print(ans)


if __name__ == "__main__":
    main()
