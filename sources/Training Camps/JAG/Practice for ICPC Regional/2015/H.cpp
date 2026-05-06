/*
 * ICPC Japanese Alumni Group, JAG Practice Contest for ACM-ICPC Asia Regional 2015 H. Donut Decoration
 * BOJ 13089 - lazy segment tree
 * Date: 2024.10.20
 */

#include<bits/stdc++.h>
using namespace std;
using ii = pair<int, int>;

class seg_tree {
    // States:
    // {-1, -1}: fail
    // { 0,  0}: init
    // { a,  b}: tasks a~b done once each in order, 1 <= a <= b
    vector<ii> ar;
    static int sz;
public:
    seg_tree(int n) {
        sz = 1; while (sz <= n) sz *= 2;
        ar.resize(sz * 2);
    }
    void apply(int i, const ii& t) {
        if (t.first == 0) return;
        if (ar[i].first == 0) ar[i] = t;
        else if (ar[i].second + 1 == t.first) {
            ar[i].second = t.second;
        }
        else ar[i] = ii(-1, -1);
    }
    void update(int ql, int qr, int x, int i = 1, int l = 0, int r = sz - 1) {
        if (qr < l || r < ql) return;
        if (ql <= l && r <= qr) apply(i, ii(x, x));
        else {
            apply(i<<1, ar[i]);
            apply(i<<1|1, ar[i]);
            ar[i] = ii(0, 0);
            int m = (l + r)>>1;
            update(ql, qr, x, i<<1, l, m);
            update(ql, qr, x, i<<1|1, m + 1, r);
        }
    }
    ii look(int i) { return ar[i|sz]; }
};
int seg_tree::sz = 1;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, k; cin >> n >> k;
    seg_tree segt(n);
    int q; cin >> q;
    while (q--) {
        int l, r, x; cin >> l >> r >> x;
        segt.update(l, r, x);
    }
    int ans = 0;
    for (int i = 1; i <= n; ++i) {
        // force lazy push
        segt.update(i, i, k + 1);
        if (segt.look(i) == ii(1, k + 1)) ++ans;
    }
    cout << ans;

    return 0;
}
