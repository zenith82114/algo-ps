/*
 * USA Computing Olympiad, USACO December 2006 Contest, Gold 3
 * BOJ 6206
 * JUNGOL 4188
 *
 * suffix/LCP arrays, sliding window min/max with deque
 * Date: 2025.12.24
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, k; cin >> n >> k;
    vector<int> s(n); for (int& x : s) cin >> x;

    vector<int> cnt(int(1e6) + 1, 0);
    for (int i = 0; i < n; ++i) cnt[s[i]] = 1;
    partial_sum(begin(cnt), end(cnt), begin(cnt));
    vector<int> rnk(2*n);
    for (int i = 0; i < n; ++i) rnk[i] = cnt[s[i]];
    cnt.resize(n + 1);

    vector<int> sa(n);

    for (int d = 1; d < n; d *= 2) {
        vector<int> tmp(n, 0);

        fill(cnt.begin(), cnt.end(), 0);
        for (int i = 0; i < n; ++i) ++cnt[rnk[i + d]];
        partial_sum(begin(cnt), end(cnt), begin(cnt));
        for (int i = n - 1; i > -1; --i) tmp[--cnt[rnk[i + d]]] = i;

        fill(cnt.begin(), cnt.end(), 0);
        for (int i = 0; i < n; ++i) ++cnt[rnk[i]];
        partial_sum(begin(cnt), end(cnt), begin(cnt));
        for (int i = n - 1; i > -1; --i) sa[--cnt[rnk[tmp[i]]]] = tmp[i];

        auto cmp = [&](int a, int b) {
            return make_pair(rnk[a], rnk[a + d]) < make_pair(rnk[b], rnk[b + d]);
        };
        vector<int> nrnk(2*n);
        nrnk[sa[0]] = 1;
        for (int i = 1; i < n; ++i) {
            nrnk[sa[i]] = nrnk[sa[i - 1]] + cmp(sa[i - 1], sa[i]);
        }
        if (nrnk[sa.back()] == n) break;
        rnk.swap(nrnk);
    }

    vector<int> isa(n);
    for (int i = 0; i < n; ++i) isa[sa[i]] = i;

    vector<int> lcp(n);
    for (int z = 0, i = 0; i < n; ++i) if (isa[i]) {
        int j = sa[isa[i] - 1];
        while (i + z < n && j + z < n && s[i + z] == s[j + z]) ++z;
        lcp[isa[i]] = z? z-- : 0;
    }

    deque<int> dq;
    for (int i = 1; i < k; ++i) {
        while (!dq.empty() && lcp[dq.back()] >= lcp[i]) dq.pop_back();
        dq.push_back(i);
    }
    int ans = lcp[dq.front()];
    for (int i = k; i < n; ++i) {
        while (!dq.empty() && dq.front() < i - k + 2) dq.pop_front();
        while (!dq.empty() && lcp[dq.back()] >= lcp[i]) dq.pop_back();
        dq.push_back(i);
        ans = max(ans, lcp[dq.front()]);
    }

    cout << ans;
    return 0;
}
