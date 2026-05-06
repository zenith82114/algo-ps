/*
 * Croatian Open Competition in Informatics, COCI 2011/2012, Contest #5 F. POPLOČAVANJE
 * BOJ 2809
 * JUNGOL 3723
 *
 * suffix array
 * Date: 2023.3.5
 */

#include<bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int N; cin >> N;
    string T; cin >> T;

    vector<int> rnk(N<<1);
    vector<int> cnt(128, 0);
    for (int i = 0; i < N; ++i) cnt[T[i]] = 1;
    for (int i = 1; i < 128; ++i) cnt[i] += cnt[i-1];
    for (int i = 0; i < N; ++i) rnk[i] = cnt[T[i]];
    cnt.resize(N+1);

    vector<int> sa(N);

    for (int d = 1; d < N; d <<= 1) {
        vector<int> tmp(N, 0);

        fill(cnt.begin(), cnt.end(), 0);
        for (int i = 0; i < N; ++i) ++cnt[rnk[i+d]];
        for (int i = 1; i < N; ++i) cnt[i] += cnt[i-1];
        for (int i = N-1; ~i; --i) tmp[--cnt[rnk[i+d]]] = i;

        fill(cnt.begin(), cnt.end(), 0);
        for (int i = 0; i < N; ++i) ++cnt[rnk[i]];
        for (int i = 1; i < N; ++i) cnt[i] += cnt[i-1];
        for (int i = N-1; ~i; --i) sa[--cnt[rnk[tmp[i]]]] = tmp[i];

        auto cmp = [&](int a, int b) {
            return make_pair(rnk[a], rnk[a+d]) < make_pair(rnk[b], rnk[b+d]);
        };
        vector<int> nrnk(N<<1);
        nrnk[sa[0]] = 1;
        for (int i = 1; i < N; ++i)
            nrnk[sa[i]] = nrnk[sa[i-1]] + cmp(sa[i-1], sa[i]);
        if (nrnk[sa.back()] == N)
            break;
        swap(rnk, nrnk);
    }

    vector<int> mark(N, 0);

    int M; cin >> M;
    while (M--) {
        string P; cin >> P;
        int l = 0, r = N;

        for (int i = 0; i < (int)P.size(); ++i) {
            int tl = l, tr = r;
            while (tl < tr) {
                int m = (tl + tr)>>1;
                if (sa[m] + i < N && T[sa[m] + i] >= P[i]) tr = m;
                else tl = m+1;
            }
            int nl = tl;

            tl = l, tr = r;
            while (tl < tr) {
                int m = (tl + tr)>>1;
                if (sa[m] + i < N && T[sa[m] + i] > P[i]) tr = m;
                else tl = m+1;
            }

            l = nl, r = tr;
        }

        for (int i = l; i < r; ++i) {
            mark[sa[i]]++;
            if (sa[i] + (int)P.size() < N)
                mark[sa[i] + P.size()]--;
        }
    }

    partial_sum(mark.begin(), mark.end(), mark.begin());
    cout << count(mark.begin(), mark.end(), 0);
    return 0;
}
