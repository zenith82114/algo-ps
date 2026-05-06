/*
 * ICPC, Regionals, Asia Pacific, Japan,
 * Asia Regional Contest 2016 in Tsukuba K. Black and White Boxes
 * BOJ 13409 - Hackenbush, meet in the middle
 * Date: 2024.1.17
 */

#include<bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    using pli = pair<int64_t, int>;

    int n; cin >> n;
    vector<pli> v(n);
    for (auto& [x, y] : v) {
        string s; cin >> s;
        y = s.size();
        int64_t d = 1LL<<40;
        int i = 0;
        for (; i < y && s[i] == s[0]; ++i) x += d;
        for (; i < y; ++i) {
            d >>= 1;
            x += s[i] == s[0]? d : -d;
        }
        if (s[0] == 'W') x = -x;
    }

    auto subsums = [] (const vector<pli>& v) {
        vector<pli> ss; ss.reserve(1<<v.size());
        ss.emplace_back(0, 0);
        int m = 1;
        for (const auto& [x, y] : v) {
            for (int i = 0; i < m; ++i) {
                ss.emplace_back(ss[i].first + x, ss[i].second + y);
            }
            m <<= 1;
        }
        return ss;
    };

    vector<pli> v1(v.begin(), v.begin() + (n>>1));
    auto ss1 = subsums(v1);
    vector<pli> v2(v.begin() + (n>>1), v.end());
    auto ss2 = subsums(v2); sort(ss2.begin(), ss2.end());

    int ans = 0;
    for (const auto& [x, y] : ss1) {
        auto p = lower_bound(ss2.begin(), ss2.end(), make_pair(-x, 1000));
        if (p == ss2.begin()) continue;
        p = prev(p);
        if (p->first == -x) ans = max(ans, y + p->second);
    }
    cout << ans;
    return 0;
}
