"""
# Swedish Olympiad in Informatics, 2022, Final D. Triangle numbers
# BOJ 26880 - greedy
# Date: 2024.8.22
"""

import sys


def main() -> None:
    rd = sys.stdin.readline
    n = int(rd())
    a = list(map(int, rd().split()))
    b = list(range(n))
    b.sort(key=lambda i: a[i])
    a.sort()

    def check(sol: list):
        for i in range(-1, 2):
            if sol[i + 1][1] < a[sol[i][0]]:
                return None

        ans = [''] * n
        for i in range(n):
            ans[b[i]] = (
                '1' if sol[0][0] - sol[0][1] < i <= sol[0][0] else
                '2' if sol[1][0] - sol[1][1] < i <= sol[1][0] else
                '3'
            )
        return ''.join(ans)

    mx = a[-1]
    p1 = n - 1
    p2 = mx - 1
    p3 = p2 + a[p2]
    if p2 < p3 < p1:
        sol = [(p1, p1 - p3), (p2, p2 + 1), (p3, p3 - p2)]
        ans = check(sol)
        if ans is not None:
            print("YES")
            print(ans)
            return

    for p2 in range(mx, p1):
        p3 = p2 - mx
        sol = [(p1, p1 - p2), (p2, mx), (p3, p3 + 1)]
        ans = check(sol)
        if ans is not None:
            print("YES")
            print(ans)
            return

    print("NO")


if __name__ == "__main__":
    main()
