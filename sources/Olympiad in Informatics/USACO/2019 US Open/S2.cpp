/*
 * USA Computing Olympiad, USACO 2019 US Open Contest, Silver 2. Cow Steeplechase II
 * BOJ 17196
 * JUNGOL 4124
 *
 * Shamos-Hoey alg.
 * Date: 2023.6.8
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;

struct point {
    i64 x, y;
    bool operator<(const point& p) const {
        return make_pair(x, y) < make_pair(p.x, p.y);
    }
};

struct segment {
    point l, r;
    int id;
    double eval(i64 x) const {
        if (l.x == r.x) return l.y;
        return l.y + (double)(r.y - l.y) * (x - l.x) / (r.x - l.x);
    }
    bool operator<(const segment& seg) const {
        i64 x = max(l.x, seg.l.x);
        return 1e-9 < seg.eval(x) - eval(x);
    }
};

int ccw(const point& o, const point& a, const point& b) {
    i64 t = (a.x - o.x) * (b.y - o.y) - (b.x - o.x) * (a.y - o.y);
    return t? (t > 0? 1 : -1) : 0;
}

bool intersect(const segment& s1, const segment& s2) {
    const auto& [a, b, i1] = s1;
    const auto& [c, d, i2] = s2;
    int ab = ccw(a, b, c) * ccw(a, b, d);
    int cd = ccw(c, d, a) * ccw(c, d, b);
    if (!(ab || cd)) return !(b < c || d < a);
    return ab <= 0 && cd <= 0;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);

    int N; cin >> N;

    vector<segment> segm(N);
    for (int i = 0; i < N; ++i) {
        auto& [l, r, id] = segm[i];
        cin >> l.x >> l.y >> r.x >> r.y;
        if (r < l) swap(l, r);
        id = i;
    }

    using ii = pair<int, int>;
    vector<ii> evt;
    for (int i = 0; i < N; ++i) {
        evt.emplace_back(i, 0);
        evt.emplace_back(i, 1);
    }
    sort(evt.begin(), evt.end(), [&] (const ii& e1, const ii& e2) {
        const auto& [i1, f1] = e1;
        const auto& [i2, f2] = e2;
        const point& p1 = (f1 == 0? segm[i1].l : segm[i1].r);
        const point& p2 = (f2 == 0? segm[i2].l : segm[i2].r);
        return make_pair(p1.x, f1) < make_pair(p2.x, f2);
    });

    set<segment> s;
    vector<set<segment>::iterator> ptrs(N);
    int ans1 = -1, ans2 = -1;

    for (const auto& [i, f] : evt) {
        if (f == 0) {
            auto p = s.lower_bound(segm[i]);
            if (p != s.end() && intersect(*p, segm[i])) {
                ans1 = p->id, ans2 = i; break;
            }
            if (p != s.begin() && intersect(*prev(p), segm[i])) {
                ans1 = prev(p)->id, ans2 = i; break;
            }
            ptrs[i] = s.insert(p, segm[i]);
        }
        else {
            auto p = ptrs[i];
            if (next(p) != s.end() && p != s.begin() && intersect(*next(p), *prev(p))) {
                ans1 = next(p)->id, ans2 = prev(p)->id; break;
            }
            s.erase(p);
        }
    }

    if (ans1 > ans2) swap(ans1, ans2);
    int cnt = 0;
    for (int i = 0; i < N; ++i) if (i != ans2 && intersect(segm[i], segm[ans2])) {
        if (++cnt > 1) break;
    }
    cout << (cnt == 1? ans1 : ans2) + 1;
    return 0;
}
