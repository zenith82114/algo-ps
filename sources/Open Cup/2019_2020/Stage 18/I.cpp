/*
 * Open Cup 2019/2020 Stage 18: Grand Prix of Bytedance
 * I. Longest Lyndon Prefix
 * QOJ 7406
 *
 * suffix array, stack
 * Date: 2026.7.8
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;
using ii = pair<int, int>;

vector<int> suffix_array(const string& s) {
    const int n = s.size();

    vector<int> rnk(2*n), cnt(max(n+1, 128));
    for (int i = 0; i < n; ++i) cnt[s[i]] = 1;
    for (int i = 1; i < 128; ++i) cnt[i] += cnt[i-1];
    for (int i = 0; i < n; ++i) rnk[i] = cnt[s[i]];
    cnt.resize(n+1);

    vector<int> sa(n), tmp(n);

    for (int d = 1; d < n; d *= 2) {
        fill(begin(tmp), end(tmp), 0);

        fill(cnt.begin(), cnt.end(), 0);
        for (int i = 0; i < n; ++i) ++cnt[rnk[i+d]];
        for (int i = 1; i <= n; ++i) cnt[i] += cnt[i-1];
        for (int i = n-1; i >= 0; --i) tmp[--cnt[rnk[i+d]]] = i;

        fill(cnt.begin(), cnt.end(), 0);
        for (int i = 0; i < n; ++i) ++cnt[rnk[i]];
        for (int i = 1; i <= n; ++i) cnt[i] += cnt[i-1];
        for (int i = n-1; i >= 0; --i) sa[--cnt[rnk[tmp[i]]]] = tmp[i];

        vector<int> nrnk(2*n);
        nrnk[sa[0]] = 1;

        auto cmp = [&] (int a, int b) -> int {
            return rnk[a] < rnk[b] || (rnk[a] == rnk[b] && rnk[a+d] < rnk[b+d]);
        };

        for (int i = 1; i < n; ++i) nrnk[sa[i]] = nrnk[sa[i-1]] + cmp(sa[i-1], sa[i]);
        if (nrnk[sa[n-1]] == n) break;
        rnk.swap(nrnk);
    }

    return sa;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int tc; cin >> tc;
    while (tc--) {
        int n; cin >> n;
        string str; cin >> str;

        auto sa = suffix_array(str);
        vector<int> isa(n);
        for (int i = 0; i < n; ++i) isa[sa[i]] = i;

        stack<int> stc;
        vector<int> ans(n);

        for (int i = n-1; i >= 0; --i) {
            while (!stc.empty() && isa[stc.top()] > isa[i]) stc.pop();
            ans[i] = (stc.empty() ? n : stc.top()) - i;
            stc.push(i);
        }
        for (int i = 0; i < n; ++i) cout << ans[i] << ' ';
        cout << '\n';
    }

    return 0;
}
