/*
 * Asia-Pacific Informatics Olympiad, APIO 2007 B. Backup
 * BOJ 1150
 * JUNGOL 2007
 *
 * greedy, linked list
 * Date: 2023.5.2
 */

#include<bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int N, K; cin >> N >> K;
    vector<int> D(N);
    for (int& d : D) cin >> d;
    adjacent_difference(D.begin(), D.end(), D.begin());
    D[0] = 0;
    D.emplace_back(0);

    using ii = pair<int, int>;
    priority_queue<ii, vector<ii>, greater<ii> > pq;
    for (int i = 1; i < N; ++i) pq.emplace(D[i], i);

    vector<int> prv(N+1), nxt(N+1);
    iota(prv.begin(), prv.end(), -1); prv[0] = 0;
    iota(nxt.begin(), nxt.end(),  1); nxt[N] = N;

    vector<bool> chk(N+1, false);

    int ans = 0;
    while (K && !pq.empty()) {
        auto [d, i] = pq.top(); pq.pop();
        if (chk[i]) continue;
        ans += d; --K;

        int pi = prv[i], ni = nxt[i];
        chk[pi] = chk[ni] = true;
        D[i] = D[pi] + D[ni] - d;
        if (pi != 0 && ni != N) pq.emplace(D[i], i);

        prv[i] = prv[pi];
        nxt[i] = nxt[ni];
        nxt[prv[pi]] = ni != N? i : N;
        prv[nxt[ni]] = pi != 0? i : 0;
    }

    cout << ans;
    return 0;
}
