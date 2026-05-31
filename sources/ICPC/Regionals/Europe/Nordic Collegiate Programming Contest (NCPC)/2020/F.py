"""
# ICPC, Regionals, Europe, Northwestern Europe Regional Contest,
# Nordic Collegiate Programming Contest, NCPC 2020 F. Film Critics
# Petrozavodsk Programming Camp, Winter 2021, Day 3: Nordic+ Contest 2020 F. Film Critics
# JUNGOL 15922
#
# greedy
# Date: 2026.5.31
"""

def main() -> None:
    import sys
    rd = lambda: sys.stdin.readline().rstrip()

    n, m, k = map(int, rd().split())
    a = list(map(int, rd().split()))

    if k == 0 or k % m > 0:
        print('impossible')
        return
    p = k // m

    idx = sorted(range(n), key=lambda i: a[i])
    ans = [idx[n-p] + 1]
    l, r = n-p-1, n-p+1
    psum = m

    while l > -1 or r < n:
        if l > -1 and psum > len(ans) * a[idx[l]]:
            ans.append(idx[l] + 1)
            l -= 1
        elif r < n and psum <= len(ans) * a[idx[r]]:
            ans.append(idx[r] + 1)
            r += 1
            psum += m
        else:
            print('impossible')
            return

    print(*ans)


if __name__ == "__main__":
    main()
