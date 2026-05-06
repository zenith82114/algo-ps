/*
 * Central Europe Olympiad in Informatics, CEOI 2011, Day 1 B. Matching
 * BOJ 3308
 * JUNGOL 3715
 *
 * KMP, linked list
 * Date: 2026.3.22
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;
constexpr int MAXN = 1e6, MAXM = 1e6;

int s[MAXN], t[MAXM];
array<int, MAXN> rs, lptr, rptr, p, q, ff;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m; cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        cin >> rs[i];
        s[--rs[i]] = i;
    }
    for (int i = 0; i < m; ++i) cin >> t[i];

    iota(lptr.begin(), lptr.begin() + n, -1);
    iota(rptr.begin(), rptr.begin() + n, 1); rptr[n - 1] = -1;
    for (int i = n - 1; i > -1; --i) {
        int x = s[i];
        p[i] = (lptr[x] > -1 ? rs[lptr[x]] : -1);
        q[i] = (rptr[x] > -1 ? rs[rptr[x]] : -1);
        if (rptr[x] > -1) lptr[rptr[x]] = lptr[x];
        if (lptr[x] > -1) rptr[lptr[x]] = rptr[x];
    }

    auto equiv = [](int a[], int i, int j) -> bool {
        if (p[j] != -1 and a[i] <= a[i - j + p[j]]) return false;
        if (q[j] != -1 and a[i] >= a[i - j + q[j]]) return false;
        return true;
    };

    ff[0] = 0;
    for (int j = 0, i = 1; i < n; ++i) {
        while (j > 0 && !equiv(s, i, j)) j = ff[j - 1];
        if (equiv(s, i, j)) ++j;
        ff[i] = j;
    }

    vector<int> ans;
    for (int j = 0, i = 0; i < m; ++i) {
        while (j > 0 && !equiv(t, i, j)) j = ff[j - 1];
        if (equiv(t, i, j)) ++j;
        if (j == n) {
            ans.push_back(i - n + 2);
            j = ff[j - 1];
        }
    }

    cout << ans.size() << '\n';
    for (int i : ans) cout << i << ' ';
    return 0;
}
