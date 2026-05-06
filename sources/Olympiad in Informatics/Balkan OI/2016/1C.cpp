/*
 * Balkan Olympiad in Informatics, BOI 2016 C. Power towers
 * BOJ 13970
 *
 * Euler's totient function
 * Date: 2025.12.23
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;

inline int pow_mod(int a, int e, int m) {
    int b = 1;
    for (; e; e >>= 1) {
        if (e&1) b = (1ll * b * a) % m;
        a = (1ll * a * a) % m;
    }
    return b;
}

vector<int> phi, x;
int n;

int func(int i, int phi_m) {
    if (phi_m == 1 || i == n) return 1;

    int r = func(i + 1, phi[phi_m]);
    i64 y = 1;
    for (int j = 0; j < r && y < phi_m; ++j) y *= x[i];
    if (y < phi_m) return y;
    return pow_mod(x[i], r, phi_m) + phi_m;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int tc, m; cin >> tc >> m;

    phi.resize(m + 1);
    iota(phi.begin(), phi.end(), 0);
    for (int p = 2; p <= m; ++p) if (phi[p] == p) {
        for (int q = p; q <= m; q += p) {
            phi[q] -= phi[q] / p;
        }
    }

    while (tc--) {
        cin >> n;
        x.resize(n);
        for (int& xi : x) cin >> xi;
        cout << pow_mod(x[0], func(1, phi[m]), m) << '\n';
    }

    return 0;
}
