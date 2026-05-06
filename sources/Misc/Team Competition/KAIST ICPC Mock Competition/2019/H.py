"""
# 2019 KAIST 9th ICPC Mock Competition H. Maximizer
# BOJ 17515 - greedy
# Date: 2025.11.13
"""

def main() -> None:
    import sys
    rd = lambda: sys.stdin.readline().rstrip()

    n = int(rd())
    a = list(map(int, rd().split()))
    b = list(map(int, rd().split()))

    def solve(k):
        ans = 0
        j = -1
        for i in range(n):
            if a[i] > k:
                continue
            j += 1
            while j < n and b[j] <= n - k: j += 1
            ans += abs(i - j)
        return ans

    if n & 1:
        m = (n + 1) // 2
        print(min(solve(m), solve(m - 1)))
    else:
        print(solve(n//2))


if __name__ == "__main__":
    main()
