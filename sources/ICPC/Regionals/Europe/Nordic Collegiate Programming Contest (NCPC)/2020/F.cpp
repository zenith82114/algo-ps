/*
 * ICPC, Regionals, Europe, Northwestern Europe Regional Contest,
 * Nordic Collegiate Programming Contest, NCPC 2020 F. Film Critics
 * Petrozavodsk Programming Camp, Winter 2021, Day 3: Nordic+ Contest 2020 F. Film Critics
 * BOJ 21052 - greedy
 * Date: 2023.7.12
 */

#include<bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);

    int N, M, K; cin >> N >> M >> K;
    if (K == 0 || K%M != 0) { cout << "impossible"; return 0; }

    vector<pair<int, int> > v; v.reserve(N);
    for (int i = 1; i <= N; ++i) {
        int a; cin >> a; v.emplace_back(a, i);
    }
    sort(v.begin(), v.end());

    const int p = K/M;
    int s = M;
    vector<int> ans { v[N-p].second };
    int i = N-p-1, j = N-p+1;
    for (int k = 1; k < N; ++k) {
        if (j < N && s <= k * v[j].first) {
            s += M;
            ans.emplace_back(v[j].second);
            ++j;
        }
        else if (i > -1 && s > k * v[i].first) {
            ans.emplace_back(v[i].second);
            --i;
        }
        else { cout << "impossible"; return 0; }
    }
    for (int i : ans) cout << i << ' ';
    return 0;
}
