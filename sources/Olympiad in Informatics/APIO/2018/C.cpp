/*
 * Asia-Pacific Informatics Olympiad, APIO 2018
 * C. Duathlon
 * QOJ 192
 *
 * block-cut tree
 * Date: 2026.8.9
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;
using ii = pair<int, int>;
const int MAXN = 1e5+4, MAXM = 2e5+4;

int n, m;
vector<int> gph[MAXN], bct[MAXN+MAXM];
array<int, MAXN+MAXM> par, cnt;
array<int, MAXN> dfn, low;
stack<int> stc;
int tot;

void tarjan(int px, int x) {
    static int clk = 0;

    dfn[x] = low[x] = ++clk;
    stc.push(x);

    for (int y : gph[x]) if (y != px) {
        if (dfn[y]) {
            low[x] = min(low[x], dfn[y]);
        } else {
            tarjan(x, y);
            low[x] = min(low[x], low[y]);

            if (dfn[x] <= low[y]) {
                int b = ++tot;
                bct[b].push_back(x);
                bct[x].push_back(b);

                while (true) {
                    int u = stc.top(); stc.pop();
                    bct[b].push_back(u);
                    bct[u].push_back(b);
                    if (u == y) break;
                }
            }
        }
    }
}

void dfs(int px, int x, vector<int>& bs) {
    par[x] = px;
    cnt[x] = (int)(x <= n);
    if (x > n) bs.push_back(x);

    for (int y : bct[x]) if (y != px) {
        dfs(x, y, bs);
        cnt[x] += cnt[y];
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m;
    while (m--) {
        int x, y; cin >> x >> y;
        gph[x].push_back(y);
        gph[y].push_back(x);
    }

    dfn.fill(0);
    tot = n;
    for (int x = 1; x <= n; ++x) if (!dfn[x]) {
        tarjan(0, x);
        stc.pop();
    }

    i64 ans = 0;
    par.fill(0);
    for (int root = 1; root <= n; ++root) if (!par[root]) {
        vector<int> bs;
        dfs(-1, root, bs);

        i64 k = cnt[root];
        ans -= k*(k-1);

        for (int b : bs) {
            i64 pairs = k*k;
            for (int x : bct[b]) {
                i64 a = (par[x] == b ? cnt[x] : k - cnt[b]);
                pairs -= a*a;
            }
            ans += (bct[b].size()-1) * pairs;
        }
    }

    cout << ans;
    return 0;
}
