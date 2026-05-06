/*
 * JOI Open Contest, JOI Open Contest 2014 Day 1 A. Factories
 * BOJ 11933
 * JUNGOL 3507
 *
 * tree compression, DP
 * Date: 2023.9.16
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;
constexpr int MAXN = 5e5;
constexpr i64 inf = INT64_MAX/2;

vector<pair<int, int> > gph[MAXN] {};
int rmq[20][2*MAXN] {};
i64 d[MAXN] {};
int st[MAXN] {}, fn[MAXN] {};

void dfs(int px, int x, int& clk) {
    st[x] = clk;
    rmq[0][clk++] = x;
    for (const auto& [y, w] : gph[x]) if (y != px) {
        d[y] = d[x] + w;
        dfs(x, y, clk);
        rmq[0][clk++] = x;
    }
    fn[x] = clk-1;
}

int lca(int x, int y) {
    int l = st[x], r = st[y]; if (l > r) swap(l, r);
    int n = r - l + 1;
    int i = 19; while (~n & (1<<i)) --i;
    int x1 = rmq[i][l], x2 = rmq[i][r - (1<<i) + 1];
    return d[x1] < d[x2]? x1 : x2;
}

vector<int> v;
int clr[MAXN] {};
pair<i64, i64> mem[MAXN] {};

void dp(int x, int& idx) {
    auto& [ax, bx] = mem[x];
    ax = clr[x] == 1? 0 : inf;
    bx = clr[x] == 2? 0 : inf;
    while (idx < (int)v.size() && fn[v[idx]] <= fn[x]) {
        int y = v[idx++]; dp(y, idx);
        auto [ay, by] = mem[y];
        ax = min(ax, ay + d[y] - d[x]);
        bx = min(bx, by + d[y] - d[x]);
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);

    int N, Q; cin >> N >> Q;

    for (int i = 1; i < N; ++i) {
        int x, y, w; cin >> x >> y >> w;
        gph[x].emplace_back(y, w);
        gph[y].emplace_back(x, w);
    }
    int clk = 0; dfs(-1, 0, clk);

    for (int i = 1; i < 20; ++i)
    for (int j = 0; j + (1<<i>>1) < 2*N; ++j) {
        int x1 = rmq[i-1][j], x2 = rmq[i-1][j + (1<<i>>1)];
        rmq[i][j] = d[x1] < d[x2]? x1 : x2;
    }

    while (Q--) {
        for (int x : v) clr[x] = 0;
        v.clear();
        int S, T; cin >> S >> T;
        for (int i = 0; i < S; ++i) {
            int x; cin >> x;
            v.emplace_back(x); clr[x] = 1;
        }
        for (int i = 0; i < T; ++i) {
            int x; cin >> x;
            v.emplace_back(x); clr[x] = 2;
        }
        auto cmp = [] (const int& x, const int& y) { return st[x] < st[y]; };
        sort(v.begin(), v.end(), cmp);
        for (int i = 0; i+1 < S+T; ++i) v.emplace_back(lca(v[i], v[i+1]));
        sort(v.begin(), v.end(), cmp);
        v.erase(unique(v.begin(), v.end()), v.end());

        int idx = 0; dp(v[0], idx);
        i64 ans = inf;
        for (int x : v) {
            const auto& [a, b] = mem[x];
            ans = min(ans, a + b);
        }
        cout << ans << '\n';
    }

    return 0;
}
