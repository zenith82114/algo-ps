/*
 * JOI 2015/2016 Spring Camp Day 2 C. Toilets
 * BOJ 17709
 * JUNGOL 5017
 *
 * greedy
 * Date: 2023.8.16
 */

#include<bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    using i64 = int64_t;

    i64 N; cin >> N;
    int M; cin >> M;
    i64 psum = 0, psumx = 0;
    while (M--) {
        string s; i64 k; cin >> s >> k;
        int del = 0, delx = 0;
        for (char c : s) {
            del += c == 'F'? +1 : -1;
            delx = max(delx, del);
        }
        psumx = max(psumx, psum + (k - 1)*max(0, del) + delx);
        psum += k*del;
    }
    if (psum < 0) cout << -1;
    else cout << max(0L, psumx - psum - 1);
    return 0;
}
