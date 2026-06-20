/*
 * Petrozavodsk Programming Camp, Winter 2019, Day 5: Gennady Korotkevich Contest 4
 * I. Nine Judges
 * QOJ 12319
 *
 * graph theory, SWAR
 * Date: 2026.6.18
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;
using u64 = uint64_t;
const int MAXN = 9, MAXK = 5e4;

int pref[MAXN][MAXK];
u64 in_mask[MAXN][MAXK];
int in_deg[MAXK];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, K, P; cin >> n >> K >> P;
    for (int i = 0; i < n; ++i)
    for (int j = 0; j < K; ++j) {
        int x; cin >> x;
        pref[i][j] = --x;
    }

    for (int b = 0; b < K; b += 64) {
        for (int i = 0; i < n; ++i) {
            u64 mask = 0;

            for (int j = 0; j < K; ++j) {
                int x = pref[i][j];

                in_mask[i][x] = mask;
                if (b <= x && x < b + 64) mask |= 1ull<<(x - b);
            }
        }

        for (int j = 0; j < K; ++j) {
            u64 s0=0, s1=0, s2=0, s3=0;

            for (int i = 0; i < n; ++i) {
                u64 c1 = s0 & in_mask[i][j]; s0 ^= in_mask[i][j];
                u64 c2 = s1 & c1; s1 ^= c1;
                u64 c3 = s2 & c2; s2 ^= c2;
                s3 ^= c3;
            }

            u64 maj = 0;
            switch (n) {
                case 1: maj = s0; break;
                case 3: maj = s1; break;
                case 5: maj = s2 | (s1 & s0); break;
                case 7: maj = s2; break;
                case 9: maj = s3 | (s2 & (s1 | s0)); break;
            }
            in_deg[j] += __builtin_popcountll(maj);
        }
    }

    vector<int> ord(K); iota(begin(ord), end(ord), 0);
    sort(begin(ord), end(ord), [](int x, int y) { return in_deg[x] < in_deg[y]; });
    for (int i = 0; i < P; ++i) cout << (ord[i]+1) << ' ';
    return 0;
}
