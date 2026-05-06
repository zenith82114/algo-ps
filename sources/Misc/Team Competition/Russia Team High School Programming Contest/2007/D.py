"""
# Russian Olympiad in Informatics, Russia Team High School Programming Contest 2007 D. Выражение
# BOJ 21463 - DP, greedy
# Date: 2026.1.30
"""

def main() -> None:
    import sys
    rd = lambda: sys.stdin.readline().rstrip()
    MAX_DIST = 20
    INF = int(2e5 + 5)

    n = int(rd())
    x = list(map(int, rd().split()))
    ans = [''] * n

    s = 0
    while s < n:
        if x[s] == 0:
            ans[s] = '+'
            s += 1
            continue

        e = s
        while e < n and x[e] > 0: e += 1

        c = [i for i in range(s, e) if x[i] >= 2]

        if not c:
            for i in range(s, e): ans[i] = '+'
            s = e
            continue

        m = len(c)
        c.append(s - 1) # c[-1] = s - 1
        dp = [-1] * (m + 1); dp[-1] = 0
        opt = [0] * (m + 1)
        is_big = False

        for i in range(m):
            prod = 1

            for dist in range(1, min(i + 1, MAX_DIST) + 1):
                j = i - dist
                prod = min(prod * x[c[j + 1]], INF)
                if prod == INF: is_big = True
                temp = dp[j] + (c[j + 1] - c[j] - 1) + prod
                if dp[i] < temp:
                    dp[i], opt[i] = temp, dist

        if is_big:
            for i in range(s, c[0] + 1): ans[i] = '+'
            for i in range(c[0] + 1, c[-2] + 1): ans[i] = '*'
            for i in range(c[-2] + 1, e): ans[i] = '+'
        else:
            for i in range(s, e): ans[i] = '+'
            i = m - 1
            while i > 0:
                dist = opt[i]
                for j in range(c[i - dist + 1] + 1, c[i] + 1):
                    ans[j] = '*'
                i -= dist

        s = e

    print(x[0], end='')
    for i in range(1, n):
        print(f"{ans[i]}{x[i]}", end='')


if __name__ == "__main__":
    main()
