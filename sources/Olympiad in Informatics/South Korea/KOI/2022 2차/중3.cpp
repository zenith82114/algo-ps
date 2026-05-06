/*
 * 한국정보올림피아드, KOI 2022 2차대회, 중등부 3. 주차 타워
 * BOJ 25404
 * JUNGOL 5201
 *
 * DP, segment tree
 * Date: 2023.9.29
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;
constexpr i64 inf = INT64_MAX>>1;

class seg_tree {
    vector<i64> ar;
    int n;
public:
    seg_tree(int sz) {
        n = 1; while (n < sz) n *= 2;
        ar.resize(2*n, inf);
    }
    void update(int i, i64 x) {
        for (ar[i |= n] = x; i > 1; i >>= 1)
            ar[i>>1] = min(ar[i], ar[i^1]);
    }
    i64 query(int i, int j) {
        i64 ans = inf;
        for (i |= n, j |= n; i <= j; i >>= 1, j >>= 1) {
            if ( i&1) ans = min(ans, ar[i++]);
            if (~j&1) ans = min(ans, ar[j--]);
        }
        return ans;
    }
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);

    int n; cin >> n;
    vector<pair<int, int> > v;
    for (int x = 0; x < n; ++x) {
        int a; cin >> a;
        v.emplace_back(a, x);
    }
    sort(v.begin(), v.end());

    vector<i64> dp(n, inf);
    seg_tree segt_p(n); segt_p.update(0, 0);
    seg_tree segt_m(n); segt_m.update(0, 0);
    vector<int> dirty { 0 };

    for (int i = 0, j = 0; i < n; i = ++j) {
        while (j+1 < n && v[i].first == v[j+1].first) ++j;

        int y0 = v[i].second;
        int y1 = v[j].second;
        dp[y0] = min(dp[y0], segt_p.query(0, y1) + n - y0);
        dp[y0] = min(dp[y0], segt_m.query(0, y1) + 2*y1 - y0);
        dp[y0] = min(dp[y0], segt_p.query(y1, n-1) - y0);
        dp[y0] = min(dp[y0], segt_m.query(y1, n-1) + n + 2*y1 - y0);
        dp[y1] = min(dp[y1], segt_p.query(0, y0) + n - 2*y0 + y1);
        dp[y1] = min(dp[y1], segt_m.query(0, y0) + y1);
        dp[y1] = min(dp[y1], segt_p.query(y0, n-1) - 2*y0 + y1);
        dp[y1] = min(dp[y1], segt_m.query(y0, n-1) + n + y1);

        if (i < j) {
            for (int k = i; k < j; ++k) {
                int y0 = v[k].second;
                int y1 = v[k+1].second;
                dp[y0] = min(dp[y0], segt_p.query(0, y1) + 2*n + y0 - 2*y1);
                dp[y0] = min(dp[y0], segt_m.query(0, y1) + n + y0);
                dp[y0] = min(dp[y0], segt_p.query(y1, n-1) + n + y0 - 2*y1);
                dp[y0] = min(dp[y0], segt_m.query(y1, n-1) + 2*n + y0);
                dp[y1] = min(dp[y1], segt_p.query(0, y0) + 2*n - y1);
                dp[y1] = min(dp[y1], segt_m.query(0, y0) + n + 2*y0 - y1);
                dp[y1] = min(dp[y1], segt_p.query(y0, n-1) + n - y1);
                dp[y1] = min(dp[y1], segt_m.query(y0, n-1) + 2*n + 2*y0 - y1);
            }
        }

        for (int x : dirty) { segt_p.update(x, inf); segt_m.update(x, inf); }
        dirty.clear();
        for (int k = i; k <= j; ++k) {
            int x = v[k].second;
            dirty.emplace_back(x);
            segt_p.update(x, dp[x] + x);
            segt_m.update(x, dp[x] - x);
        }
    }

    i64 ans = inf;
    for (int i = n-1; i >= 0 && v[i].first == v[n-1].first; --i) {
        ans = min(ans, dp[v[i].second]);
    }
    cout << ans;
    return 0;
}
