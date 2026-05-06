"""
# Russian Olympiad in Informatics, Russia Team High School Programming Contest 2019 B. Blocking the View
# BOJ 19806 - geometry; ray-segment intersection
# Date: 2026.2.25
"""

class Vec2:
    def __init__(self, x, y):
        self.x = float(x)
        self.y = float(y)

    def __repr__(self) -> str:
        return f"({self.x}, {self.y})"

    def __add__(self, other):
        return Vec2(self.x + other.x, self.y + other.y)

    def __sub__(self, other):
        return Vec2(self.x - other.x, self.y - other.y)

    def __neg__(self):
        return Vec2(-self.x, -self.y)

    def dot(self, other) -> float:
        return self.x * other.x + self.y * other.y

    def cross(self, other) -> float:
        return self.x * other.y - self.y * other.x


def main() -> None:
    import sys
    rd = lambda: sys.stdin.readline().rstrip()

    def ray_seg(p, v, q1, q2):
        c1, c2 = v.cross(q1 - p), v.cross(q2 - p)
        if c1*c2 > 0:
            return False
        if c1 == c2 == 0:
            return v.dot(q1 - p) > 0 or v.dot(q2 - p) > 0
        if c1 > c2: q1, q2 = q2, q1
        return (q2 - q1).cross(p - q1) >= 0

    for _ in range(int(rd())):
        inp = list(map(int, rd().split()))
        a1 = Vec2(inp[0], inp[1])
        a2 = Vec2(inp[2], inp[3])
        b1 = Vec2(inp[4], inp[5])
        b2 = Vec2(inp[6], inp[7])
        v  = Vec2(inp[8], inp[9])
        ans = (ray_seg(a1, v, b1, b2) or
               ray_seg(a2, v, b1, b2) or
               ray_seg(b1, -v, a1, a2) or
               ray_seg(b2, -v, a1, a2))
        print(['No', 'Yes'][ans])


if __name__ == "__main__":
    main()
