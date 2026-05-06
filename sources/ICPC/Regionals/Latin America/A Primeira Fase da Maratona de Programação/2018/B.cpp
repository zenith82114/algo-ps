/*
 * ICPC, Regionals, Latin America, Sub-Regional Brasil do ACM ICPC,
 * A Primeira Fase da Maratona de Programação 2018 B. Bolinhas de Gude
 * BOJ 16443 - Sprague-Grundy theorem
 * Date: 2023.7.27
 */

#include<bits/stdc++.h>
using namespace std;

int memo[101][101];

int grundy(int x, int y) {
    int& ret = memo[x][y];
    if (ret != -1) return ret;
    set<int> s;
    for (int k = 0; k < x; ++k) s.emplace(grundy(k, y));
    for (int k = 0; k < y; ++k) s.emplace(grundy(x, k));
    for (int k = 1; k < min(x, y); ++k) s.emplace(grundy(x-k, y-k));
    ret = 0;
    while (s.find(ret) != s.end()) ++ret;
    return ret;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    using ii = pair<int, int>;

    for (int x = 0; x <= 100; ++x)
    for (int y = 0; y <= 100; ++y)
        memo[x][y] = (!x || !y || x == y)? -2 : -1;

    int N; cin >> N;
    vector<ii> v(N);
    for (auto& [x, y] : v) cin >> x >> y;
    if (any_of(v.begin(), v.end(), [] (const ii& a) {
        const auto& [x, y] = a; return !x || !y || x == y;
    })) {
        cout << 'Y';
    } else {
        int g = 0;
        for (auto& [x, y] : v) g ^= grundy(x, y);
        cout << (g? 'Y' : 'N');
    }

    return 0;
}
