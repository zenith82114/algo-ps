/*
 * USA Computing Olympiad, USACO US Open 2016 Contest, Platinum 3. Landscaping
 * BOJ 12010
 * JUNGOL 3631
 *
 * DP
 * Date: 2023.6.27
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;
constexpr i64 inf = INT64_MAX>>2;

int N, X, Y, Z;

vector<i64> dp(vector<int>& v) {
    const int M = v.size();
    vector<i64> res(M), pfs(M);

    res[1] = min(X + Y, Z * abs(v[1] - v[0]));
    int i = (res[1] == X + Y? 0 : -2);
    i64 tmp = (res[1] == X + Y? X + Y : inf);

    for (int j = 3; j < M; j += 2) {
        pfs[j] = pfs[j-2] + Z * abs(v[j-1] - v[j-2]);
        tmp += Z * abs(v[j-1] - v[j-2]);
        while (i+2 < j && X + Y <= Z * abs(v[j] - v[i+2])) {
            i += 2;
            tmp = min(tmp, X + Y + pfs[j] - pfs[i+1] + (i > 0? res[i-1] : 0));
        }
        res[j] = min(tmp, res[j-2] + Z * abs(v[j] - v[j-1]));
    }

    return res;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);

    cin >> N >> X >> Y >> Z;

    vector<int> ar, ty;
    for (int i = 0; i < N; ++i) {
        int a, b; cin >> a >> b;
        while (a--) { ar.emplace_back(i); ty.emplace_back(+1); }
        while (b--) { ar.emplace_back(i); ty.emplace_back(-1); }
    }
    int sz = ar.size();
    if (!sz) { cout << 0; return 0; }

    int lv = 0;
    int mx_lv = 0, mn_lv = 0;
    for (int i = 1; i < sz; ++i) if (ty[i-1] == ty[i]) {
        lv += ty[i];
        mx_lv = max(mx_lv, lv);
        mn_lv = min(mn_lv, lv);
    }
    lv = 0;
    if (mn_lv < 0) { mx_lv -= mn_lv; lv = -mn_lv; }

    vector<vector<int> > vs(mx_lv + 1);
    vector<int> cst(mx_lv + 1);
    vs[lv].emplace_back(0);
    cst[lv] = ty[0] > 0? Y : X;
    for (int i = 1; i < sz; ++i) {
        if (ty[i-1] == ty[i]) lv += ty[i];
        if (vs[lv].empty()) cst[lv] = (ty[i] > 0? Y : X);
        vs[lv].emplace_back(ar[i]);
    }

    i64 ans = 0;
    for (lv = 0; lv <= mx_lv; ++lv) {
        auto& v = vs[lv];
        int M = v.size();
        if (M == 1) {
            ans += cst[lv];
            continue;
        }
        auto res1 = dp(v);
        if (M & 1) {
            reverse(v.begin(), v.end());
            auto res2 = dp(v);
            i64 tmp = min(res1[M-2], res2[M-2]);
            for (int i = 1; i+2 < M; i += 2)
                tmp = min(tmp, res1[i] + res2[M-3-i]);
            ans += tmp + cst[lv];
        }
        else ans += res1[M-1];
    }
    cout << ans;
    return 0;
}
