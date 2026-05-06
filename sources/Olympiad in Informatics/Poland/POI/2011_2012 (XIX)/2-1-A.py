"""
# Polish Olympiad in Informatics, POI 2011/2012, Stage 2 Day 1 A. Vouchers
# BOJ 8226 - number theory
# Date: 2024.9.7
"""

def main() -> None:
    import sys
    rd = sys.stdin.readline

    C = 10 ** 6
    m = int(rd())
    inb = [False] * (C + 1)
    for _ in range(m):
        inb[int(rd())] = True
    n = int(rd())
    last = list(range(C + 1))
    sold = [False] * (C + 1)
    cus = 0
    ans = []
    for _ in range(n):
        a = int(rd())
        qty = a
        while last[a] <= C and qty > 0:
            if not sold[last[a]]:
                sold[last[a]] = True
                cus += 1
                qty -= 1
                if inb[last[a]]:
                    ans.append(cus)
            last[a] += a
        cus += qty
    print(len(ans))
    for x in ans:
        print(x)


if __name__ == "__main__":
    main()
