"""
# Petrozavodsk Programming Camp, Winter 2021, Day 5: Almost Retired Dandelion Contest, ICPC Camp Contest 2 G. Remove the Prime
# Open Cup 2020/2021 Stage 11: Grand Prix of Nizhny Novgorod G. Remove the Prime
# BOJ 21088 - prime factorization, sweep line
# Date: 2026.1.31
"""

def maybe_prime(x, d, s, a):
    y = pow(a, d, x)
    if y == 1: return True
    for _ in range(s):
        if y == x - 1: return True
        y = pow(y, 2, x)
        if y == 1: return False
    return False


def miller_rabin(x):
    d, s = x - 1, 0
    while ~d & 1: d, s = d//2, s + 1
    for a in [2,3,5,7,11,13,17,19,23,29,31,37]:
        if x == a: return True
        if not maybe_prime(x, d, s, a): return False
    return True


def main() -> None:
    import sys
    rd = lambda: sys.stdin.readline().rstrip()
    from math import gcd, isqrt

    SIEVE_SIZE = 10**6 + 5
    spf = list(range(SIEVE_SIZE))
    for p in range(2, SIEVE_SIZE):
        if spf[p] < p: continue
        for q in range(p*p, SIEVE_SIZE, p):
            if spf[q] == q: spf[q] = p

    small_primes = [p for p in range(2, SIEVE_SIZE) if spf[p] == p]
    active = {}
    z = 1
    active_z = -1

    n = int(rd())
    a = list(map(int, rd().split()))
    a.append(1)
    grundy = 0

    for i, x in enumerate(a):
        small_factors = set()
        for p in small_primes:
            if x < p*p: break
            if x < SIEVE_SIZE: break
            if x % p == 0:
                small_factors.add(p)
                while x % p == 0: x //= p

        if 1 < x < SIEVE_SIZE:
            while x > 1:
                p = spf[x]
                small_factors.add(p)
                x //= p

        for p in list(active.keys()):
            if p < SIEVE_SIZE:
                if p not in small_factors:
                    grundy ^= (i - active[p])
                    del active[p]
            elif gcd(p, x) == 1:
                grundy ^= (i - active[p])
                del active[p]
            else:
                while x % p == 0: x //= p

        for p in small_factors:
            if p not in active:
                active[p] = i

        if z > 1:
            g = gcd(z, x)
            if g == 1:
                z = 1
            elif g < z:
                grundy ^= (i - active_z)
                active[g] = active_z
                while x % g == 0: x //= g
                z = 1
            else:
                x = 1

        if x > 1:
            if miller_rabin(x):
                active[x] = i
            else:
                r = isqrt(x)
                if r*r == x:
                    active[r] = i
                else:
                    z, active_z = x, i

    print("First" if grundy else "Second")


if __name__ == "__main__":
    main()
