/*
 * ICPC, World Finals, ACM-ICPC World Finals 2016 G. Oil
 * BOJ 12771
 * JUNGOL 10802
 *
 * rotating sweep line
 * Date: 2023.1.10
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;
using vec2 = complex<i64>;

inline i64 cross(const vec2& u, const vec2& v) {
    return (conj(u) * v).imag();
}
inline int ccw(const vec2& o, const vec2& p, const vec2& q) {
    i64 x = cross(p - o, q - o);
    return x < 0? -1 : x > 0? 1 : 0;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int N; cin >> N;
    int DN = N<<1;

    struct Event {
        vec2 pnt;
        int seg_id;
        bool right;
        Event(int x, int y, int i, int r): pnt(x, y), seg_id(i), right(r) {}
    };
    vector<Event> ev0; ev0.reserve(DN);
    vector<int> amt; amt.reserve(N);
    for (int i = 0; i < N; ++i) {
        int x0, x1, y; cin >> x0 >> x1 >> y;
        if (x0 > x1) swap(x0, x1);
        ev0.emplace_back(x0, y, i, false);
        ev0.emplace_back(x1, y, i, true);
        amt.emplace_back(x1 - x0);
    }

    i64 ans = 0L;
    for (const auto& ei : ev0) {
        vec2 orig = ei.pnt;
        vector<Event> ev;
        for (auto ej : ev0) {
            if (ej.pnt.imag() < orig.imag()) {
                ej.pnt = orig * 2L - ej.pnt;
                ej.right = !ej.right;
                ev.emplace_back(ej);
            }
            else if (ej.pnt.imag() > orig.imag())
                ev.emplace_back(ej);
        }

        sort(ev.begin(), ev.end(), [&orig] (const Event& e1, const Event& e2) {
            int c = ccw(orig, e1.pnt, e2.pnt);
            return c? c > 0 : e1.right && !e2.right;
        });

        i64 sum = amt[ei.seg_id];
        ans = max(ans, sum);
        for (const auto& e : ev) {
            sum += e.right? amt[e.seg_id] : -amt[e.seg_id];
            ans = max(ans, sum);
        }
    }

    cout << ans << '\n';
    return 0;
}
