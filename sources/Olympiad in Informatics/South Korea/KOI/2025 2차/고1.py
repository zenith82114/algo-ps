"""
# 한국정보올림피아드, KOI 2025 2차대회, 고등부 1. 점프
# BOJ 34202
# JUNGOL 8595
#
# stack
# Date: 2025.12.19
"""

def main() -> None:
    import sys
    rd = lambda: sys.stdin.readline().rstrip()

    n = int(rd())
    c = [0] + list(map(int, rd().split()))
    d = [0] + [c[i] - c[i - 1] for i in range(1, n)]
    e, ne = [], []
    for i in range(n - 1, 1, -1):
        if d[i] == 2:
            e.append(i)
        else:
            ne.append(i)

    ans = [1]
    for _ in range(n - 2):
        if d[ans[-1]] == -2:
            ans.append(e.pop())
        else:
            ans.append(ne.pop())
    ans.append(n)
    print(*ans)


if __name__ == "__main__":
    main()
