"""
# ICPC, Regionals, Europe, Central Europe Regional Contest,
# CERC 2019 A. ABB
# BOJ 18171
# JUNGOL 11598
#
# KMP
# Date: 2025.10.24
"""

def main() -> None:
    import sys
    rd = lambda: sys.stdin.readline().rstrip()

    n = int(rd())
    s = rd()
    t = s[::-1] + '$' + s

    ff = [0] * len(t)
    j = 0
    for i in range(1, len(t)):
        while j and t[i] != t[j]: j = ff[j - 1]
        if t[i] == t[j]: j += 1
        ff[i] = j
    print(n - ff[-1])


if __name__ == "__main__":
    main()
