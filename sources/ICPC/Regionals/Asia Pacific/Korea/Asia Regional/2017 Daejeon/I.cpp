/*
 * ICPC, Regionals, Asia Pacific, Korea,
 * Asia Regional - Daejeon 2017 I. Slot Machines
 * BOJ 14959
 *
 * KMP
 * Date: 2022.10.2
 */

#include<bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int N; cin >> N;
    vector<int> T(N);
    for (int i = N-1; ~i; --i) cin >> T[i];

    vector<int> pf(N);
    int K = N-1;
    int P = 1;
    for (int i = 1, j = 0; i < N; ++i) {
        while (j && T[i] != T[j])
            j = pf[j-1];
        if (T[i] == T[j]) ++j;
        pf[i] = j;

        int k = N-1 - i;
        int p = i+1 - j;
        if (K+P > k+p || (K+P == k+p && P > p)) {
            K = k; P = p;
        }
    }

    cout << K << ' ' << P << '\n';
    return 0;
}
