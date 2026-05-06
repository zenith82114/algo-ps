/*
 * ICPC, Regionals, Northern Eurasia,
 * Northwestern Russia Regional Contest Northern Subregional 2003 K. Key Insertion
 * BOJ 7480 - disjoint sets, segment tree
 * Date: 2026.2.9
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;
const int MAXN = 1<<18;

struct seg_tree {
    int n;
    int tr[2*MAXN];

    void init(int sz) {
        for (n = 1; n < sz; n *= 2);
        fill(tr + n, tr + 2*n, 1);
        for (int i = n - 1; i; --i) tr[i] = tr[2*i] + tr[2*i + 1];
    }

    int kth(int k) {
        int i = 1;
        while (i < n) {
            if (k <= tr[2*i]) i *= 2;
            else { k -= tr[2*i]; i = 2*i + 1; }
        }
        return i - n;
    }

    void erase(int i) {
        for (i |= n; i; i /= 2) --tr[i];
    }
} segt;

array<int, MAXN> L, dsu, ans;

int _find(int i) {
    if (dsu[i] == i) return i;
    return dsu[i] = _find(dsu[i]);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m; cin >> n >> m;

    iota(dsu.begin(), dsu.end(), 0);
    vector<pair<int, int> > e;
    for (int i = 1; i <= n; ++i) {
        cin >> L[i];
        int j = _find(L[i]);
        dsu[j] = j + 1;
        e.emplace_back(j, i);
    }
    m = e.size();
    sort(e.begin(), e.end());

    ans.fill(0);
    for (int l = 0, r = 0; l < m; l = r) {
        r = l + 1;
        while (r < m && e[r - 1].first + 1 == e[r].first) ++r;
        segt.init(r - l);
        int base = e[l].first;

        for (int p = r - 1; p >= l; --p) {
            int i = e[p].second;
            int x = segt.kth(L[i] - base + 1);
            ans[x + base] = i;
            segt.erase(x);
        }
    }

    int w = e.back().first;
    cout << w << '\n';
    for (int i = 1; i <= w; ++i) cout << ans[i] << ' ';
    return 0;
}
