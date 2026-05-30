/*
 * ICPC, Regionals, Europe, Central Europe Regional Contest,
 * CERC 2017 J. Justified Jungle
 * JUNGOL 11584
 *
 * ad-hoc
 * Date: 2026.5.30
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;
const int MAXN = 1e6 + 4;

vector<int> tree[MAXN];
int sz[MAXN];

void get_sz(int px, int x) {
    sz[x] = 1;
    for (int y : tree[x]) if (y != px) {
        get_sz(x, y);
        sz[x] += sz[y];
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n; cin >> n;
    for (int i = 1; i < n; ++i) {
        int x, y; cin >> x >> y;
        tree[x].push_back(y);
        tree[y].push_back(x);
    }

    get_sz(0, 1);

    for (int c = n/2; c > 0; --c) if (n % c == 0) {
        int k = n/c - 1;
        int cnt = 0;
        for (int x = 2; x <= n; ++x) cnt += (sz[x] % c == 0);
        if (k == cnt) cout << k << ' ';
    }
    return 0;
}
