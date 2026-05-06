/*
 * 한국정보올림피아드, KOI 2018, 중등부 4. 공룡 발자국
 * BOJ 15974
 * JUNGOL 3233
 *
 * DP, two pointers
 * Date: 2025.1.23
 */

#include<bits/stdc++.h>
using namespace std;

struct vec2 {
    int x, y;
    vec2 operator-(const vec2& v) const {
        return { x - v.x, y - v.y };
    }
};
int64_t cross(const vec2& v, const vec2& w) {
    return 1ll*v.x*w.y - 1ll*v.y*w.x;
}
int ccw(const vec2& o, const vec2& p, const vec2& q) {
    auto k = cross(p - o, q - o);
    return (k < 0) ? -1 : (k ? 1 : 0);
}

vec2 p[3000];
int dp[3000][3000][2] {}, opt[3000][3000][2];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n; cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> p[i].x >> p[i].y;
        if (p[0].y > p[i].y) swap(p[0], p[i]);
        dp[0][i][1] = (int)-1e9;
    }
    sort(p + 1, p + n, [] (const vec2& v, const vec2& w) {
        return ccw(p[0], v, w) > 0;
    });

    for (int i = 1; i + 1 < n; ++i) {
        vector<int> vh { 0 }, vj;
        for (int h = 1; h < i; ++h) {
            if (ccw(p[0], p[h], p[i])) vh.emplace_back(h);
        }
        sort(vh.begin(), vh.end(), [i] (const int& h1, const int& h2) {
            return ccw(p[i], p[h1], p[h2]) > 0;
        });
        for (int j = i + 1; j < n; ++j) {
            if (ccw(p[0], p[i], p[j])) vj.emplace_back(j);
        }
        sort(vj.begin(), vj.end(), [i] (const int& j1, const int& j2) {
            return ccw(p[i], p[j1], p[j2]) > 0;
        });

        auto it = vh.begin();
        int h_opt = 0;
        for (int j : vj) {
            while (it != vh.end() && ccw(p[*it], p[i], p[j]) > 0) {
                int h = *(it++);
                if (dp[h_opt][i][0] < dp[h][i][0]) h_opt = h;
            }
            dp[i][j][1] = dp[h_opt][i][0] + 1;
            opt[i][j][1] = h_opt;
        }

        reverse(vh.begin(), vh.end());
        reverse(vj.begin(), vj.end());
        it = vh.begin();
        h_opt = 0;
        for (int j : vj) {
            while (it != vh.end() && ccw(p[*it], p[i], p[j]) < 0) {
                int h = *(it++);
                if (dp[h_opt][i][1] < dp[h][i][1]) h_opt = h;
            }
            dp[i][j][0] = dp[h_opt][i][1] + 1;
            opt[i][j][0] = h_opt;
        }
    }

    int s = 0, t = 0;
    for (int i = 0; i < n; ++i)
    for (int j = i + 1; j < n; ++j) {
        if (dp[s][t][0] < dp[i][j][0]) s = i, t = j;
    }

    vector<int> ans { t, s };
    int u = 0;
    while (s) {
        t = opt[s][t][u];
        swap(s, t);
        ans.emplace_back(s);
        u ^= 1;
    }
    if (ans.size() < 4u) cout << "0\n";
    else {
        cout << ans.size() << '\n';
        reverse(ans.begin(), ans.end());
        for (int i : ans) cout << p[i].x << ' ' << p[i].y << '\n';
    }

    return 0;
}
