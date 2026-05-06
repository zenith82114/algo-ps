/*
 * ICPC Japanese Alumni Group, JAG Summer Camp 2015 Day 4 D. Identity Function
 * BOJ 16808 - Euler's totient function
 * Date: 2023.6.2
 */

#include<bits/stdc++.h>
using namespace std;

vector<int> primes; // < 32000

vector<int> factorize(int n) {
    vector<int> v;
    for (int p : primes) while (n > 1 && n % p == 0) {
        v.emplace_back(p);
        n /= p;
    }
    if (n > 1) v.emplace_back(n);
    return v;
}

int phi(int n) {
    auto v = factorize(n);
    v.erase(unique(v.begin(), v.end()), v.end());
    for (int p : v) n -= n / p;
    return n;
}

vector<int> divisors(int n) {
    vector<int> v;
    int d = 1;
    for (; d * d < n; ++d) if (n % d == 0) {
        v.emplace_back(d);
        v.emplace_back(n / d);
    }
    if (d * d == n) v.emplace_back(d);
    sort(v.begin(), v.end());
    return v;
}

int pow_mod(int x, int e, int m) {
    int y = 1;
    x %= m;
    for (; e; e >>= 1) {
        if (e&1) y = (1LL * y * x) % m;
        x = (1LL * x * x) % m;
    }
    return y;
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);

    vector<int> spf(32000);
    for (int i = 2; i < 32000; ++i) {
        if (!spf[i]) {
            spf[i] = i;
            primes.emplace_back(i);
        }
        for (int p : primes) {
            if (p > spf[i] || 1LL * i * p >= 32000LL) break;
            spf[i * p] = p;
        }
    }

    int N; cin >> N;
    const auto v = factorize(N);
    for (size_t i = 1; i < v.size(); ++i)
        if (v[i-1] == v[i]) { cout << -1; return 0; }


    int64_t ans = 1LL;
    for (int p : v) {
        if (gcd(N, p-1) != 1) { cout << -1; return 0; }

        const auto div = divisors(phi(p-1));
        for (int d : div) if (pow_mod(N, d, p-1) == 1) {
            ans = lcm(ans, d); break;
        }
    }

    cout << ans;
    return 0;
}
