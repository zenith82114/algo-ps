/*
 * Croatian Open Competition in Informatics, COCI 2007/2008, Contest #2 F. PRAVOKUTNI
 * BOJ 3008
 *
 * two pointers
 * Date: 2025.2.19
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;

struct vec2 {
    int x, y, q;
    vec2() = default;
    vec2(int x, int y): x(x), y(y), q(0) {}
};

i64 cross(const vec2& u, const vec2& v) {
    return (i64)u.x * v.y - (i64)u.y * v.x;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n; cin >> n;
    vector<vec2> a(n);
    for (auto& [x, y, q] : a) cin >> x >> y;
    i64 cnt[4];
    i64 ans = 0;

    for (int i = 0; i < n; ++i) {
        vector<vec2> b;
        for (int j = 0; j < n; ++j) if (i != j) {
            b.emplace_back(a[j].x - a[i].x, a[j].y - a[i].y);
        }
        for (auto& [x, y, q] : b) {
            while (x < 0 || y <= 0) { swap(x, y); y = -y; ++q; }
        }
        sort(b.begin(), b.end(), [] (const vec2& u, const vec2& v) {
            return cross(u, v) > 0;
        });
        for (int l = 0, r = 0; l < n - 1; l = r) {
            memset(cnt, 0, sizeof cnt);
            while (r < n - 1 && cross(b[l], b[r]) == 0) ++cnt[b[r++].q];
            for (int k = 0; k < 4; ++k) ans += cnt[k] * cnt[(k + 1) & 3];
        }
    }

    cout << ans;
    return 0;
}
