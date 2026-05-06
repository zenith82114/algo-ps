"""
# Waterloo's local Programming Contests, 2 October, 1999 D. Suffidromes
# BOJ 4399 - greedy
# Date: 2025.11.7
"""

def main() -> None:
    import sys

    def chk(s: str, i: int) -> bool:
        return all(s[j] == s[i - 1 - j]
                   for j in range(i, len(s)))

    lines = [a.strip() for a in sys.stdin.readlines()]

    for tc in range(0, len(lines), 2):
        a, b = lines[tc], lines[tc + 1]
        if a == b:
            print('No Solution.')
            continue

        n, m = len(a), len(b)
        if n > m:
            a, b, n, m = b, a, m, n

        for i in range(n + 1):
            fa, fb = chk(a, i), chk(b, i)
            if fa and not fb:
                print(a[:i][::-1])
                break
            elif fb and not fa:
                print(b[:i][::-1])
                break
            elif fa and fb:
                j = i - 1
                while j >= 0 and a[j] == b[j]: j -= 1
                if j < 0: continue
                c = a if a[j] < b[j] else b
                print(c[:i][::-1])
                break
        else:
            assert a == b[:n]
            print(('b' if b[n] == 'a' and chk(b, n + 1) else 'a') + a[::-1])


if __name__ == "__main__":
    main()
