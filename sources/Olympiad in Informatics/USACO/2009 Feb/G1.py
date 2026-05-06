"""
# USA Computing Olympiad, USACO February 2009 Contest, Gold 1. Fair Shuttle
# BOJ 1161
#
# greedy
# Date: 2025.2.24
"""

def main() -> None:
    import sys
    rd = sys.stdin.readline

    k, _, c = map(int, rd().split())
    a = [tuple(map(int, rd().split())) for _ in range(k)]
    a.sort(key=lambda x: (x[1], -x[0]))

    b = [0] * c
    ans = 0
    for s, e, t in a:
        b.sort(reverse=True)
        i = 0
        while i < c and s < b[i]:
            i += 1
        while i < c and t > 0:
            b[i] = e
            ans += 1
            i += 1
            t -= 1
    print(ans)


if __name__ == "__main__":
    main()
