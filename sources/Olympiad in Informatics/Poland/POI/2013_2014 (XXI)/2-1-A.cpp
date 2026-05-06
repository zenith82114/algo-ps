/*
 * Polish Olympiad in Informatics, POI 2013/2014, Stage 2 Day 1 A. Criminals
 * BOJ 10127 - greedy, difference array
 * Date: 2025.3.19
 */

#include<bits/stdc++.h>
using namespace std;

int n, k, mx, my;
array<int, 1000004> c, cx, cy, px, py, vsz, l, r, imos;
vector<int> v[1000004];

bool fix_x(int q) {
    v[0][0] = q;
    for (int j = 1; j < mx; ++j) {
        if (px[j] < vsz[cx[j]] && v[cx[j]][px[j]] > v[cx[j - 1]][px[j - 1]] && q != 1)
            return true;
        while (px[j] < vsz[cx[j]] && v[cx[j]][px[j]] <= v[cx[j - 1]][px[j - 1]])
            ++px[j];
        if (px[j] == vsz[cx[j]]) return false;
    }
    return true;
}

bool fix_y(int q) {
    v[0][0] = q;
    for (int j = 1; j < my; ++j) {
        if (py[j] >= 0 && v[cy[j]][py[j]] < v[cy[j - 1]][py[j - 1]] && q != n)
            return true;
        while (py[j] >= 0 && v[cy[j]][py[j]] >= v[cy[j - 1]][py[j - 1]])
            --py[j];
        if (py[j] < 0) return false;
    }
    return true;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> k;
    for (int i = 1; i <= n; ++i) {
        cin >> c[i];
        v[c[i]].emplace_back(i);
    }
    for (int kk = 1; kk <= k; ++kk) vsz[kk] = v[kk].size();
    cin >> mx >> my;
    cx[0] = px[0] = 0;
    cy[0] = py[0] = 0;
    v[0].emplace_back();
    for (int j = 1; j <= mx; ++j) cin >> cx[j], px[j] = 0;
    for (int j = 1; j <= my; ++j) cin >> cy[j], py[j] = vsz[cy[j]] - 1;

    for (int kk = 1; kk <= k; ++kk) l[kk] = n + 2, r[kk] = -1;

    if (fix_x(1)) {
        l[c[1]] = (mx > 1? v[cx[mx - 1]][px[mx - 1]] : 1) + 1;
        for (int q = 2; q <= n; ++q) {
            if (l[c[q]] <= n + 1) continue;
            if (fix_x(q)) l[c[q]] = (mx > 1? v[cx[mx - 1]][px[mx - 1]] : q) + 1;
            else break;
        }
    }
    if (fix_y(n)) {
        r[c[n]] = (my > 1? v[cy[my - 1]][py[my - 1]] : n) - 1;
        for (int q = n - 1; q > 0; --q) {
            if (r[c[q]] >= 0) continue;
            if (fix_y(q)) r[c[q]] = (my > 1? v[cy[my - 1]][py[my - 1]] : q) - 1;
            else break;
        }
    }

    for (int i = 1; i <= n; ++i) imos[i] = 0;
    for (int kk = 1; kk <= k; ++kk) if (l[kk] <= r[kk]) {
        ++imos[l[kk]]; --imos[r[kk] + 1];
    }
    for (int i = 2; i <= n; ++i) imos[i] += imos[i - 1];

    vector<int> ans;
    for (int i = 1; i <= n; ++i) if (c[i] == cx[mx] && imos[i]) ans.emplace_back(i);

    cout << ans.size() << '\n';
    for (int i : ans) cout << i << ' ';
    return 0;
}
