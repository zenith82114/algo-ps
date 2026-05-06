"""
# ICPC, Regionals, Europe, Central Europe Regional Contest,
# CERC 2019 A. ABB
# BOJ 18171
# JUNGOL 11598
#
# Manacher's
# Date: 2025.10.24
"""

def main() -> None:
    import sys
    rd = lambda: sys.stdin.readline().rstrip()

    n = int(rd())
    s = f"${'$'.join(rd())}$"

    rad = [0] * len(s)
    p = 1
    for i in range(1, len(s)):
        rad[i] = min(rad[2*p - i], max(0, p + rad[p] - i))
        while (
            0 <= i - rad[i] - 1 and i + rad[i] + 1 < len(s) and
            s[i - rad[i] - 1] == s[i + rad[i] + 1]
        ):
            rad[i] += 1
        if p + rad[p] < i + rad[i]: p = i

        if i + rad[i] == 2*n:
            print(i - n)
            return


if __name__ == "__main__":
    main()
