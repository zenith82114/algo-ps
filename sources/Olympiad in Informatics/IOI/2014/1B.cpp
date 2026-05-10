/*
 * International Olympiad in Informatics, IOI 2014, Day 1 B. Wall
 * JUNGOL 4680
 *
 * lazy segment tree
 * Date: 2026.5.10
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;
using ii = pair<int, int>;
constexpr int INF = 1e9;

class lazy_seg_tree {
    int N, lgN;
    vector<ii> lz;

    int _clamp(int v, ii x) {
        return max(x.first, min(v, x.second));
    }
    void _apply(int i, ii x) {
        lz[i].first = _clamp(lz[i].first, x);
        lz[i].second = _clamp(lz[i].second, x);
    }
    void _push(int i) {
        _apply(i<<1, lz[i]), _apply(i<<1|1, lz[i]);
        lz[i] = ii(-INF, INF);
    }

public:
    lazy_seg_tree(int n) {
        N = 1, lgN = 0;
        while (N < n) N *= 2, ++lgN;
        lz.assign(2*N, ii(-INF, INF));
    }
    void update(int i, int j, ii x) {
        i |= N, j |= N;
        for (int k = lgN; k; --k) {
            if (    i>>k<<k !=   i) _push(i>>k);
            if ((j+1)>>k<<k != j+1) _push(j>>k);
        }
        for (int l = i, r = j; l <= r; l >>= 1, r >>= 1) {
            if ( l&1) _apply(l++, x);
            if (~r&1) _apply(r--, x);
        }
    }
    int query(int i) {
        i |= N;
        for (int k = lgN; k; --k) _push(i>>k);
        return _clamp(0, lz[i]);
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m; cin >> n >> m;
    lazy_seg_tree segt(n);
    while (m--) {
        int op, i, j, h; cin >> op >> i >> j >> h;
        segt.update(i, j, (op&1) ? ii(h, INF) : ii(-INF, h));
    }
    for (int i = 0; i < n; ++i) cout << segt.query(i) << '\n';
    return 0;
}
