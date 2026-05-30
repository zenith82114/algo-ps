/*
 * ICPC, Regionals, Northern Eurasia, Northern Eurasia Finals 2018 K. King Kog's Reception
 * BOJ 16670
 * JUNGOL 12710
 *
 * segment tree
 * Date: 2025.8.27
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;
constexpr int TN = 1<<20;

struct node {
    i64 tot, end;
    node(): tot(0), end(0) {}
    node(i64 t, i64 e): tot(t), end(e) {}
    node operator+(const node& rhs) const {
        return node(tot + rhs.tot, max(rhs.end, end + rhs.tot));
    }
} segt[2*TN];

void pull(int i) {
    segt[i] = segt[i<<1] + segt[i<<1|1];
}

void segt_init() {
    for (int i = 0; i < TN; ++i) segt[i|TN].end = i;
    for (int i = TN - 1; i; --i) pull(i);
}

void segt_upd(int t, int d) {
    int i = t|TN;
    segt[i].tot += d;
    segt[i].end += d;
    for (i >>= 1; i; i >>= 1) pull(i);
}

node segt_qry(int t) {
    node ansl, ansr;
    for (int l = TN, r = t|TN; l <= r; l >>= 1, r >>= 1) {
        if ( l&1) ansl = ansl + segt[l++];
        if (~r&1) ansr = segt[r--] + ansr;
    }
    return ansl + ansr;
}

pair<int, int> que[300'004];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    segt_init();
    int q; cin >> q;
    for (int j = 1; j <= q; ++j) {
        char op; cin >> op;
        if (op == '+') {
            auto& [t, d] = que[j]; cin >> t >> d;
            segt_upd(t, d);
        }
        else if (op == '-') {
            int k; cin >> k;
            const auto& [t, d] = que[k];
            segt_upd(t, -d);
        }
        else {
            int t; cin >> t;
            cout << (segt_qry(t).end - t) << '\n';
        }
    }

    return 0;
}
