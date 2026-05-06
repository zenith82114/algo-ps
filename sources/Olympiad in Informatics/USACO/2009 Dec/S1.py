"""
# USA Computing Olympiad, USACO December 2009 Contest, Silver 1. Bobsledding
# BOJ 6009
#
# sweep line
# Date: 2024.8.28
"""

def main() -> None:
    import sys
    rd = sys.stdin.readline

    L, N = map(int, rd().split())
    v = [(0, 1), (L, 10**18)]
    for _ in range(N):
        x, y = map(int, rd().split())
        v.append((x, y))
    v.sort()
    N = len(v)
    for i in range(1, N):
        x0, y0 = v[i - 1]
        x1, y1 = v[i]
        v[i] = (x1, min(y1, y0 + x1 - x0))
    for i in range(N - 2, -1, -1):
        x0, y0 = v[i]
        x1, y1 = v[i + 1]
        v[i] = (x0, min(y0, y1 + x1 - x0))

    ans = 1
    for i in range(1, N):
        x0, y0 = v[i - 1]
        x1, y1 = v[i]
        ans = max(ans, y1)
        if x1 - x0 > abs(y1 - y0):
            ans = max(ans, (x1 - x0 + y1 + y0) // 2)
    print(ans)


if __name__ == "__main__":
    main()
