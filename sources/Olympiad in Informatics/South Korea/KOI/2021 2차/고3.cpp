/*
 * 한국정보올림피아드, KOI 2021 2차대회, 고등부 3. 가장 긴 공통 괄호 문자열
 * BOJ 22349
 * JUNGOL 4807
 *
 * suffix/LCP arrays, binary search
 * Date: 2026.1.3
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int tc; cin >> tc;
    while (tc--) {
        string a, b; cin >> a >> b;
        if (a.size() > b.size()) swap(a, b);
        const string s = a + (char)127 + b;
        const int na = a.size();
        const int n = s.size();

        vector<int> cnt(128, 0);
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

        vector<int> psum(na + 1), fall(na + 1, na + 1);
        // fall[i] := min { j; i < j && psum[i] > psum[j] }
        stack<int> stk;
        for (int i = 0; i < na; ++i) psum[i + 1] = psum[i] + (a[i] == '(' ? +1 : -1);
        for (int i = 0; i <= na; ++i) {
            while (!stk.empty() && psum[stk.top()] > psum[i]) {
                fall[stk.top()] = i; stk.pop();
            }
            stk.push(i);
        }

        vector<int> lim(na);
        // lim[i] := max { L; a.substr(i, L) is substring of b }
        for (int i = 0, t = 0; i < n - 1; ++i) {
            if (sa[i] < na) {
                t = min(t, lcp[i]);
                lim[sa[i]] = t;
            }
            else t = n;
        }
        for (int i = n - 2, t = 0; i >= 0; --i) {
            if (sa[i] < na) {
                lim[sa[i]] = max(lim[sa[i]], t);
                t = min(t, lcp[i]);
            }
            else t = lcp[i];
        }

        const int lo = *min_element(begin(psum), end(psum));
        const int hi = *max_element(begin(psum), end(psum));
        vector<vector<int> > buckets(hi - lo + 1);
        for (int i = 0; i <= na; ++i) buckets[psum[i] - lo].push_back(i);

        int ans = 0;
        for (int i = 0; i <= na; ++i) {
            const auto& b = buckets[psum[i] - lo];
            auto f = --lower_bound(begin(b), end(b), min(fall[i], i + lim[i] + 1));
            if (f >= begin(b)) ans = max(ans, *f - i);
        }
        cout << ans << '\n';
    }

    return 0;
}
