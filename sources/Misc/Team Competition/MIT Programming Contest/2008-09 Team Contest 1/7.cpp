/*
 * MIT Programming Contest 2008-09, Team Contest 1 7. Rectangle
 * JUNGOL 1568
 *
 * segment tree, sweep line
 * Date: 2026.5.7
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;

struct edge {
    int x, y1, y2;
    bool is_left;
    bool operator<(const edge &other) const {
        return x < other.x;
    }
};
vector<edge> edges;

vector<int> ys;
int enc(int y) {
    return distance(ys.begin(), lower_bound(ys.begin(), ys.end(), y));
}

class seg_tree {
    int N;
    vector<int> cnt, len, val;

    void _update(int p) {
        if (cnt[p]) val[p] = len[p];
        else val[p] = (p < N) ? (val[p<<1] + val[p<<1|1]) : 0;
    }

    void _apply(int p, int x) {
        cnt[p] += x;
        _update(p);
    }

public:
    seg_tree(int sz) {
        N = 1; while (N < sz) N *= 2;
        cnt.assign(2*N, 0);
        val.assign(2*N, 0);
        len.assign(2*N, 0);
        for (int i = 0; i < sz - 1; ++i) len[N + i] = ys[i + 1] - ys[i];
        for (int i = N - 1; i > 0; --i) len[i] = len[i<<1] + len[i<<1|1];
    }

    void add(int l, int r, int x) {
        l |= N; r |= N;
        for (int i = l, j = r; i <= j; i >>= 1, j >>= 1) {
            if ( i&1) _apply(i++, x);
            if (~j&1) _apply(j--, x);
        }
        for (int i = 1; (l >> i) > 0; ++i) {
            _update(l >> i);
            _update(r >> i);
        }
    }

    int query() { return val[1]; }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n; cin >> n;
    for (int i = 0; i < n; ++i) {
        int x1, x2, y1, y2;
        cin >> x1 >> x2 >> y1 >> y2;
        edges.push_back({x1, y1, y2, true});
        edges.push_back({x2, y1, y2, false});
        ys.push_back(y1);
        ys.push_back(y2);
    }
    sort(begin(edges), end(edges));
    sort(begin(ys), end(ys));
    ys.erase(unique(begin(ys), end(ys)), end(ys));

    seg_tree segt(ys.size());
    int x_pre = 0;
    int active_len = 0;
    i64 ans = 0;

    for (auto [x, y1, y2, is_left] : edges) {
        ans += 1ll * active_len * (x - x_pre);
        x_pre = x;
        segt.add(enc(y1), enc(y2) - 1, is_left ? 1 : -1);
        active_len = segt.query();
    }

    cout << ans;
    return 0;
}
