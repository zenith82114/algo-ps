/*
 * Waterloo's local Programming Contests, 26 January, 2002 E. A Star not a Tree?
 * BOJ 4360 - geometric median; gradient descent
 * Date: 2023.1.19
 */

#include<bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    struct vec2 {
        double x, y;
        vec2() = default;
        vec2(double x, double y): x(x), y(y) {}

        vec2& operator+=(const vec2& v) {
            x += v.x;
            y += v.y;
            return *this;
        }
        vec2 operator-(const vec2& v) const {
            return vec2(x - v.x, y - v.y);
        }
        vec2& operator-=(const vec2& v) {
            x -= v.x;
            y -= v.y;
            return *this;
        }
        vec2 operator*(const double c) const {
            return vec2(c * x, c * y);
        }
        double norm() const { return hypot(x, y); }
        vec2 normalized() const {
            double norm = this->norm();
            return vec2(x / norm, y / norm);
        }
    };

    int N; cin >> N;
    vector<vec2> pts(N);
    for (auto& [x, y] : pts) cin >> x >> y;

    constexpr double eps = 1e-9;
    vec2 q(5000.0, 5000.0);

    for (int i = 0; i < 2000; ++i) {
        vec2 grad(0.0, 0.0);
        for (const auto& p : pts) {
            vec2 pq = q - p;
            if (pq.norm() > eps)
                grad += pq.normalized();
        }
        if (grad.norm() < eps) break;
        grad = grad.normalized();
        double step = i < 1000? 10.0 : 0.01;
        q -= grad * step;
    }

    double ans = 0.0;
    for (const auto& p : pts) ans += (q - p).norm();
    cout << lrint(ans);
    return 0;
}
