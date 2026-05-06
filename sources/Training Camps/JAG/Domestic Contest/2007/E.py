"""
# ICPC Japanese Alumni Group, JAG Domestic Contest 2007 E. Lifeguard in the Pool
# BOJ 22684 - geometry, calculus, DP
# Date: 2025.7.22
"""

EPS = 1e-9
INF = 1e18
from math import sqrt

class Vec2:
    def __init__(self, x, y):
        self.x = float(x)
        self.y = float(y)

    # def __repr__(self) -> str:
    #     return f"({self.x}, {self.y})"

    def __eq__(self, other):
        return abs(self.x - other.x) < EPS and abs(self.y - other.y) < EPS

    def __add__(self, other):
        return Vec2(self.x + other.x, self.y + other.y)

    def __sub__(self, other):
        return Vec2(self.x - other.x, self.y - other.y)

    def __mul__(self, scalar):
        return Vec2(self.x * scalar, self.y * scalar)

    def __rmul__(self, scalar):
        return self.__mul__(scalar)

    def __truediv__(self, scalar):
        assert abs(scalar) > EPS
        return Vec2(self.x / scalar, self.y / scalar)

    def __neg__(self):
        return Vec2(-self.x, -self.y)

    def dot(self, other) -> float:
        return self.x * other.x + self.y * other.y

    def cross(self, other) -> float:
        return self.x * other.y - self.y * other.x

    def norm_squared(self) -> float:
        return self.x ** 2 + self.y ** 2

    def norm(self) -> float:
        return sqrt(self.norm_squared())

    def normalized(self):
        return self.__truediv__(self.norm())

    def project(self, other):
        return (self.dot(other) / other.norm_squared()) * other


def main() -> None:
    import sys
    rd = lambda: sys.stdin.readline().rstrip()

    n = int(rd())
    while n:
        it = map(int, rd().split())
        p = [Vec2(next(it), next(it)) for _ in range(n)]
        tg, tw = int(rd()), int(rd())
        tan_theta = tg / sqrt(tw * tw - tg * tg)
        s = Vec2(*map(int, rd().split()))
        e = Vec2(*map(int, rd().split()))

        for i in range(n):
            j = (i + 1) % n
            if (p[j] - p[i]).cross(s - p[i]) == 0 and s != p[j]:
                k = j
                break
        np = [s]
        np.extend(p[(k + i) % n] for i in range(n))
        if s == np[-1]:
            np.pop()
        p, n = np, len(np)

        def best_route(a: Vec2, b: Vec2, c: Vec2) -> tuple[Vec2, float]:
            # a~b: ground, b~c: water
            assert a != b != c != a
            d = a + (c - a).project(b - a)
            w, h = (a - d).norm(), (c - d).norm()
            x = max(0, min(w - h * tan_theta, (b - a).norm()))
            f = a + x * (b - a).normalized()
            return f, tg * (f - a).norm() + tw * (c - f).norm()

        def solve() -> float:
            q = []
            for i in range(n):
                q.append(p[i])
                j = (i + 1) % n
                f = best_route(p[i], p[j], e)[0]
                if f != p[i] and f != p[j]:
                    q.append(f)
            m = len(q)

            dp = [INF] * m
            dp[0] = 0
            for i in range(1, m):
                dp[i] = dp[i - 1] + tg * (q[i] - q[i - 1]).norm()
                for j in range(i - 1):
                    dp[i] = min(dp[i], dp[j] + min(
                        best_route(q[j], q[j + 1], q[i])[1],
                        best_route(q[i], q[i - 1], q[j])[1]))

            ans = INF
            for i in range(m):
                ans = min(ans, dp[i] + tw * (e - q[i]).norm())
            return ans

        ans = solve()
        p[1:] = p[1:][::-1]
        ans = min(ans, solve())
        print(ans)

        n = int(rd())


if __name__ == "__main__":
    main()
