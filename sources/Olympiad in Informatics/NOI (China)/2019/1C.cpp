/*
 * National Olympiad in Informatics (China), NOI 2019 Day 1 C. sequence
 * BOJ 19654 - min cost flow, priority queue
 * Date: 2025.1.29
 */

#include<bits/stdc++.h>
using namespace std;
array<int, 200000> a, b;
bitset<200000> ina, inb;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int tc; cin >> tc;
    while (tc--) {
        int n, K, L; cin >> n >> K >> L;
        priority_queue<pair<int, int> > qs, qa, qb, qam, qbm;
        for (int i = 0; i < n; ++i) cin >> a[i];
        for (int i = 0; i < n; ++i) {
            cin >> b[i];
            qs.emplace(a[i] + b[i], i);
            qa.emplace(a[i], i);
            qb.emplace(b[i], i);
            ina.reset(i);
            inb.reset(i);
        }
        qs.emplace(-1e9, 0);
        qam.emplace(-1e9, 0);
        qbm.emplace(-1e9, 0);
        int cnt = 0;

        for (int k = K; k--;) {
            auto [vs, s] = qs.top();
            auto [vi, i] = qa.top();
            auto [vj, j] = qb.top();
            auto [vim, im] = qam.top();
            auto [vjm, jm] = qbm.top();
            int ci = -1, cj = -1;

            if (cnt < K - L) ci = i, cj = j;
            else {
                int best = vs;
                ci = cj = s;
                if (best < vi + vjm) {
                    best = vi + vjm, ci = i, cj = jm;
                }
                if (best < vim + vj) {
                    best = vim + vj, ci = im, cj = j;
                }
                if (best < vim + vjm) {
                    best = vim + vjm, ci = im, cj = jm;
                }
            }
            ++cnt;
            ina.set(ci);
            if (inb[ci]) --cnt;
            if (!inb[ci]) qbm.emplace(b[ci], ci);
            inb.set(cj);
            if (ina[cj]) --cnt;
            if (!ina[cj]) qam.emplace(a[cj], cj);

            while (qs.size() > 1u &&
                (ina[qs.top().second] || inb[qs.top().second])) qs.pop();
            while (!qa.empty() && ina[qa.top().second]) qa.pop();
            while (!qb.empty() && inb[qb.top().second]) qb.pop();
            while (qam.size() > 1u &&
                (ina[qam.top().second] || !inb[qam.top().second])) qam.pop();
            while (qbm.size() > 1u &&
                (inb[qbm.top().second] || !ina[qbm.top().second])) qbm.pop();
        }

        int64_t ans = 0;
        for (int i = 0; i < n; ++i) {
            if (ina[i]) ans += a[i];
            if (inb[i]) ans += b[i];
        }
        cout << ans << '\n';
    }

    return 0;
}
