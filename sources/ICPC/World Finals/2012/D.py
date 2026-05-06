"""
# ICPC, World Finals, ACM-ICPC World Finals 2012 D. Fibonacci Words
# BOJ 4206
# JUNGOL 1390
#
# ad-hoc
# Date: 2025.12.28
"""

def main() -> None:
    import sys

    fib = [0] * 101
    fib[1] = 1
    for i in range(2, 101): fib[i] = fib[i - 1] + fib[i - 2]

    def solve(n: int, p: str) -> int:
        if n < 0: return 0
        if p == '0': return fib[n - 1] if n > 0 else 1
        if p == '1': return fib[n]

        if p[0] == '0':
            p = '1' + p
        i = 0
        m = len(p)
        q = []
        while i < m:
            if i and p[i - 1] == p[i] == '0':
                return 0
            if i == m - 1:
                q = ''.join(q)
                return solve(n - 1, q + '0') + solve(n - 1, q + '1')
            if p[i + 1] == '0':
                q.append('1')
                i += 2
            else:
                q.append('0')
                i += 1

        return solve(n - 1, ''.join(q))

    lines = [line.strip() for line in sys.stdin.readlines()]
    for i in range(len(lines) // 2):
        print(f"Case {i + 1}: {solve(int(lines[2*i]), lines[2*i + 1])}")


if __name__ == "__main__":
    main()
