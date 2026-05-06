"""
# Central Europe Olympiad in Informatics, CEOI 2005, Day 2 C. Ticket Office
# BOJ 2095 - greedy
# Date: 2026.2.10
"""

def main() -> None:
    import sys
    rd = lambda: sys.stdin.readline().rstrip()

    n, L, m = map(int, rd().split())
    z = sorted(map(int, rd().split()))

    s = [n + 1]
    for zi in reversed(z):
        if zi + L <= s[-1]: s.append(zi)
    s.reverse()
    s.pop()
    assert len(s) > 0

    j = 0
    free = 1
    old_sj, gap = s[0], L

    z.append(n + 1)
    for zi in z:
        if zi > old_sj:
            free = s[j] + L
            j += 1
            if j < len(s): old_sj, gap = s[j], L
            else: break
        if zi >= free and (zi - free) % L < gap:
            s[j] = zi
            gap = (zi - free) % L

    cnt = (s[0] - 1) // L
    for i in range(len(s) - 1): cnt += (s[i + 1] - s[i] - L) // L
    cnt += (n - s[-1] - L + 1) // L

    ans = 2*len(s) + min(cnt, m - len(s))
    print(ans)


if __name__ == "__main__":
    main()
