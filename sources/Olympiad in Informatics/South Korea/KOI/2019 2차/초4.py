"""
# 한국정보올림피아드, KOI 2019 2차대회, 초등부 4. 로봇
# BOJ 17617
# JUNGOL 3429
#
# sliding window minimum with deque
# Date: 2025.12.19
"""

def main() -> None:
    import sys
    rd = lambda: sys.stdin.readline().rstrip()
    from collections import deque

    n = int(rd())
    r, m = map(int, rd().split())
    x = sorted(map(int, rd().split()))
    x.extend([xi + m for xi in x])
    x = [x[i] - 2*r*i for i in range(2*n)]

    ans = 0
    q = deque([0])
    for j in range(1, 2*n):
        if q and q[0] <= j - n:
            q.popleft()
        if q:
            ans = max(ans, x[j] - x[q[0]])
        while q and x[q[-1]] >= x[j]:
            q.pop()
        q.append(j)
    print((ans + 1) // 2)


if __name__ == "__main__":
    main()
