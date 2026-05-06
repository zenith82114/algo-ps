/*
 * ICPC, Regionals, Europe, Central Europe Regional Contest,
 * CTU Open Contest 2011 G. Simple Polygon
 * BOJ 6620 - Shamos-Hoey alg.
 * Date: 2023.4.11
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;

struct point {
    i64 x, y;
    bool operator<(const point& p) const {
        return make_pair(x, y) < make_pair(p.x, p.y);
    }
    bool operator==(const point& p) const {
        return x == p.x && y == p.y;
    }
};

vector<pair<point, point> > endp;

struct segment {
    static i64 t;
    double y0, m;
    int id;
    segment(int i): id(i) {
        const auto& [a, b] = endp[i];
        m = (double)(b.y - a.y) / (b.x - a.x);
        y0 = a.y - m * a.x;
    }
    bool operator<(const segment& other) const {
        return y0 + m * t < other.y0 + other.m * t;
    }
};
i64 segment::t = 0L;

int ccw(const point& o, const point& a, const point& b) {
    i64 x1 = a.x - o.x, y1 = a.y - o.y;
    i64 x2 = b.x - o.x, y2 = b.y - o.y;
    i64 t = x1 * y2 - x2 * y1;
    return t? (t > 0? 1 : -1) : 0;
}

bool intersects(int i, int j) {
    const auto& [a, b] = endp[i];
    const auto& [c, d] = endp[j];

    if (a == c && ccw(a, b, d) != 0) return false;
    if (b == d && ccw(a, b, c) != 0) return false;
    if (a == d || b == c) return false;

    int ab = ccw(a, b, c) * ccw(a, b, d);
    int cd = ccw(c, d, a) * ccw(c, d, b);
    if (!(ab || cd)) return !(b < c || d < a);
    return ab <= 0 && cd <= 0;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int N; cin >> N;
    while (N) {
        endp.resize(N);

        for (auto& s : endp) {
            i64 x, y; cin >> x >> y;
            auto& [nx, ny] = s.first;
            // change basis so that no segment can be vertical
            nx = 30000 * x - y;
            ny = x + 30000 * y;
        }
        for (int i = 0; i < N; ++i) endp[i].second = endp[(i+1)%N].first;
        for (auto& [a, b] : endp) if (b < a) swap(a, b);

        using event = pair<int, bool>;
        vector<event> evt;
        for (int i = 0; i < N; ++i) {
            evt.emplace_back(i, true);
            evt.emplace_back(i, false);
        }
        sort(evt.begin(), evt.end(), [&] (const event& e1, const event& e2) {
            const auto& [i1, b1] = e1;
            const auto& [i2, b2] = e2;
            const point& p1 = b1? endp[i1].first : endp[i1].second;
            const point& p2 = b2? endp[i2].first : endp[i2].second;
            return make_tuple(p1.x, b1, p1.y) < make_tuple(p2.x, b2, p2.y);
        });

        multiset<segment> ms;
        bool ans = true;

        for (const auto& [i, b] : evt) {
            if (b) {
                segment::t = endp[i].first.x + 1;
                auto it = ms.emplace(i);
                if (it != ms.begin() && intersects(i, prev(it)->id)) ans = false;
                if (next(it) != ms.end() && intersects(i, next(it)->id)) ans = false;
            } else {
                segment::t = endp[i].second.x - 1;
                auto it = ms.find(segment(i));
                if (it != ms.begin() && next(it) != ms.end() &&
                    intersects(prev(it)->id, next(it)->id)) ans = false;
                ms.erase(it);
            }
            if (!ans) break;
        }

        cout << (ans? "YES\n" : "NO\n");
        cin >> N;
    }

    return 0;
}
