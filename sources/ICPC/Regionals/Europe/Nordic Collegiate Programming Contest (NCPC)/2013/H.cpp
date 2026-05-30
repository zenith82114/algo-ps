/*
 * ICPC, Regionals, Europe, Northwestern Europe Regional Contest,
 * Nordic Collegiate Programming Contest, NCPC 2013 H. Pinball
 * BOJ 9244
 * JUNGOL 15848
 *
 * sweep line, BBST
 * Date: 2025.2.1
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;

struct point { i64 x, y; };
struct segment {
    point l, r;
    int id;
    double eval(i64 X) const {
        return l.y + (double)(r.y - l.y)*(X - l.x)/(r.x - l.x);
    }
    bool operator<(const segment& oth) const {
        i64 X = max(l.x, oth.l.x);
        return make_pair(eval(X), id) < make_pair(oth.eval(X), oth.id);
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n; cin >> n;
    vector<segment> seg(n+1);

    for (int i = 1; i <= n; ++i) {
        auto& [l, r, id] = seg[i];
        cin >> l.x >> l.y >> r.x >> r.y;
        if (l.x > r.x) swap(l, r);
        id = i;
    }
    seg[0].l.x = -1'000'002;
    seg[0].l.y = +1'000'002;
    cin >> seg[0].r.x;
    seg[0].r.y = +1'000'001;
    seg[0].id = 0;

    vector<tuple<i64, int, i64, int> > evt;

    for (int i = 0; i <= n; ++i) {
        auto& [l, r, id] = seg[i];
        evt.emplace_back(l.x, 0, +l.y, i);
        evt.emplace_back(r.x, 1, -r.y, i);
    }
    sort(evt.begin(), evt.end());

    vector<int> succ(n+1, -1);
    set<segment> bbst;
    vector<set<segment>::iterator> iters(n+1);

    for (auto& [x, right, y, id] : evt) {
        if (right) y = -y;
        if (!right) {
            iters[id] = bbst.emplace(seg[id]).first;
        }
        if (y == min(seg[id].l.y, seg[id].r.y)) {
            if (iters[id] != bbst.begin()) {
                succ[id] = prev(iters[id])->id;
            }
        }
        if (right) {
            bbst.erase(iters[id]);
        }
    }

    i64 ans = seg[0].r.x;
    for (int i = 0; i != -1; i = succ[i]) {
        const auto& [l, r, id] = seg[i];
        ans = l.y < r.y? l.x : r.x;
    }
    cout << ans;
    return 0;
}
