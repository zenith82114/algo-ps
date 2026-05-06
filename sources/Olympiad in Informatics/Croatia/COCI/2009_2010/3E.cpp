/*
 * Croatian Open Competition in Informatics, COCI 2009/2010, Contest #3 E. PATULJCI
 * BOJ 2912
 * JUNGOL 4187
 *
 * segment tree, binary search
 * Date: 2025.8.3
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;

struct node { int val = 0, cnt = 0; } segt[1<<20];

node merge(const node& l, const node& r) {
    if (l.val == r.val) return { l.val, l.cnt + r.cnt };
    return { (l.cnt > r.cnt? l : r).val, abs(l.cnt - r.cnt) };
}

vector<int> grp[10004];

int range_cnt(int i, int j, int v) {
    const auto& g = grp[v];
    return upper_bound(g.begin(), g.end(), j)
         - lower_bound(g.begin(), g.end(), i);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, _; cin >> n >> _;
    int tn = 1; while (tn <= n) tn *= 2;
    for (int i = 1; i <= n; ++i) {
        int v; cin >> v;
        segt[tn|i] = { v, 1 };
        grp[v].emplace_back(i);
    }
    for (int i = tn - 1; i; --i) segt[i] = merge(segt[i<<1], segt[i<<1|1]);

    int q; cin >> q;
    while (q--) {
        int a, b; cin >> a >> b;
        int ans = 0;
        for (int i = tn|a, j = tn|b; i <= j; i /= 2, j /= 2) {
            if (i&1) {
                if (range_cnt(a, b, segt[i].val)*2 > b - a + 1) {
                    ans = segt[i].val;
                    break;
                }
                ++i;
            }
            if (~j&1) {
                if (range_cnt(a, b, segt[j].val)*2 > b - a + 1) {
                    ans = segt[j].val;
                    break;
                }
                --j;
            }
        }
        if (ans) cout << "yes " << ans << '\n';
        else cout << "no\n";
    }

    return 0;
}
