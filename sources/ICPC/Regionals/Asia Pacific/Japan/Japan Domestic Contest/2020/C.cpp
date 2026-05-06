/*
 * ICPC, Regionals, Asia Pacific, Japan,
 * 2020 Japan Domestic Contest C. Luggage
 * BOJ 20226 - integer factorization, binary search
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
    while (~d&1) d >>= 1, ++s;
    for (int a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
        if (n == (u64)a) return true;
        if (!probable_prime(n, d, s, a)) return false;
    }
    return true;
}

inline u64 G(u64 x, u64 c, u64 n) {
    return (mul_mod(x, x, n) + c) % n;
}

void factorize(u64 n, vector<u64>& v) {
    while (~n & 1) {
        n >>= 1;
        v.emplace_back(2);
    }
    if (n == 1) return;
    if (miller_rabin(n)) {
        v.emplace_back(n);
        return;
    }

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
        for (p = 2; p*p <= n; ++p) {
            if (n%p == 0) {
                v.emplace_back(p);
                factorize(n/p, v);
                return;
            }
        }
        v.emplace_back(n);
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    u64 n;
    for (cin >> n; n; cin >> n) {
        vector<u64> fac;
        if (n > 1) factorize(n, fac);
        sort(fac.begin(), fac.end());

        vector<u64> div { 1 };
        int sz_fac = fac.size();
        for (int i = 0, j = 1; i < sz_fac; i = j) {
            while (j < sz_fac && fac[i] == fac[j]) ++j;

            int sz_div = div.size();
            for (int k = 0; k < sz_div; ++k) {
                u64 x = div[k];
                for (int t = i; t < j; ++t) {
                    x *= fac[i];
                    div.emplace_back(x);
                }
            }
        }
        sort(div.begin(), div.end());

        u64 ans = n + 2;

        int sz_div = div.size();
        for (int i = 0; i < sz_div; ++i) {
            u64 q = div[i];
            int r0 = min(i, sz_div - 1 - i);
            int l = 0, r = r0;
            while (l != r) {
                int mid = (l + r)>>1;
                u64 x = div[mid];
                if (x*x >= q) r = mid;
                else l = mid+1;
            }
            l = r - 1;
            while (l >= 0 && q % div[l]) --l;
            if (l >= 0) ans = min(ans, div[l] + q/div[l] + n/q);
            while (r <= r0 && q % div[r]) ++r;
            if (r <= r0) ans = min(ans, div[r] + q/div[r] + n/q);
        }

        cout << ans << '\n';
    }

    return 0;
}
