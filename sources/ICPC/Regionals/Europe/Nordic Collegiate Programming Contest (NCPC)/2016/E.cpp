/*
 * ICPC, Regionals, Europe, Northwestern Europe Regional Contest,
 * Nordic Collegiate Programming Contest, NCPC 2016 E. Exponial
 * JUNGOL 15877
 *
 * Euler's totient function
 * Date: 2026.5.30
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;

inline int pow_mod(int a, int e, int m) {
    int b = 1;
    for (; e; e >>= 1) {
        if (e&1) b = (1ll*b*a)%m;
        a = (1ll*a*a)%m;
    }
    return b;
}

int phi(int m) {
    int ret = m;
    for (int p = 2; p*p <= m; ++p) {
        if (m%p == 0) {
            ret -= ret/p;
            while (m%p == 0) m /= p;
        }
    }
    if (m > 1) ret -= ret/m;
    return ret;
}

int func(int i, int phi_m) {
    if (i <= 1 || phi_m == 1) return 1;

    int r = func(i-1, phi(phi_m));
    i64 y = 1;
    for (int j = 0; j < r && y < phi_m; ++j) y *= i;
    if (y < phi_m) return y;
    return pow_mod(i, r, phi_m) + phi_m;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m; cin >> n >> m;
    cout << pow_mod(n, func(n-1, phi(m)), m);
    return 0;
}
