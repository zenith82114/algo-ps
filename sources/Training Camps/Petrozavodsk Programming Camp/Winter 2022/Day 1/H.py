"""
# Petrozavodsk Programming Camp, Winter 2022, Day 1: Kyoto U Contest 2 H. High Powers
# BOJ 24660 - mathematics; algebra
# Date: 2025.8.4
"""

def main() -> None:
    MOD = 998244353
    n, m = map(int, input().split())
    s, t, u = map(int, input().split())

    def coeff(n: int) -> list:
        if n == 1:
            return [0, 1, 0]
        if n == 2:
            return [0, 0, 1]

        f = coeff(n//3)
        e = [0] * (7 + (n%3))
        for i in range(3):
            for j in range(3):
                for k in range(3):
                    e[i + j + k + (n%3)] += (f[i] * f[j] * f[k]) % MOD
        while len(e) > 3:
            e[-2] += e[-1] * s
            e[-3] -= e[-1] * t
            e[-4] += e[-1] * u
            e.pop()

        return [_ % MOD for _ in e]

    en, em = coeff(n), coeff(m)
    print((en[1]*em[2] - en[2]*em[1]) % MOD)


if __name__ == "__main__":
    main()
