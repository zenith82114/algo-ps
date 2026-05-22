/*
 * UCPC 2018 Qualifier F. 트리와 색깔
 * JUNGOL 3602
 *
 * Euler tour, segment tree
 * Date: 2026.5.22
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;
const int MAXN = 2e5 + 4, MAXC = MAXN;
const int MOD = 1e9 + 7;

vector<int> ctox[MAXC];
vector<int> tree[MAXN];
vector<int> que[MAXC];
pair<int, int> et[MAXN];

class seg_tree {
    int N;
    int a[4*MAXN];
public:
    void init(int sz) {
        N = 1; while (N < sz) N *= 2;
        memset(a, 0, 2*N * sizeof(int));
    }
    void add(int i) {
        for (i |= N; i; i >>= 1) ++a[i];
    }
    int query(int i, int j) {
        int ret = 0;
        for (i |= N, j |= N; i <= j; i >>= 1, j >>= 1) {
            if ( i&1) ret += a[i++];
            if (~j&1) ret += a[j--];
        }
        return ret;
    }
} segt;

void dfs(int px, int x) {
    static int clk = 0;
    et[x].first = clk++;
    for (int y : tree[x]) if (y != px) dfs(x, y);
    et[x].second = clk - 1;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m, C; cin >> n >> m >> C;
    for (int x = 1; x <= n; ++x) {
        int c; cin >> c;
        ctox[c].push_back(x);
    }
    for (int i = 1; i < n; ++i) {
        int x, y; cin >> x >> y;
        tree[x].push_back(y);
        tree[y].push_back(x);
    }
    while (m--) {
        int x, c; cin >> x >> c;
        que[c].push_back(x);
    }

    dfs(0, 1);
    int ans = 0;
    segt.init(n + 1);
    for (int c = 1; c <= C; ++c) {
        for (int x : ctox[c]) segt.add(et[x].first);
        for (int x : que[c]) ans = (ans + segt.query(et[x].first, et[x].second)) % MOD;
    }
    cout << ans;
    return 0;
}
