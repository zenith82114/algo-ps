"""
# ICPC, Regionals, Europe, Southeastern Europe Regional Contest,
# SEERC 2009 A. RSA Factorization
# BOJ 3734 - number theory, bruteforce
# Date: 2023.11.8
"""

def ceil_sqrt(n):
    l, r = 1, n
    while l != r:
        mid = (l + r)>>1
        if mid*mid < n: l = mid+1
        else: r = mid
    return (l, l*l == n)

n, k = map(int, input().split())
x, y2 = 0, 4*n*k
y, sqr = -1, False
while not sqr:
    y, sqr = ceil_sqrt(y2)
    if sqr:
        if (y - x) > (2*k) and (y - x) % (2*k) == 0 \
        and (y + x) > 2 and (y + x) % 2 == 0:
            p = (y - x) // (2*k)
            q = (y + x) // 2
            print(f'{p} * {q}')
        elif (y + x) > (2*k) and (y + x) % (2*k) == 0 \
        and (y - x) > 2 and (y - x) % 2 == 0:
            p = (y + x) // (2*k)
            q = (y - x) // 2
            print(f'{p} * {q}')
        else: sqr = False
    y2 += 2*x + 1
    x += 1
