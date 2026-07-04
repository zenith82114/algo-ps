/*
 * 트리와 쿼리 8
 * QOJ 18811
 *
 * LCA (sparse table), parallel binary search, Euler tour, segment tree
 * Date: 2026.3.13
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;
using ii = pair<int, int>;
constexpr int
    MAXN = 1e5 +4,
    MAXLGN = 17,
    MAXM = 1e5 +4;

int tag[MAXN];
vector<int> tree[MAXN];
struct query { int x, y, k, w; } que[MAXM];
ii ans[MAXM];

int spt[MAXLGN][MAXN];
ii et[MAXN];
int dep[MAXN] {};

vector<int> bucket[MAXN];

struct seg_tree {
    vector<int> ar;
    int n;

    void init(int sz) {
        n = 1; while (n < sz) n *= 2;
        ar.resize(2*n);
    }
    void reset() {
        fill(ar.begin(), ar.end(), 0);
    }
    void add(int i, int j) {
        for (i |= n, j |= n; i <= j; i >>= 1, j >>= 1) {
            if ( i&1) ++ar[i++];
            if (~j&1) ++ar[j--];
        }
    }
    int query(int i) {
        int ans = 0;
        for (i |= n; i; i >>= 1) ans += ar[i];
        return ans;
    }
} segt;

void dfs(int px, int x) {
    static int clk = 0;
    spt[0][x] = px;
    et[x].first = clk++;
    dep[x] = dep[px] + 1;
    for (int y : tree[x]) if (y != px) dfs(x, y);
    et[x].second = clk-1;
}

int lca(int x, int y) {
    if (dep[x] < dep[y]) swap(x, y);
    for (int t = dep[x] - dep[y], i = 0; t; t >>= 1, ++i) {
        if (t&1) x = spt[i][x];
    }
    if (x == y) return x;
    for (int i = MAXLGN-1; i >= 0; --i) if (spt[i][x] != spt[i][y]) {
        x = spt[i][x], y = spt[i][y];
    }
    return spt[0][x];
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n; cin >> n;
    for (int x = 1; x <= n; ++x) cin >> tag[x];
    for (int i = 1; i < n; ++i) {
        int x, y; cin >> x >> y;
        tree[x].push_back(y);
        tree[y].push_back(x);
    }
    int m; cin >> m;
    for (int i = 0; i < m; ++i) {
        auto& q = que[i];
        cin >> q.x >> q.y >> q.k;
        ans[i] = (q.x == q.y ? ii(-1, -1) : ii(0, n));
    }

    dfs(0, 1);

    for (int i = 1; i < MAXLGN; ++i)
    for (int x = 1; x <= n; ++x) {
        spt[i][x] = spt[i-1][spt[i-1][x]];
    }
    for (int i = 0; i < m; ++i) {
        auto& q = que[i];
        q.w = lca(q.x, q.y);
    }

    vector<int> tag_asc(n+1);
    iota(tag_asc.begin(), tag_asc.end(), 0);
    sort(tag_asc.begin()+1, tag_asc.end(),
        [] (int x, int y) { return tag[x] < tag[y]; });

    segt.init(n);

    for (int phase = 1; phase < n; phase *= 2) {
        for (int j = 1; j <= n; ++j) bucket[j].clear();

        bool early_exit = true;
        for (int i = 0; i < m; ++i) {
            auto [lo, hi] = ans[i];
            if (lo + 1 < hi) {
                bucket[(lo + hi)/2].push_back(i);
                early_exit = false;
            }
        }
        if (early_exit) break;

        segt.reset();

        for (int j = 1; j <= n; ++j) {
            int x = tag_asc[j];
            segt.add(et[x].first, et[x].second);

            for (int i : bucket[j]) {
                auto q = que[i];
                int cnt = segt.query(et[q.x].first)
                        + segt.query(et[q.y].first)
                        - segt.query(et[q.w].first)
                        - (q.w != 1 ? segt.query(et[spt[0][q.w]].first) : 0);
                (cnt < q.k ? ans[i].first : ans[i].second) = j;
            }
        }
    }

    for (int i = 0; i < m; ++i) {
        auto q = que[i];
        cout << (q.x == q.y ? tag[q.x] : tag[tag_asc[ans[i].second]]) << '\n';
    }

    return 0;
}
