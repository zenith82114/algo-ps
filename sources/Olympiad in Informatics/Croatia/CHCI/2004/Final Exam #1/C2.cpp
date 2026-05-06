/*
 * Croatian Highschool Competitions in Informatics, 2004, Final Exam #1 C. mapa
 * BOJ 3225 - geometry, DnC; Chebyshev distance
 * Date: 2025.4.13
 */

#include<bits/stdc++.h>
using namespace std;

struct point {
    int x, y;
    bool operator<(const point& q) const {
        return make_pair(x, y) < make_pair(q.x, q.y);
    }
} p[300004];

int dist(int i, int j) {
    const auto& [xi, yi] = p[i];
    const auto& [xj, yj] = p[j];
    return max(abs(xi - xj), abs(yi - yj));
}

int dnc(int l, int r) {
    if (r - l < 3) {
        int ans = INT32_MAX;
        for (int i = l; i < r; ++i)
        for (int j = i + 1; j <= r; ++j) {
            ans = min(ans, dist(i, j));
        }
        return ans;
    }

    int m = (l + r) / 2;
    int d = min(dnc(l, m), dnc(m + 1, r));

    vector<int> v;
    int t = p[m].x - d;
    for (int i = m; i >= l; --i) {
        if (p[i].x > t) v.emplace_back(i);
        else break;
    }
    t = p[m].x + d;
    for (int i = m + 1; i <= r; ++i) {
        if (p[i].x < t) v.emplace_back(i);
        else break;
    }
    sort(v.begin(), v.end(), [] (int i, int j) {
        return p[i].y < p[j].y;
    });

    int k = v.size();
    int ans = d;
    for (int i = 0; i < k; ++i) {
        for (int j = i + 1; j < k; ++j) {
            if (p[v[j]].y - p[v[i]].y >= d) break;
            ans = min(ans, dist(v[i], v[j]));
        }
    }
    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n; cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> p[i].x >> p[i].y;
        p[i].y *= 3;
    }
    sort(p, p + n);
    cout << (dnc(0, n - 1) / 3.);
    return 0;
}
