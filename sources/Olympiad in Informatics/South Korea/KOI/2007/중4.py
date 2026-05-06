"""
# 한국정보올림피아드, KOI 2007, 중등부 4. 짐정리
# JUNGOL 1075
#
# permutation cycle decomposition, greedy
# Date: 2026.5.5
"""

def main() -> None:
    import sys
    rd = lambda: sys.stdin.readline().rstrip()

    n = int(rd())
    a = sorted((int(rd()), i) for i in range(n))

    ans = sum(x for x, _ in a)
    vis = [False] * n
    m0 = a[0][0]

    for i in range(n):
        if vis[i]: continue
        m = a[i][0]
        len = 0
        j = i
        while not vis[j]:
            vis[j] = True
            len += 1
            j = a[j][1]
        ans += min(m * (len - 2), m + m0 * (len + 1))

    print(ans)


if __name__ == "__main__":
    main()
