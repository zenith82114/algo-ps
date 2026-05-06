"""
# Baltic Olympiad in Informatics, BOI 2006 Day 2 A. City Planning
# BOJ 3370
#
# binary search, two pointers
# Date: 2025.10.26
"""

def main() -> None:
    import sys
    rd = lambda: sys.stdin.readline().rstrip()

    n, t, k = map(int, rd().split())
    c, sc = [0], [0]
    for _ in range(k):
        c.append(int(rd()))
        sc.append(sc[-1] + c[-1])

    def solve(m):
        cnt, ans = 0, 0
        y = k
        for x in range(10**6):
            while y > 0 and c[y] + t*x > m:
                y -= 1
            if y == 0:
                break
            cnt += 4*(x + 1) * y
            ans += 4*(x + 1) * (sc[y] + y * t*x)
        return (cnt, ans)

    lo, hi = 0, 10**12
    while lo + 1 < hi:
        print(lo, hi)
        mid = (lo + hi) // 2
        if solve(mid)[0] < n:
            lo = mid
        else:
            hi = mid

    cnt, ans = solve(hi)
    print(ans - hi * (cnt - n))


if __name__ == "__main__":
    main()
