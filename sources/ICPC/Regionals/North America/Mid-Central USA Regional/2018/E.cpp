/*
 * ICPC, Regionals, North America,
 * 2018 Mid-Central USA Regional Programming Contest E. Coprime Integers
 * 2018 Pacific Northwest Region Programming Contest Division 1 B. Coprime Integers
 * BOJ 16409 - Mobius Inversion
 * Date: 2023.2.12
 */

#include<bits/stdc++.h>
using namespace std;

using i64 = int64_t;
constexpr int SZ = 1e7 +1;

array<int, SZ> spf, Mu;
vector<int> primes;

i64 solve(const int n, const int m) {
    if (!n || !m) return 0ll;

    i64 ans = 0ll;
    for (int i = 1, j = 0; i <= min(n, m); i = j+1) {
        j = min(n / (n / i), m / (m / i));
        ans += 1ll * (n / i) * (m / i) * (Mu[j] - Mu[i-1]);
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    spf.fill(0);
    Mu.fill(0); Mu[1] = 1;
    for (int i = 2; i < SZ; ++i) {
        if (!spf[i]) {
            spf[i] = i;
            Mu[i] = -1;
            primes.emplace_back(i);
        }
        for (const int& p : primes) {
            if (p < spf[i] && 1ll * i * p < SZ) {
                spf[i * p] = p;
                Mu[i * p] = Mu[i] * Mu[p];
            }
            else break;
        }
        if (1ll * i * spf[i] < SZ)
            spf[i * spf[i]] = spf[i];
    }

    partial_sum(Mu.begin(), Mu.end(), Mu.begin());

    int a, b, c, d; cin >> a >> b >> c >> d;
    cout << (solve(b, d) - solve(a-1, d) - solve(b, c-1) + solve(a-1, c-1));
    return 0;
}
