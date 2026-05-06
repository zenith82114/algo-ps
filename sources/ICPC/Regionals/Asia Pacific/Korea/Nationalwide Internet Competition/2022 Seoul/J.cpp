/*
 * ICPC, Regionals, Asia Pacific, Korea,
 * Seoul Nationalwide Internet Competition 2022 J. Rectangles
 * BOJ 25952
 * JUNGOL 11036
 *
 * sqrt decomposition
 * Date: 2025.8.11
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;

vector<int> yval[100'004], xl, xh;
bitset<100'004> mark;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n; cin >> n;
    const int k = round(sqrt(4. / 3. * n / log(n + 1)) + .5);
    while (n--) {
        int x, y; cin >> x >> y;
        yval[x].emplace_back(y);
    }
    for (int x = 0; x <= 100'000; ++x) {
        auto& Y = yval[x];
        if (Y.size() < 2) continue;
        sort(begin(Y), end(Y));
        ((int)Y.size() < k? xl : xh).emplace_back(x);
    }
    i64 ans = 0;

    map<pair<int, int>, int> mp;
    for (int x : xl) {
        const auto& Y = yval[x];
        for (size_t i = 0; i < Y.size(); ++i)
        for (size_t j = i + 1; j < Y.size(); ++j) {
            ans += mp[make_pair(Y[i], Y[j])]++;
        }
    }

    for (int x1 : xh) {
        for (int y : yval[x1]) mark.set(y);
        for (int x2 : xl) {
            i64 cnt = 0;
            for (int y : yval[x2]) cnt += mark[y];
            ans += cnt * (cnt - 1) / 2;
        }
        for (int y : yval[x1]) mark.reset(y);
    }

    for (size_t i = 0; i < xh.size(); ++i)
    for (size_t j = i + 1; j < xh.size(); ++j) {
        const auto& Y1 = yval[xh[i]], Y2 = yval[xh[j]];
        i64 cnt = 0;
        size_t p1 = 0, p2 = 0;
        while (p1 < Y1.size() && p2 < Y2.size()) {
            cnt += Y1[p1] == Y2[p2];
            ++(Y1[p1] < Y2[p2]? p1 : p2);
        }
        ans += cnt * (cnt - 1) / 2;
    }

    cout << ans;
    return 0;
}
