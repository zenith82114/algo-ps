/*
 * USA Computing Olympiad, USACO November 2008 Contest, Gold 3. Light Switching
 * JUNGOL 2625
 *
 * lazy segment tree
 * Date: 2026.5.9
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;

class lazy_seg_tree {
    int N, lgN;
    vector<int> ar, len;
    vector<bool> lz;

    void _apply(int i) {
        ar[i] = len[i] - ar[i];
        if (i < N) lz[i] = !lz[i];
    }
    void _push(int i) {
        if (lz[i]) _apply(i<<1), _apply(i<<1|1);
        lz[i] = false;
    }
    void _pull(int i) {
        ar[i] = ar[i<<1] + ar[i<<1|1];
    }
public:
    lazy_seg_tree(int sz) {
        N = 1, lgN = 0;
        while (N < sz) N *= 2, ++lgN;
        ar.assign(2*N, 0);
        len.assign(2*N, 1);
        for (int i = N-1; i > 0; --i) len[i] = len[i<<1] + len[i<<1|1];
        lz.assign(N, false);
    }
    void flip(int i, int j) {
        i |= N, j |= N;
        for (int k = lgN; k; --k) {
            if (    i>>k<<k !=   i) _push(i>>k);
            if ((j+1)>>k<<k != j+1) _push(j>>k);
        }
        for (int l = i, r = j; l <= r; l >>= 1, r >>= 1) {
            if ( l&1) _apply(l++);
            if (~r&1) _apply(r--);
        }
        for (int k = 1; k <= lgN; ++k) {
            if (    i>>k<<k !=   i) _pull(i>>k);
            if ((j+1)>>k<<k != j+1) _pull(j>>k);
        }
    }
    int query(int i, int j) {
        i |= N, j |= N;
        for (int k = lgN; k; --k) {
            if (    i>>k<<k !=   i) _push(i>>k);
            if ((j+1)>>k<<k != j+1) _push(j>>k);
        }
        int ans = 0;
        for (int l = i, r = j; l <= r; l >>= 1, r >>= 1) {
            if ( l&1) ans += ar[l++];
            if (~r&1) ans += ar[r--];
        }
        return ans;
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m; cin >> n >> m;
    lazy_seg_tree segt(n + 1);
    while (m--) {
        int q, s, e; cin >> q >> s >> e;
        if (q) cout << segt.query(s, e) << '\n';
        else segt.flip(s, e);
    }

    return 0;
}
