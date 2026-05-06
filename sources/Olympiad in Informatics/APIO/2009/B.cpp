/*
 * Asia-Pacific Informatics Olympiad, APIO 2009 B. The Siruseri Convention Centre
 * BOJ 4012
 * JUNGOL 2458
 *
 * greedy, sparse table
 * Date: 2024.12.1
 *
 * cf. https://juejin.cn/post/6953858056610381838
 */

#include<bits/stdc++.h>
using namespace std;
constexpr int INF = 0x3f3f3f3f;

int n;
struct elem {
    int l, r;
    elem(int l, int r): l(l), r(r) {}
    bool operator<(const elem& e) const {
        return make_pair(l, r) < make_pair(e.l, e.r);
    }
};
vector<elem> v0, v;
int spt[18][200005];

int max_mis(int l, int r) {
    int i = lower_bound(v.begin(), v.end(), elem{l, l}) - v.begin();
    if (i == n || r < v[i].r) return 0;
    int ans = 1;
    for (int k = 17; k >= 0; --k) {
        if (spt[k][i] < n && v[spt[k][i]].r <= r) {
            i = spt[k][i];
            ans += (1<<k);
        }
    }
    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n0; cin >> n0;
    for (int i = 0; i < n0; ++i) {
        int l, r; cin >> l >> r;
        v0.emplace_back(l, r);
        v.emplace_back(l, r);
    }

    /* remove any segment that includes another */
    sort(v.begin(), v.end(), [] (const elem& x, const elem& y) {
        return make_pair(x.r, -x.l) < make_pair(y.r, -y.l);
    });
    n = 1;
    for (int i = 1; i < n0; ++i) if (v[n - 1].l < v[i].l) v[n++] = v[i];
    v.erase(v.begin() + n, v.end());
    /* now v[].l and v[].r are both strictly increasing sequences */

    /* build sparse table */
    for (int i = 0, j = 0; i < n; ++i) {
        while (j < n && v[j].l <= v[i].r) ++j;
        spt[0][i] = j;
    }
    spt[0][n] = n;
    for (int k = 1; k < 18; ++k)
    for (int i = 0; i <= n; ++i) spt[k][i] = spt[k - 1][spt[k - 1][i]];

    /* MIS starting with v[0] */
    cout << max_mis(-INF, INF) << '\n';

    set<elem> s;
    s.emplace(-INF, -INF);
    s.emplace(INF, INF);
    for (int i = 0; i < n0; ++i) {
        auto lb = s.lower_bound(v0[i]);
        int l1 = prev(lb)->r;
        int r1 = v0[i].l;
        int l2 = v0[i].r;
        int r2 = lb->l;
        if (l1 >= r1 || l2 >= r2) continue;
        /* if OK to add to MIS */
        if (max_mis(l1 + 1, r1 - 1) + 1 + max_mis(l2 + 1, r2 - 1)
            == max_mis(l1 + 1, r2 - 1)
        ) {
            cout << (i + 1) << ' ';
            s.emplace(v0[i]);
        }
    }

    return 0;
}
