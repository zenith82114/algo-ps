/*
 * 한국정보올림피아드, KOI 2010, 고등부 3. 교차 선분
 * BOJ 2474
 * JUNGOL 2305
 *
 * greedy
 * Date: 2025.10.11
 *
 * cf. bipartite permutation graph and strong ordering
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;

struct segment {
    int x = 0, y = 0;
    bool operator<(const segment& other) const { return x < other.x; }
    bool intersects(const segment& other) const {
        return ((x - other.x) ^ (y - other.y)) < 0;
    }
};
using segments = segment[100'000];

segments s, a, b;
int na = 0, nb = 0;
int vi = -1, vj = -1;

int dfs_b(int, int);

int dfs_a(int i, int j) {
    if (i == na) return 0;
    vi = max(vi, i);
    if (j == nb || !a[i].intersects(b[j])) return 1;
    for (; j < nb && a[i].intersects(b[j]); ++j) {
        if (i + 1 < na && a[i + 1].intersects(b[j])) return 1 + dfs_b(i + 1, j);
    }
    return 2;
}

int dfs_b(int i, int j) {
    if (j == nb) return 0;
    vj = max(vj, j);
    if (i == na || !b[j].intersects(a[i])) return 1;
    for (; i < na && b[j].intersects(a[i]); ++i) {
        if (j + 1 < nb && b[j + 1].intersects(a[i])) return 1 + dfs_a(i, j + 1);
    }
    return 2;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n; cin >> n;
    for (int i = 0; i < n; ++i) cin >> s[i].x >> s[i].y;
    sort(s, s + n);
    for (int i = 0; i < n; ++i) {
        if (!na || a[na - 1].y < s[i].y) a[na++] = s[i];
        else b[nb++] = s[i];
    }

    for (int i = 0; i + 1 < na; ++i) assert(!a[i].intersects(a[i + 1]));
    for (int j = 0; j + 1 < nb; ++j) assert(!b[j].intersects(b[j + 1]));

    int ans = 1;
    for (int i = 0, j = 0; i < na && j < nb; ) {
        if (!a[i].intersects(b[j])) (a[i].x < b[j].x? i : j)++;
        else {
            ans = max(ans, 1 + max(dfs_a(i, j + 1), dfs_b(i + 1, j)));
            i = vi + 1; j = vj + 1;
        }
    }
    cout << ans;
    return 0;
}
