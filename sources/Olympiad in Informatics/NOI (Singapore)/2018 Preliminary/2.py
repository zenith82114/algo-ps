"""
# National Olympiad in Informatics (Singapore), NOI 2018 Preliminary 2. Knapsack
# BOJ 19696 - greedy, knapsack
# Date: 2025.4.5
"""

def main() -> None:
    import sys
    rd = sys.stdin.readline

    s, n = map(int, rd().split())
    a = [[] for _ in range(s + 1)]
    for _ in range(n):
        v, w, k = map(int, rd().split())
        a[w].append((v, k))

    dp = [0] * (s + 1)
    for w in range(1, s + 1):
        a[w].sort(reverse=True)
        c = s // w
        for v, k in a[w]:
            for _ in range(min(c, k)):
                for j in reversed(range(w, s + 1)):
                    dp[j] = max(dp[j], dp[j - w] + v)
            c -= k
            if c <= 0:
                break
    print(max(dp))


if __name__ == "__main__":
    main()
