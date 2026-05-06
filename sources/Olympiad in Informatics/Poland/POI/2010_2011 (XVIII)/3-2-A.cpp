/*
 * Polish Olympiad in Informatics, POI 2010/2011, Stage 3 Day 2 A. Meteors
 * BOJ 8217 - parallel binary search, segment tree
 * Date: 2023.5.4
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;

class seg_tree {
    int N;
    vector<i64> ar;
public:
    seg_tree(int sz) {
        for (N = 1; N < sz; N <<= 1);
        ar.resize(N<<1);
    }
    void add(int l, int r, int x) {
        for (l |= N, r |= N; l <= r; l >>= 1, r >>= 1) {
            if ( l&1) ar[l++] += x;
            if (~r&1) ar[r--] += x;
        }
    }
    i64 query(int i) {
        i64 ans = 0;
        for (i |= N; i; i >>= 1) ans += ar[i];
        return ans;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int N, M; cin >> N >> M;

    vector<vector<int> > own(N);
    for (int j = 1; j <= M; ++j) {
        int i; cin >> i;
        own[--i].emplace_back(j);
    }

    vector<int> P(N); for (int& p : P) cin >> p;

    int K; cin >> K;
    struct query { int l, r, a; };
    vector<query> Q(K);
    for (auto& [l, r, a] : Q) cin >> l >> r >> a;

    vector<int> lo(N, 0), hi(N, K);
    vector<vector<int> > ls(K);

    for (int iter = 1; iter <= K; iter <<= 1) {
        for (auto& l : ls) l.clear();
        for (int i = 0; i < N; ++i) if (lo[i] != hi[i])
            ls[(lo[i] + hi[i])>>1].emplace_back(i);

        seg_tree segt(M+1);

        for (int k = 0; k < K; ++k) {
            const auto& [l, r, a] = Q[k];
            if (l <= r)
                segt.add(l, r, a);
            else
                segt.add(l, M, a), segt.add(1, r, a);
            for (int i : ls[k]) {
                i64 ans = 0;
                for (int j : own[i]) ans = min(ans + segt.query(j), (i64)1e9+1);
                if (ans < P[i]) lo[i] = k+1; else hi[i] = k;
            }
        }
    }

    for (int k : lo) if (k < K) cout << k+1 << '\n'; else cout << "NIE\n";

    return 0;
}
