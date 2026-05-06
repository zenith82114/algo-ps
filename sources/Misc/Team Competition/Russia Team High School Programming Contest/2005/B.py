"""
# Russian Olympiad in Informatics, Russia Team High School Programming Contest 2005 B. Эльфы и олени
# BOJ 21482 - greedy, two pointers
# Date: 2025.2.28
"""

def main() -> None:
    import sys
    rd = sys.stdin.readline

    m, n = map(int, rd().split())
    a = sorted((v, i + 1) for i, v in enumerate(map(int, rd().split())))
    b = sorted((v, i + 1) for i, v in enumerate(map(int, rd().split())))

    i, k = 0, n // 2
    ans = []
    for j in range(n // 2):
        while i < m and a[i][0] <= b[j][0]:
            i += 1
        if i == m:
            break
        while k < n and b[k][0] <= a[i][0]:
            k += 1
        if k == n:
            break
        ans.append((i, j, k))
        i += 1
        k += 1

    print(len(ans))
    for i, j, k in ans:
        print(a[i][1], b[j][1], b[k][1])


if __name__ == "__main__":
    main()
