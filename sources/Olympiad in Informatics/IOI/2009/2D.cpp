/*
 * International Olympiad in Informatics, IOI 2009, Day 2 D. Salesman
 * BOJ 5466
 * JUNGOL 3622
 *
 * DP, segment tree
 * Date: 2023.1.12
 */

#include<bits/stdc++.h>
using namespace std;

class seg_tree {
    static const int N = 1<<19;
    vector<int> arr;
public:
    seg_tree(): arr(N<<1, (int)-2e9) {}
    void update(int i, int x) {
        for (arr[i |= N] = x; i > 1; i >>= 1)
            arr[i>>1] = max(arr[i], arr[i^1]);
    }
    int query(int i, int j) {
        int ans = INT_MIN;
        for (i |= N, j |= N; i <= j; i >>= 1, j >>= 1) {
            if (i&1)  ans = max(ans, arr[i++]);
            if (~j&1) ans = max(ans, arr[j--]);
        }
        return ans;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int N, U, D, S; cin >> N >> U >> D >> S;
    struct Market { int t, l, m; };
    vector<Market> mks(N);
    for (auto& [t, l, m] : mks) cin >> t >> l >> m;
    sort(mks.begin(), mks.end(), [] (const Market& mk1, const Market& mk2) {
        return mk1.t != mk2.t? mk1.t < mk2.t : mk1.l < mk2.l;
    });

    vector<int> dp(N), dp_u(N), dp_d(N);
    seg_tree segt_u, segt_d;
    segt_u.update(S, -U * S);
    segt_d.update(S, D * S);

    for (int i = 0, j = 0; i < N; i = ++j) {
        while (j+1 < N && mks[i].t == mks[j+1].t) j++;

        for (int k = i; k <= j; ++k) {
            const auto& [t, l, m] = mks[k];
            dp[k] = m + max(
                segt_u.query(l+1, 500'001) + U * l,
                segt_d.query(1, l) - D * l);
        }
        dp_u[j] = dp[j];
        for (int k = j-1; k >= i; --k)
            dp_u[k] = max(dp[k], dp_u[k+1] - U * (mks[k+1].l - mks[k].l) + mks[k].m);
        dp_d[i] = dp[i];
        for (int k = i+1; k <= j; ++k)
            dp_d[k] = max(dp[k], dp_d[k-1] - D * (mks[k].l - mks[k-1].l) + mks[k].m);

        for (int k = i; k <= j; ++k) {
            const int& l = mks[k].l;
            dp[k] = max({ dp[k], dp_u[k], dp_d[k] });
            segt_u.update(l, dp[k] - U * l);
            segt_d.update(l, dp[k] + D * l);
        }
    }

    cout << max(
        segt_u.query(S+1, 500'001) + U * S,
        segt_d.query(1, S) - D * S) << '\n';
    return 0;
}
