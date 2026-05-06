"""
# ICPC, World Finals, ICPC World Finals 2021 H. Prehistoric Programs
# BOJ 26137
#
# greedy
# Date: 2025.6.9
"""

def main() -> None:
    import sys
    rd = lambda: sys.stdin.readline().rstrip()

    n = int(rd())
    q_pos, q_z, q_neg = [], [], []
    d_sum, pos_d_sum = 0, 0
    for i in range(n):
        s = rd()
        d = 2 * s.count('(') - len(s)
        d_sum += d
        if d > 0: pos_d_sum += d

        p, m = 0, 0
        if d > 0:
            for c in s:
                p += 1 if c == '(' else -1
                m = min(m, p)
            q_pos.append((-m, d, i))
        elif d < 0:
            d = -d
            for c in reversed(s):
                p += -1 if c == '(' else 1
                m = min(m, p)
            q_neg.append((-m, d, i))
        else:
            for c in s:
                p += 1 if c == '(' else -1
                m = min(m, p)
            q_z.append((-m, d, i))

    if d_sum != 0:
        print('impossible')
        return
    if any(e[0] > pos_d_sum for e in q_z):
        print('impossible')
        return

    def solve(v: list[tuple]) -> list[int] | None:
        ans = []
        p = 0
        for m, d, i in sorted(v):
            if p < m: return None
            p += d
            ans.append(i)
        return ans

    r_pos = solve(q_pos)
    if r_pos is None:
        print('impossible')
        return
    r_neg = solve(q_neg)
    if r_neg is None:
        print('impossible')
        return
    r_z = [e[2] for e in q_z]

    for i in r_pos: print(i + 1)
    for i in r_z: print(i + 1)
    for i in reversed(r_neg): print(i + 1)


if __name__ == "__main__":
    main()
