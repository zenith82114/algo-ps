/*
 * Polish Olympiad in Informatics, POI 2003/2004, Stage 1 A. Game
 * BOJ 1842 - Sprague-Grundy theorem; staircase Nim
 * Date: 2023.9.25
 */

#include<bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);

    int m, n; cin >> m >> n;
    vector<pair<int, int> > v; // <pile id, size>

    int pj = -1;
    int id = m - n + 1;
    while (n--) {
        int j; cin >> j;
        if (j == pj+1) {
            v.back().second++;
        } else {
            id -= (j - pj - 1);
            v.emplace_back(id, 1);
        }
        pj = j;
    }

    if (v.back().first == 0) { cout << 0; return 0; }
    if (v.back().first == 1) { cout << v.back().second; return 0; }

    int gn = 0;
    for (const auto& [i, x] : v) if (i&1) gn ^= x;
    if (!gn) { cout << 0; return 0; }

    int ans = 0;
    for (auto it = v.begin(); it != v.end(); ++it) {
        if (it->first == 2) break;
        const auto& [i, x] = *it;
        if (i&1) {
            if ((gn ^ x) <= x) ans++;
        } else {
            auto nit = next(it);
            int y = (nit != v.end() && nit->first == i-1)? nit->second : 0;
            if (y <= (gn ^ y) && (gn ^ y) <= x + y) ++ans;
        }
    }

    cout << ans;
    return 0;
}
