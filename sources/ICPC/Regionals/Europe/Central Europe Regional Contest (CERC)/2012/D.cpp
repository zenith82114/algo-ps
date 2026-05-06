/*
 * ICPC, Regionals, Europe, Central Europe Regional Contest,
 * CERC 2012 D. Non-boring sequences
 * BOJ 3408
 * JUNGOL 11525
 *
 * DnC
 * Date: 2023.6.14
 */

#include<bits/stdc++.h>
using namespace std;

vector<int> A, prv, nxt;

bool dnc(int l, int r) {
    if (l >= r) return true;
    for (int i = 0; l+i <= r-i; ++i) {
        if (prv[l+i] < l && nxt[l+i] > r)
            return dnc(l, l+i-1) && dnc(l+i+1, r);
        if (prv[r-i] < l && nxt[r-i] > r)
            return dnc(l, r-i-1) && dnc(r-i+1, r);
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);

    int T; cin >> T;
    while (T--) {
        int N; cin >> N;
        A.resize(N); for (int& a : A) cin >> a;
        auto tmp(A); sort(tmp.begin(), tmp.end());
        for (int& a : A) a = (int)(lower_bound(tmp.begin(), tmp.end(), a) - tmp.begin());

        prv.clear(); prv.resize(N, -1);
        nxt.clear(); nxt.resize(N, N);
        fill(tmp.begin(), tmp.end(), -1);
        for (int i = 0; i < N; ++i) {
            if (tmp[A[i]] != -1) prv[i] = tmp[A[i]], nxt[prv[i]] = i;
            tmp[A[i]] = i;
        }

        cout << (dnc(0, N-1)? "non-" : "") << "boring\n";
    }

    return 0;
}
