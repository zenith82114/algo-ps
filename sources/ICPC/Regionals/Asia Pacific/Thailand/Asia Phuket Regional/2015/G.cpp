/*
 * ICPC, Regionals, Asia Pacific, Thailand,
 * 2015 ACM-ICPC Asia Phuket Regional Programming Contest G. Primorial vs LCM
 * BOJ 11790 - prime sieve, prefix sum, binary search
 * Date: 2023.12.4
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;

constexpr int _1e7 = 10'000'000;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);

    vector<int> spf(_1e7), primes;
    for (int i = 2; i < _1e7; ++i) {
        if (!spf[i]) {
            spf[i] = i;
            primes.emplace_back(i);
        }
        for (int p : primes) {
            if (p > spf[i] || (i64)i * p >= (i64)_1e7) break;
            spf[i * p] = p;
        }
    }

    vector<pair<i64, i64> > v;
    v.emplace_back(1, 1);
    for (int p : primes) {
        int k = (int)(14. / log10(p));
        i64 q = p;
        for (int i = 2; i <= k; ++i) {
            q *= p;
            v.emplace_back(q, p);
        }
    }
    sort(v.begin(), v.end());

    int m = v.size();
    for (int i = 1; i < m; ++i) {
        v[i].second = v[i].second * v[i-1].second % 1'000'000'007;
    }

    int t; cin >> t;
    for (int i = 1; i <= t; ++i) {
        i64 n; cin >> n;
        int l = 0, r = m;
        while (l != r) {
            int mid = (l + r)>>1;
            if (v[mid].first > n) r = mid;
            else l = mid+1;
        }
        cout << "Case " << i << ": " << v[l-1].second << '\n';
    }

    return 0;
}
