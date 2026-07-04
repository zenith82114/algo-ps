/*
 * 수열과 쿼리 26
 * QOJ 18784
 *
 * segment tree beats
 * Date: 2023.9.7
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;
using ii = pair<int, int>;

class lazy_seg_tree {
    struct node {
        i64 sum;
        int max0, max1, max0_cnt;
    };
    vector<node> ar;
    int N;

    void _push(int n) {
        if (n & N) return;
        if (ar[n].max0 < ar[n<<1].max0) {
            ar[n<<1].sum -= (i64)ar[n<<1].max0_cnt * (ar[n<<1].max0 - ar[n].max0);
            ar[n<<1].max0 = ar[n].max0;
        }
        if (ar[n].max0 < ar[n<<1|1].max0) {
            ar[n<<1|1].sum -= (i64)ar[n<<1|1].max0_cnt * (ar[n<<1|1].max0 - ar[n].max0);
            ar[n<<1|1].max0 = ar[n].max0;
        }
    }

    void _pull(int n) {
        if (n & N) return;
        ar[n].sum = ar[n<<1].sum + ar[n<<1|1].sum;
        if (ar[n<<1].max0 == ar[n<<1|1].max0) {
            ar[n].max0 = ar[n<<1].max0;
            ar[n].max1 = max(ar[n<<1].max1, ar[n<<1|1].max1);
            ar[n].max0_cnt = ar[n<<1].max0_cnt + ar[n<<1|1].max0_cnt;
        } else {
            int i = (ar[n<<1].max0 > ar[n<<1|1].max0)? n<<1 : n<<1|1;
            int j = i^1;
            ar[n].max0 = ar[i].max0;
            ar[n].max1 = max(ar[i].max1, ar[j].max0);
            ar[n].max0_cnt = ar[i].max0_cnt;
        }
    }

    void _update_min(int n, int nl, int nr, int ql, int qr, int x) {
        _push(n);
        if (qr < nl || nr < ql || ar[n].max0 <= x) return;
        if (ql <= nl && nr <= qr && ar[n].max1 < x) {
            ar[n].sum -= (i64)ar[n].max0_cnt * (ar[n].max0 - x);
            ar[n].max0 = x;
            _push(n);
            return;
        }
        int nm = (nl + nr)>>1;
        _update_min(n<<1, nl, nm, ql, qr, x);
        _update_min(n<<1|1, nm+1, nr, ql, qr, x);
        _pull(n);
    }

    int _query_max(int n, int nl, int nr, int ql, int qr) {
        _push(n);
        if (qr < nl || nr < ql) return 0;
        if (ql <= nl && nr <= qr) return ar[n].max0;
        int nm = (nl + nr)>>1;
        return max(_query_max(n<<1, nl, nm, ql, qr),
                _query_max(n<<1|1, nm+1, nr, ql, qr));
    }

    i64 _query_sum(int n, int nl, int nr, int ql, int qr) {
        _push(n);
        if (qr < nl || nr < ql) return 0;
        if (ql <= nl && nr <= qr) return ar[n].sum;
        int nm = (nl + nr)>>1;
        return _query_sum(n<<1, nl, nm, ql, qr)
                + _query_sum(n<<1|1, nm+1, nr, ql, qr);
    }

public:
    lazy_seg_tree(const vector<int>& data) {
        int sz = data.size();
        N = 1; while (N < sz) N <<= 1;
        ar.resize(N<<1);
        for (int i = 0; i < sz; ++i) {
            ar[N|i].sum = data[i];
            ar[N|i].max0 = data[i];
            ar[N|i].max1 = -1;
            ar[N|i].max0_cnt = 1;
        }
        for (int i = sz; i < N; ++i) {
            ar[N|i].sum = 0;
            ar[N|i].max0 = 0;
            ar[N|i].max1 = -1;
            ar[N|i].max0_cnt = 1;
        }
        for (int n = N-1; n; --n) _pull(n);
    }

    void update_min(int l, int r, int x) {
        _update_min(1, 0, N-1, l, r, x);
    }

    int query_max(int l, int r) {
        return _query_max(1, 0, N-1, l, r);
    }

    i64 query_sum(int l, int r) {
        return _query_sum(1, 0, N-1, l, r);
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n; cin >> n;
    vector<int> data(n+1); for (int i = 1; i <= n; cin >> data[i++]);
    lazy_seg_tree segt(data);

    int m; cin >> m;
    while (m--) {
        int op, l, r; cin >> op >> l >> r;
        if (op == 1) {
            int x; cin >> x;
            segt.update_min(l, r, x);
        } else if (op == 2) {
            cout << segt.query_max(l, r) << '\n';
        } else {
            cout << segt.query_sum(l, r) << '\n';
        }
    }

    return 0;
}
