/*
 * North American Invitational Programming Contest, NAIPC 2017
 * E. Blazing New Trails
 * QOJ 6448
 *
 * Aliens trick, minimum spanning tree
 * Date: 2026.8.22
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;
using ii = pair<int, int>;
const int MAXN = 2e5+4;
const i64 INF = 1e18;

struct edge {
    int x, y, c;

    bool operator<(const edge& rhs) const { return c < rhs.c; }
};

struct disjoint_sets {
    int ar[MAXN];

    void init(int n) {
        memset(ar+1, -1, n * sizeof(int));
    }

    int find(int x) {
        if (ar[x] < 0) return x;
        return ar[x] = find(ar[x]);
    }

    bool unite(int x, int y) {
        x = find(x), y = find(y);
        if (x == y) return false;
        if (ar[x] < ar[y]) swap(x, y);
        ar[y] += ar[x];
        ar[x] = y;
        return true;
    }
} dsu;

int n;
bitset<MAXN> is_sp;
vector<edge> mixed, same;

pair<i64, int> mst(i64 lmd) {
    int cnt = 0, mixed_cnt = 0;
    i64 cost = 0;
    dsu.init(n);

    size_t i = 0, j = 0;
    while (i < mixed.size() || j != same.size()) {
        i64 c1 = (i < mixed.size() ? mixed[i].c + lmd : INF);
        i64 c2 = (j < same.size()  ? same[j].c        : INF);
        auto& e = (c1 <= c2 ? mixed[i++] : same[j++]);

        if (dsu.unite(e.x, e.y)) {
            ++cnt;
            if (c1 <= c2) { ++mixed_cnt; cost += e.c + lmd; }
            else cost += e.c;
        }
    }

    if (cnt < n-1) return { -1, -1 };
    return { cost, mixed_cnt };
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int m, k, w; cin >> n >> m >> k >> w;
    while (k--) { int x; cin >> x; is_sp.set(x); }
    while (m--) {
        int x, y, c; cin >> x >> y >> c;
        (is_sp[x] != is_sp[y] ? mixed : same).push_back({ x, y, c });
    }
    sort(begin(mixed), end(mixed));
    sort(begin(same), end(same));

    i64 B = (i64)1e5*(n-1) + 1;
    int rmax = mst(-B).second;
    if (rmax == -1) { cout << -1; return 0; }
    int rmin = mst(+B).second;

    if (w < rmin || rmax < w) { cout << -1; return 0; }

    i64 lo = -B, hi = +B;
    while (lo + 1 < hi) {
        i64 mid = (lo + hi)/2;
        (mst(mid).second >= w ? lo : hi) = mid;
    }

    cout << (mst(lo).first - w*lo);
    return 0;
}
