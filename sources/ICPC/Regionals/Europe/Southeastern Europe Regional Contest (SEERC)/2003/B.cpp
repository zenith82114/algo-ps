/*
 * ICPC, Regionals, Europe, Southeastern Europe Regional Contest,
 * SEERC 2003 B. Hidden Password
 * BOJ 3789 - lexicographically minimal string rotation; suffix array
 * Date: 2023.6.12
 */

#include<bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);

    int T; cin >> T;
    while (T--) {
        int N; cin >> N; N = 2*N + 1;
        string S; cin >> S; S = S + S + char(127);
        int i;

        vector<int> rnk(N<<1);
        vector<int> cnt(128);
        for (i = 0; i < N; ++i) cnt[S[i]] = 1;
        for (i = 1; i < 128; ++i) cnt[i] += cnt[i-1];
        for (i = 0; i < N; ++i) rnk[i] = cnt[S[i]];
        cnt.resize(N+1);

        vector<int> sa(N);

        for (int d = 1; d < N; d <<= 1) {
            vector<int> tmp(N, 0);

            fill(cnt.begin(), cnt.end(), 0);
            for (i = 0; i < N; ++i) ++cnt[rnk[i+d]];
            for (i = 1; i < N; ++i) cnt[i] += cnt[i-1];
            for (i = N-1; ~i; --i) tmp[--cnt[rnk[i+d]]] = i;

            fill(cnt.begin(), cnt.end(), 0);
            for (i = 0; i < N; ++i) ++cnt[rnk[i]];
            for (i = 1; i < N; ++i) cnt[i] += cnt[i-1];
            for (i = N-1; ~i; --i) sa[--cnt[rnk[tmp[i]]]] = tmp[i];

            auto cmp = [&] (int a, int b) -> int {
                return rnk[a] < rnk[b] || (rnk[a] == rnk[b] && rnk[a+d] < rnk[b+d]);
            };
            vector<int> nrnk(N<<1);
            nrnk[sa[0]] = 1;
            for (i = 1; i < N; ++i)
                nrnk[sa[i]] = nrnk[sa[i-1]] + cmp(sa[i-1], sa[i]);
            if (nrnk[sa[N-1]] == N) break;
            rnk.swap(nrnk);
        }

        cout << sa[0] << '\n';
    }

    return 0;
}
