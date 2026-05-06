/*
 * Petrozavodsk Programming Camp, Winter 2019, Day 1: 300iq Contest J. Jealous Split
 * BOJ 18456 - Aliens trick, convex hull trick
 * Date: 2026.2.5
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;
using i128 = __int128_t;
// typedef __int128 i128;
const int MAXN = 1e5 + 4;

int n;
i128 s[MAXN], dp[MAXN];
int min_cnt[MAXN], max_cnt[MAXN];

struct line {
    i128 y0, m;
    int id;
    line(i128 y0, i128 m, int id): y0(y0), m(m), id(id) {};
    i128 eval(i128 x) { return y0 + m*x; }
};

inline bool chk(const line& a, const line& b, const line& c, int tie_brk) {
    return (b.y0 - a.y0)*(b.m - c.m) - (c.y0 - b.y0)*(a.m - b.m) >= tie_brk;
}

void solve(i128 lmd, int cnt[], int tie_brk) {
    int sz = 1;
    deque<line> hl; hl.emplace_back(0, 0, 0);

    for (int i = 1; i <= n; ++i) {
        while (sz > 1 && hl[0].eval(s[i]) - hl[1].eval(s[i]) >= tie_brk) {
            --sz; hl.pop_front();
        }
        dp[i] = s[i]*s[i] + lmd + hl[0].eval(s[i]);
        cnt[i] = cnt[hl[0].id] + 1;

        line f(dp[i] + s[i]*s[i], -2*s[i], i);

        if (sz && hl.back().m == f.m) {
            if (hl.back().y0 > f.y0) {
                --sz; hl.pop_back();
            }
            else if (hl.back().y0 == f.y0) {
                if (!tie_brk) hl.back().id = i;
                continue;
            }
            else continue;
        }
        while (sz > 1 && chk(hl[sz - 2], hl[sz - 1], f, tie_brk)) {
            --sz; hl.pop_back();
        }
        ++sz; hl.push_back(f);
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cout << "Yes\n";

    int k;
    cin >> n >> k;
    for (int i = 1; i <= n; ++i) {
        int a; cin >> a;
        s[i] = s[i - 1] + a;
    }

    i128 lo = -1, hi = s[n]*s[n] + 1;
    while (lo + 1 < hi) {
        i128 mid = (lo + hi)/2;
        solve(mid, max_cnt, 0);
        (max_cnt[n] >= k ? lo : hi) = mid;
    }
    solve(lo, min_cnt, 1);
    solve(lo, max_cnt, 0);

    vector<int> ans;
    --k;
    for (int j = n - 1, i = n; j; --j) {
        i128 cost = (s[i] - s[j])*(s[i] - s[j]);
        if (min_cnt[j] <= k && k <= max_cnt[j] && dp[i] == dp[j] + cost + lo) {
            ans.push_back(j);
            i = j;
            --k;
        }
    }
    reverse(ans.begin(), ans.end());
    for (int i : ans) cout << i << ' ';
    return 0;
}
