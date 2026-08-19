/*
 * USA Computing Olympiad, USACO 2026 First Contest, Platinum
 * 1. Hoof, Paper, Scissors Triples
 * QOJ 16292
 *
 * geometry, two pointers
 * Date: 2026.8.19
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;
using ii = pair<int, int>;

struct vec2 {
    int x, y;

    vec2(int x, int y): x(x), y(y) {}

    bool _lt180() const {
        return y > 0 || (y == 0 && x > 0);
    }

    i64 cross(const vec2& rhs) const {
        return (i64)x*rhs.y - (i64)y*rhs.x;
    }

    bool operator<(const vec2& rhs) const {
        bool b1 = _lt180(), b2 = rhs._lt180();
        return (b1 != b2 ? b1 : cross(rhs) > 0);
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int tc; cin >> tc;
    while (tc--) {
        vector<vec2> vs;
        int n; cin >> n;
        while (n--) {
            int h, p, s; cin >> h >> p >> s;
            int x = h - s, y = p - s;
            if (x || y) vs.emplace_back(x, y);
        }
        sort(begin(vs), end(vs));

        vector<vec2> uvs;
        vector<int> cnt;
        for (const auto& v : vs) {
            if (uvs.empty()) {
                uvs.push_back(v), cnt.push_back(1);
                continue;
            }

            vec2& w = uvs.back();
            if (!(v < w) && !(w < v)) ++cnt.back();
            else uvs.push_back(v), cnt.push_back(1);
        }

        auto ch2 = [](int n) { return (i64)n*(n-1)/2; };
        auto ch3 = [](int n) { return (i64)n*(n-1)*(n-2)/6; };

        const int m = uvs.size();
        i64 sum = 0;
        i64 ans = ch3(vs.size());

        for (int r = 0, l = 0; l < m; ++l) {
            if (sum > 0) sum -= cnt[l];
            else r = l;

            while (uvs[l].cross(uvs[(r+1)%m]) > 0) {
                sum += cnt[r = (r+1)%m];
            }
            ans -= ch3(cnt[l] + sum) - ch3(sum);

            if (l != (r+1)%m && uvs[l].cross(uvs[(r+1)%m]) == 0) {
                ans -= ch2(cnt[l]) * cnt[(r+1)%m];
                ans -= cnt[l] * sum * cnt[(r+1)%m];
            }
        }

        cout << ans << '\n';
    }

    return 0;
}
