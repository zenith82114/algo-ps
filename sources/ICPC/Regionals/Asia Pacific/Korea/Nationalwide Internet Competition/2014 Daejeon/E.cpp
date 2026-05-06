/*
 * ICPC, Regionals, Asia Pacific, Korea,
 * Daejeon Nationalwide Internet Competition 2014 E. Highway
 * BOJ 10254
 *
 * rotating calipers
 * Date: 2023.6.5
 */

#include<iostream>
#include<algorithm>
#include<vector>
#include<cmath>
using namespace std;
using i64 = int64_t;

struct vec2 {
    i64 x, y;
    bool operator<(const vec2& v) const {
        return y != v.y ? y < v.y : x < v.x;
    };
    vec2 operator-(const vec2& v) const {
        return { x - v.x, y - v.y };
    }
};
i64 cross(const vec2& v, const vec2& w) {
    return v.x*w.y - v.y*w.x;
}
i64 dot(const vec2& v, const vec2& w) {
    return v.x*w.x + v.y*w.y;
}
i64 ccw(const vec2& o, const vec2& p, const vec2& q) {
    return cross(p - o, q - o);
}

inline double dist(const vec2& p, const vec2& q) {
    return hypot(p.x - q.x, p.y - q.y);
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);

    int TC; cin >> TC;
    while (TC--) {
        int N; cin >> N;
        vector<vec2> points(N);
        for (auto& [x, y] : points) cin >> x >> y;

        swap(points[0], *min_element(points.begin(), points.end()));
        vec2& p0 = points[0];
        sort(++points.begin(), points.end(), [&p0] (const vec2& p1, const vec2& p2) {
            i64 k = ccw(p0, p1, p2);
            return k? k > 0 : dot(p2 - p1, p0 - p1) < 0;
        });

        int M = 0;
        vector<vec2> hull;
        for (const auto &p : points) {
            while (M > 1 && ccw(hull[M-2], hull[M-1], p) <= 0) {
                --M; hull.pop_back();
            }
            ++M; hull.push_back(p);
        }

        auto area = [&hull] (int i, int j, int k) -> i64 {
            return ccw(hull[i], hull[j], hull[k]);
        };

        double dmx = 0.;
        pair<int, int> ans;
        if (M > 3) {
            int j0 = 1;
            while (j0 < M && area(M-1, 0, j0) < area(M-1, 0, j0+1))
                ++j0;
            int i = 0, j = j0;
            while (i <= j0 && j < M) {
                double d = dist(hull[i], hull[j]);
                if (dmx < d) { dmx = d; ans = {i, j}; }
                while (j < M && area(i, i+1, j) < area(i, i+1, (j+1)%M)) {
                    ++j;
                    double d = dist(hull[i], hull[j < M? j : 0]);
                    if (dmx < d) { dmx = d; ans = {i, j < M? j : 0}; }
                }
                ++i;
            }
        }
        else {
            for (int i = 0; i < M; ++i) {
                int j = (i+1)%M;
                double d = dist(hull[i], hull[j]);
                if (dmx < d) { dmx = d; ans = {i, j}; }
            }
        }

        auto& [i, j] = ans;
        auto& [xi, yi] = hull[i]; cout << xi << ' ' << yi << ' ';
        auto& [xj, yj] = hull[j]; cout << xj << ' ' << yj << '\n';
    }

    return 0;
}
