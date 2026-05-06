"""
# Central Europe Olympiad in Informatics, CEOI 2016, Day 1 B. Kangaroo
# BOJ 13188
# JUNGOL 5424
#
# connected component DP
# Date: 2025.7.25
"""

def main() -> None:
    import sys
    rd = lambda: sys.stdin.readline().rstrip()
    MOD = 10**9 + 7

    n, s, e = map(int, rd().split())
    f = [0] * (n + 2)
    nf = [0] * len(f)
    nf[1] = 1

    for i in range(2, n + 1):
        f[:] = [0] * len(f)
        f, nf = nf, f
        if i in [s, e]:
            for j in range(1, i + 1):
                nf[j] = (f[j - 1] + f[j]) % MOD
        else:
            for j in range(1, n + 1):
                nf[j] = j * f[j + 1] + (j - int(s < i) - int(e < i)) * f[j - 1]
                nf[j] %= MOD
    print(nf[1])


if __name__ == "__main__":
    main()
