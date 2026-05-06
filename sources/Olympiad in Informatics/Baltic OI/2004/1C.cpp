/*
 * Baltic Olympiad in Informatics, BOI 2004 Day 1 C. Sequence
 * BOJ 13324
 *
 * slope trick
 * Date: 2022.2.25
 *
 * The variable M (commented) gives the minimized deviation. (BOJ 13323)
 */

#include<bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int N, A; cin >> N >> A;
    priority_queue<int> pq;
    pq.emplace(A);
    vector<int> T(N);
    T[0] = A;
    // uint64_t M = 0ull;
    for (int n = 1; n < N; ++n) {
        cin >> A;
        A -= n;
        if (A < pq.top()) {
            pq.emplace(A);
            // M += pq.top() - A;
            pq.pop();
        }
        pq.emplace(A);
        T[n] = pq.top();
    }

    // cout << M << '\n';
    for (int n = N - 2; ~n; --n) T[n] = min(T[n], T[n + 1]);
    for (int n = 0; n < N; ++n) cout << T[n] + n << '\n';
    return 0;
}
