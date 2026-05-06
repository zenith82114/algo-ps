/*
 * UCPC 2018 Qualifier F. 트리와 색깔
 * BOJ 15899
 *
 * Euler tour, merge sort tree
 * Date: 2025.6.26
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;

vector<int> g[200004];
int clr[200004];
pair<int, int> et[200004];
int clk = 0;
int mst[19][1<<18];

void dfs(int px, int x) {
    mst[0][clk] = clr[x];
    et[x].first = clk++;
    for (int y : g[x]) if (y != px) dfs(x, y);
    et[x].second = clk;
}

int qry(int i, int nl, int nr, int x, int c) {
    const auto& [xl, xr] = et[x];
    if (xr <= nl || nr <= xl) return 0;
    if (xl <= nl && nr <= xr) {
        return upper_bound(mst[i] + nl, mst[i] + nr, c) - (mst[i] + nl);
    }
    int nm = (nl + nr)/2;
    return qry(i - 1, nl, nm, x, c) + qry(i - 1, nm, nr, x, c);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m, _; cin >> n >> m >> _;
    for (int x = 1; x <= n; ++x) cin >> clr[x];
    for (int e = 1; e < n; ++e) {
        int x, y; cin >> x >> y;
        g[x].emplace_back(y);
        g[y].emplace_back(x);
    }
    memset(mst[0], 0x3f, sizeof mst[0]);
    dfs(0, 1);

    int lgn = 0; while ((1<<lgn) < n) ++lgn;
    n = 1<<lgn;
    for (int i = 0; i < lgn; ++i) {
        int blk = 1<<i;
        for (int j = 0; j < n; j += 2*blk) {
            int p = j, q1 = j, q2 = j + blk;
            while (q1 < j + blk && q2 < j + 2*blk) {
                mst[i + 1][p++] = mst[i][(mst[i][q1] < mst[i][q2]? q1 : q2)++];
            }
            while (q1 < j +   blk) mst[i + 1][p++] = mst[i][q1++];
            while (q2 < j + 2*blk) mst[i + 1][p++] = mst[i][q2++];
        }
    }

    i64 ans = 0;
    while (m--) {
        int x, c; cin >> x >> c;
        ans += qry(lgn, 0, n, x, c);
    }
    cout << (ans % 1'000'000'007);
    return 0;
}
