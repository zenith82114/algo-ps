/*
 * USA Computing Olympiad, USACO 2016 December Contest, Platinum 1. Lots of Triangles
 * BOJ 14164
 * JUNGOL 3986
 *
 * geometry
 * Date: 2023.1.28
 */

#include<bits/stdc++.h>
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
inline i64 cross(const vec2& v, const vec2& w) {
    return v.x * w.y - v.y * w.x;
}
inline bool ccw(const vec2& o, const vec2& p, const vec2& q) {
    return cross(p - o, q - o) > 0;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int N; cin >> N;
    vector<vec2> P(N);
    for (auto& p : P) cin >> p.x >> p.y;

    auto f = min_element(P.begin(), P.end(), [] (const vec2& p, const vec2& q) {
        return p.x != q.x? p.x < q.x : p.y < q.y;
    });
    swap(*f, P[0]);
    const vec2& ori = P[0];
    sort(P.begin() +1, P.end(), [&ori] (const vec2& p, const vec2& q) {
        return ccw(ori, p, q);
    });

    vector<vector<int>> cnt(N, vector<int>(N));
    for (int i = 1; i < N; ++i)
    for (int j = i+1; j < N; ++j) {
        for (int k = 0; k < N; ++k) {
            if (ccw(ori, P[i], P[k]) && ccw(P[i], P[j], P[k]) && ccw(P[j], ori, P[k]))
                cnt[i][j]++;
        }
    }

    vector<int> ans(N-2);
    for (int i = 0;   i < N; ++i)
    for (int j = i+1; j < N; ++j)
    for (int k = j+1; k < N; ++k) {
        if (ccw(P[i], P[j], P[k]))
            ans[cnt[i][j] + cnt[j][k] - cnt[i][k]]++;
        else
            ans[cnt[i][k] - cnt[i][j] - cnt[j][k] - 1]++;
    }

    for (int& a : ans) cout << a << '\n';
    return 0;
}
