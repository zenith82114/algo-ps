/*
 * ICPC, Regionals, Asia Pacific, Japan,
 * ACM-ICPC Asia Tsukuba Regional Contest 2017 I. Starting a Scenic Railroad Service
 * BOJ 15337 - greedy, sweep line
 * Date: 2022.11.26
 */

#include<bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int N; cin >> N;
    vector<pair<int, int>> A(N);
    for (auto& a : A) cin >> a.first >> a.second;

    array<int, 100'001> pfs, sfs;

    pfs.fill(0); sfs.fill(0);
    for (const auto& a : A) {
        ++pfs[a.second];
        ++sfs[a.first];
    }
    partial_sum(pfs.begin(), pfs.end(), pfs.begin());
    partial_sum(sfs.rbegin(), sfs.rend(), sfs.rbegin());
    int ans1 = INT_MAX;
    for (const auto& a : A) {
        ans1 = min(ans1, pfs[a.first] + sfs[a.second]);
    }
    ans1 = N - ans1;

    pfs.fill(0);
    for (const auto& a : A) {
        ++pfs[a.first];
        --pfs[a.second];
    }
    partial_sum(pfs.begin(), pfs.end(), pfs.begin());
    int ans2 = *max_element(pfs.begin(), pfs.end());

    cout << ans1 << ' ' << ans2 << '\n';
    return 0;
}
