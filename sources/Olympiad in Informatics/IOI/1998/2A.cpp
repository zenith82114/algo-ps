/*
 * International Olympiad in Informatics, IOI 1998, Day 2 A. Picture
 * BOJ 2185
 * JUNGOL 1631
 *
 * sweep line, segment tree
 * Date: 2024.9.2
 */

#include<bits/stdc++.h>
using namespace std;

struct node_ {
    int val = 0, len = 0, cnt = 0, lf = 0, rf = 0;
} segt[1<<16];

void segt_add(
    int ql, int qr, int v,
    int n = 1, int l = -10'000, int r = +9'999
) {
    if (qr < l || r < ql) return;
    auto& curr = segt[n];
    if (ql <= l && r <= qr) { curr.val += v; }
    else {
        int mid = (l + r)>>1;
        segt_add(ql, qr, v, n<<1, l, mid);
        segt_add(ql, qr, v, n<<1|1, mid+1, r);
    }
    if (curr.val) {
        curr.len = r - l + 1;
        curr.cnt = curr.lf = curr.rf = 1;
    }
    else if (l == r) {
        curr.len = 0;
        curr.cnt = curr.lf = curr.rf = 0;
    }
    else {
        const auto& lc = segt[n<<1];
        const auto& rc = segt[n<<1|1];
        curr.len = lc.len + rc.len;
        curr.cnt = lc.cnt + rc.cnt - (lc.rf & rc.lf);
        curr.lf = lc.lf;
        curr.rf = rc.rf;
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    struct event {
        int l, r, y, v;
        event(int l, int r, int y, int v)
        : l(l), r(r), y(y), v(v) {}
        bool operator<(const event& rhs) const {
            if (y != rhs.y) return y < rhs.y;
            return v > rhs.v;
        }
    };
    vector<event> evs;

    int n; cin >> n;
    for (int i = 0; i < n; ++i) {
        int x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
        if (x1 > x2) swap(x1, x2);
        if (y1 > y2) swap(y1, y2);
        evs.emplace_back(x1, x2 - 1, y1, +1);
        evs.emplace_back(x1, x2 - 1, y2, -1);
    }
    sort(evs.begin(), evs.end());

    int64_t ans = 0;
    int py = 0, plen = 0;
    for (auto [l, r, y, v] : evs) {
        ans += 2 * segt[1].cnt * (y - py);
        segt_add(l, r, v);
        ans += abs(plen - segt[1].len);
        py = y;
        plen = segt[1].len;
    }

    cout << ans;
    return 0;
}
