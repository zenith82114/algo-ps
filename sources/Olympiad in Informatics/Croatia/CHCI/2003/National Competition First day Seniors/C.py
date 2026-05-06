"""
# Croatian Highschool Competitions in Informatics, 2003, National Competition First day Seniors C. SUMA
# BOJ 3239 - angular sort, two pointers
# Date: 2025.9.18
"""

class Vec2:
    def __init__(self, x: int, y: int) -> None:
        self.x = x
        self.y = y

    def __add__(self, other):
        return Vec2(self.x + other.x, self.y + other.y)

    def __sub__(self, other):
        return Vec2(self.x - other.x, self.y - other.y)

    def dot(self, other) -> int:
        return self.x * other.x + self.y * other.y

    def cross(self, other) -> int:
        return self.x * other.y - self.y * other.x

    def norm_sqr(self) -> int:
        return self.x ** 2 + self.y ** 2


def cmp_arg(u: Vec2, v: Vec2) -> int:
    if u.y * v.y < 0:
        return v.y - u.y
    if u.cross(v) == 0:
        if u.dot(v) > 0:
            return u.norm_sqr() - v.norm_sqr()
        else:
            return v.x - u.x
    if 0 == u.y < u.x:
        return -1
    if 0 == v.y < v.x:
        return 1
    return v.cross(u)


def main() -> None:
    import sys
    rd = lambda: sys.stdin.readline().rstrip()
    from functools import cmp_to_key

    n = int(rd())
    v = [Vec2(*map(int, rd().split())) for _ in range(n)]
    v.sort(key=cmp_to_key(cmp_arg))
    v.extend(v)

    u = Vec2(0, 0)
    ans = 0
    j = 0
    for i in range(n):
        while j < i + n and (
            (v[i].cross(v[j]) == 0 and v[i].dot(v[j]) > 0) or
            v[i].cross(v[j]) > 0
        ):
            u += v[j]
            ans = max(ans, u.norm_sqr())
            j += 1
        u -= v[i]
        ans = max(ans, u.norm_sqr())

    print(ans)


if __name__ == "__main__":
    main()
