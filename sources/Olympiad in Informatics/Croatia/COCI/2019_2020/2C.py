"""
# Croatian Open Competition in Informatics, COCI 2019/2020, Contest #2 C. Checker
# BOJ 18093
#
# geometry; ear clipping
# Date: 2025.3.7
"""

def main() -> None:
    import sys
    rd = sys.stdin.readline

    rd() # ignore
    n = int(rd())
    nxt = [((i + 1) % n, c) for i, c in enumerate(map(int, rd().strip()))]
    diag = []
    for _ in range(n - 3):
        i, j, c = map(int, rd().split())
        i -= 1; j -= 1
        if 2 * ((j - i + n) % n) > n:
            i, j = j, i
        diag.append((i, j, c))
    diag.sort(key=lambda x: (x[1] - x[0] + n) % n)

    chk = True
    for i, k, c_ki in diag:
        j, c_ij = nxt[i]
        if nxt[j][0] != k:
            print("neispravna triangulacija")
            return
        c_jk = nxt[j][1]
        chk = chk and (c_ij != c_jk != c_ki != c_ij)
        nxt[i] = (k, c_ki)
    print("tocno" if chk else "neispravno bojenje")


if __name__ == "__main__":
    main()
