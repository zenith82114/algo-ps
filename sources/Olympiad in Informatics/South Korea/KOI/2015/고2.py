"""
# 한국정보올림피아드, KOI 2015, 고등부 2. 구간 성분
# JUNGOL 2918
#
# hashing
# Date: 2026.5.6
"""

def main() -> None:
    import sys
    rd = lambda: sys.stdin.readline().rstrip()
    import random
    from string import ascii_lowercase

    H = {c: random.getrandbits(64) for c in ascii_lowercase}

    a, b = rd(), rd()
    n, m = len(a), len(b)

    for ans in range(min(n, m), 0, -1):
        h = sum(H[a[i]] for i in range(ans))
        s = set([h])
        for i in range(n - ans):
            h += + H[a[i + ans]] - H[a[i]]
            s.add(h)

        h = sum(H[b[i]] for i in range(ans))
        if h in s:
            print(ans)
            return
        for i in range(m - ans):
            h += + H[b[i + ans]] - H[b[i]]
            if h in s:
                print(ans)
                return
    print(0)


if __name__ == "__main__":
    main()
