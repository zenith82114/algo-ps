"""
# 한국정보올림피아드, KOI 2008, 고등부 4. 세 번 뒤집기
# JUNGOL 1777
#
# bruteforce
# Date: 2026.5.30
"""

def main() -> None:
    import sys
    rd = lambda: sys.stdin.readline().rstrip()
    from itertools import combinations

    n = int(rd())
    a = [0] + list(map(int, rd().split()))
    ans = []

    def go(dep):
        s = 1
        while s <= n and s == a[s]: s += 1
        if s > n:
            return True
        if dep >= 3:
            return False
        e = n
        while e >= 1 and e == a[e]: e -= 1
        assert s <= e

        b = []
        l = s
        while l <= e:
            b.append(l)
            r = l
            while r < e and abs(a[r+1] - a[r]) == 1: r += 1
            b.append(r)
            l = r+1

        for i, j in combinations(b, 2):
            ans.append((i, j))
            a[i:j+1] = a[i:j+1][::-1]
            res = go(dep+1)
            a[i:j+1] = a[i:j+1][::-1]
            if res:
                return True
            else:
                ans.pop()

        return False

    assert go(0)

    for i, j in ans:
        print(i, j)
    for _ in range(3 - len(ans)):
        print("1 1")


if __name__ == "__main__":
    main()
