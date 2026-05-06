/*
 * USA Computing Olympiad, USACO February 2005 Contest, Gold 1. Jersey Politics
 * BOJ 2203
 *
 * reedy, knapsack
 * Date: 2026.1.25
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;

int val[181];
int opt[61][60001] {};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int k; cin >> k;
    for (int i = 1; i <= 3*k; ++i) cin >> val[i];
    vector<int> ord(3*k); iota(ord.begin(), ord.end(), 1);
    sort(ord.begin(), ord.end(), [] (int i, int j) { return val[i] > val[j]; });
    for (int i = 2*k; i < 3*k; ++i) cout << ord[i] << '\n';
    ord.erase(ord.begin() + 2*k, ord.end());

    int su = 0;
    for (int i : ord) su += val[i];
    assert(su >= 1000*k + 2);

    opt[0][0] = -1;

    for (int i : ord) {
        int x = val[i];
        for (int j = k - 1; j >= 0; --j)
        for (int s = 0; s + x <= (su/2); ++s) {
            if (opt[j][s] != 0 && opt[j + 1][s + x] == 0) opt[j + 1][s + x] = i;
        }
    }

    int s = 500*k + 1;
    while (s <= (su/2) && opt[k][s] == 0) ++s;
    assert(s <= su/2);
    for (int j = k; j > 0; --j) {
        int i = opt[j][s];
        s -= val[i];
        auto p = find(ord.begin(), ord.end(), i);
        assert(p != ord.end());
        ord.erase(p);
        cout << i << '\n';
    }
    for (int i : ord) cout << i << '\n';

    return 0;
}
