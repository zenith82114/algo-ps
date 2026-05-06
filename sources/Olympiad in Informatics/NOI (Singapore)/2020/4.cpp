/*
 * National Olympiad in Informatics (Singapore), NOI 2020 4. Arcade
 * BOJ 19661 - LIS
 * Date: 2023.2.17
 */

#include<bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    struct point { int x, y; point(int x, int y): x(x), y(y) {} };
    vector<point> pts;

    int N, M; cin >> N >> M;
    vector<int> T(M);
    for (int& t : T) cin >> t;
    for (const int& t : T) {
        int a; cin >> a;
        pts.emplace_back(a + t, t - a);
    }

    sort(pts.begin(), pts.end(), [] (const point& p1, const point& p2) {
        return p1.y != p2.y? p1.y > p2.y : p1.x > p2.x;
    });

    vector<int> last;
    for (const auto& [x, y] : pts) {
        auto p = lower_bound(last.begin(), last.end(), x);
        if (p != last.end()) *p = x;
        else last.emplace_back(x);
    }

    cout << last.size();
    return 0;
}
