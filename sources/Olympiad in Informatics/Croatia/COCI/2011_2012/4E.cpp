/*
 * Croatian Open Competition in Informatics, COCI 2011/2012, Contest #4 E. BROJ
 * BOJ 2814
 *
 * inclusion/exclusion, binary search
 * Date: 2023.4.28
 */

#include<bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int N, P; cin >> N >> P;
    if (P > 31607) { cout << (N == 1? P : 0); return 0; }

    vector<bool> is_prime(P, true);
    vector<int> primes;
    for (int i = 2; i < P; ++i) if (is_prime[i]) {
        primes.emplace_back(i);
        for (int j = i * i; j < P; j += i) is_prime[j] = false;
    }

    if (P < 50) {
        const int M = primes.size();
        auto solve = [&] (int x) {
            x /= P;
            int64_t ans = 0;
            for (int mask = 0; mask < 1<<M; ++mask) {
                int64_t q = 1;
                for (int i = 0; i < M && q <= x; ++i)
                    if ((1<<i) & mask) q *= primes[i];
                ans += __builtin_popcount(mask) & 1? -(x/q) : x/q;
            }
            return ans;
        };

        int l = 1, r = 1e9 + 1;
        while (l < r) {
            int m = (l + r) >> 1;
            if (solve(m) < N) l = m+1; else r = m;
        }
        cout << (l > 1e9? 0 : l);
    } else {
        const int K = 1e9 / P;
        vector<int> chk(K+1, 1); chk[0] = 0;
        for (int p : primes) for (int i = p; i <= K; i += p) chk[i] = 0;
        for (int i = 1; i <= K; ++i)
            if ((chk[i] += chk[i-1]) == N) { cout << i * P; return 0; }
        cout << 0;
    }

    return 0;
}
