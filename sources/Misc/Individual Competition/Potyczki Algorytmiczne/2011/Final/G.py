"""
# Potyczki Algorytmiczne 2011 Final G. Prime prime power
# BOJ 8293 - sieve of Eratosthenes
# Date: 2025.12.21
"""

def main() -> None:
    import sys
    rd = lambda: sys.stdin.readline().rstrip()
    import math
    import heapq

    SIEVE1_SIZE = 1_100_000 # > [sqrt(n) + k ln(sqrt(n))]^(2/3)
    SIEVE2_SIZE = 2_100_000 # > k ln(sqrt(n))
    sieve1 = [True] * SIEVE1_SIZE
    sieve2 = [True] * SIEVE2_SIZE
    primes = []

    n, k = map(int, rd().split())
    sqrt_n = math.isqrt(n)

    for p in range(2, SIEVE1_SIZE):
        if sieve1[p]:
            primes.append(p)

            for q in range(p * p, SIEVE1_SIZE, p):
                sieve1[q] = False

            base = (sqrt_n + p - 1) // p * p
            if base == p:
                base += p
            for i in range(base - sqrt_n, SIEVE2_SIZE, p):
                sieve2[i] = False

    h = []
    for i in range(1, SIEVE2_SIZE):
        if len(h) == k:
            break
        if sieve2[i]:
            h.append(-((sqrt_n + i) ** 2))
    assert len(h) == k

    limit = -h[-1]
    heapq.heapify(h)

    for q in primes:
        if q == 2:
            continue
        if 2 ** q > limit:
            break
        for p in primes:
            x = p ** q
            if n < x < limit:
                heapq.heappushpop(h, -x)
    print(-h[0])


if __name__ == "__main__":
    main()
