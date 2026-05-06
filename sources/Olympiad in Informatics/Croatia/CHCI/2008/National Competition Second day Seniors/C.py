"""
# Croatian Highschool Competitions in Informatics, 2008, National Competition Second day Seniors C. SLON
# BOJ 3133 - LIS
# Date: 2025.3.17
"""

def main() -> None:
    import sys
    rd = sys.stdin.readline
    from bisect import bisect_left
    inf = int(1e9) + 1
    MOD = int(1e9) + 7

    n = int(rd())
    a, b = [], []
    for _ in range(n):
        ai, bi = map(int, rd().split())
        a.append(-ai)
        b.append(bi)
    b, a = map(list, zip(*sorted(zip(b, a))))
    a = [-ai for ai in a]

    f = []
    v = [[] for _ in range(n + 1)]
    v[0] = [(-inf, 0), (inf, 1)]
    l, r = 0, 0
    while l < n:
        while r < n and b[l] == b[r]:
            r += 1
        for i in range(l, r):
            p = bisect_left(f, a[i])
            if p < len(f):
                f[p] = a[i]
            else:
                f.append(a[i])
                v[p + 1].append((-inf, 0))
            lb = bisect_left(v[p], (-a[i] + 1, 0)) - 1
            c = (v[p][-1][1] - v[p][lb][1] + MOD) % MOD
            v[p + 1].append((-a[i], (v[p + 1][-1][1] + c) % MOD))
        l = r

    print(len(f))
    print(v[len(f)][-1][1])


if __name__ == "__main__":
    main()
