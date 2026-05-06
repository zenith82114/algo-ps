"""
# KTH Challenge, KTH Challenge 2012 F. Xor Maximization
# Q22038 - Gaussian elimination
# Date: 2026.2.3
"""

def main() -> None:
    import sys
    rd = lambda: sys.stdin.readline().rstrip()

    rd()
    a = list(map(int, rd().split()))
    v = []

    while a:
        x = max(a)
        v.append(x)
        b = 2 ** (x.bit_length() - 1)
        for i in range(len(a)):
            if a[i] & b:
                a[i] ^= x
        a = [x for x in a if x > 0]

    ans = 0
    for x in v:
        ans = max(ans, ans ^ x)
    print(ans)

if __name__ == "__main__":
    main()
