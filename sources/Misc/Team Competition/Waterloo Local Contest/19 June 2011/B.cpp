/*
 * Waterloo's local Programming Contests, 19 June, 2011 B. Factoring Large Numbers
 * BOJ 4149 - Miller-Rabin primality test, Pollard's rho alg.
 * Date: 2024.12.9
 */

#include<bits/stdc++.h>
using namespace std;
using u64 = uint64_t;

default_random_engine rng;
uniform_int_distribution<u64> dist;

u64 mul_mod(u64 a, u64 b, u64 n) {
    u64 r = 0;
    a %= n;
    b %= n;
    for (; b; b >>= 1) {
        if (b&1) {
            r += a;
            r = r >= n? r - n : r;
        }
        a <<= 1;
        a = a >= n? a - n : a;
    }
    return r;
}

u64 pow_mod(u64 a, u64 b, u64 n) {
    u64 r = 1;
    a %= n;
    for (; b; b >>= 1) {
        if (b&1) r = mul_mod(a, r, n);
        a = mul_mod(a, a, n);
    }
    return r;
}

bool probable_prime(u64 n, u64 d, int s, int a) {
    u64 x = pow_mod(a, d, n);
    if (x == 1) return true;
    while (s--) {
        if (x == n-1) return true;
        x = mul_mod(x, x, n);
        if (x == 1) return false;
    }
    return false;
}

bool miller_rabin(u64 n) {
    u64 d = n-1;
    int s = 0;
    while (~d&1)
        d >>= 1, ++s;
    for (int a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
        if (n == (u64)a) return true;
        if (!probable_prime(n, d, s, a)) return false;
    }
    return true;
}

void factorize(u64 n, vector<u64>& v) {
    if (miller_rabin(n)) {
        v.push_back(n);
        return;
    }

    const auto G = [] (u64 x, u64 c, u64 n) {
        return (mul_mod(x, x, n) + c) % n;
    };

    u64 p = 1;
    while (p == 1) {
        u64 x = dist(rng) % n;
        u64 y = x;
        u64 c = dist(rng) % n;
        while (p == 1) {
            x = G(x, c, n);
            y = G(G(y, c, n), c, n);
            p = gcd(n, x > y? x - y : y - x);
        }
        if (p == n) p = 1;
    }

    if (p != n) {
        factorize(p, v);
        factorize(n/p, v);
    }
    else {
        for (p = 3; p*p <= n; p += 2) {
            if (n%p == 0) {
                v.push_back(p);
                factorize(n/p, v);
                return;
            }
        }
        v.push_back(n);
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    u64 N; cin >> N;
    vector<u64> v;
    while (~N & 1) {
        N >>= 1;
        v.push_back(2);
    }
    if (N > 1) factorize(N, v);
    sort(v.begin(), v.end());
    for (auto& p : v) cout << p << '\n';
    return 0;
}
