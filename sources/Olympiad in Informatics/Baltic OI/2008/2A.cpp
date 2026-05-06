/*
 * Baltic Olympiad in Informatics, BOI 2008 Day 2 A. Elections
 * BOJ 1226
 *
 * greedy, DP
 * Date: 2022.3.20
 */

#include<bits/stdc++.h>
using namespace std;


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    constexpr int INF = INT_MAX;

    int N; cin >> N;
    int K = 0;
    struct Item { int id, val; };
    vector<Item> v(N);
    for (int n = 0; n < N; ++n) {
        v[n].id = n +1;
        cin >> v[n].val;
        K += v[n].val;
    }
    K /= 2;
    sort(v.begin(), v.end(), [](const Item& i1, const Item& i2) {
        return i1.val > i2.val;
    });

    // opt[k]: id of the smallest party in some union of k seats
    array<int, 100'001> opt;
    opt.fill(INF);
    opt[0] = -1;
    int M = 0;
    for (int n = 0; n < N; ++n) {
        for (int k = 0; k <= K; ++k) {
            int kk = k + v[n].val;
            if (opt[k] < n && opt[kk] == INF) {
                opt[kk] = n;
                M = max(M, kk);
            }
        }
    }

    vector<int> ans;
    while (M) {
        ans.emplace_back(v[opt[M]].id);
        M -= v[opt[M]].val;
    }

    cout << ans.size() << '\n';
    for (const int& a : ans)
        cout << a << ' ';
    cout << '\n';
    return 0;
}
