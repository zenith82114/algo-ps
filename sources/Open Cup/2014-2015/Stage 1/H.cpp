/*
 * Open Cup 2014/2015 Stage 1: Grand Prix of SPb
 * H. Removing Vertices
 * QOJ 18508
 *
 * tree DP
 * Date: 2026.6.26
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;
using ii = pair<int, int>;
const int MAXN = 1e5 +4, INF = 1e9;

vector<int> gph[MAXN];
bitset<MAXN> marked, seen;
int dp[MAXN][3] {};
int y_pick[MAXN];
vector<int> ans;

void dfs(int px, int x) {
    seen.set(x);

    int a = 0;
    ii b(INF, -1);
    dp[x][2] = 1;

    for (int y : gph[x]) if (y != px) {
        dfs(x, y);
        int c = min(dp[y][0], dp[y][2]);
        a += c;
        b = min(b, ii(dp[y][1] - c, y));
        dp[x][2] += *min_element(dp[y], dp[y] + 3);
    }

    if (marked[x]) {
        dp[x][0] = INF;
        dp[x][1] = a;
    } else {
        dp[x][0] = a;
        dp[x][1] = a + b.first;
        y_pick[x] = b.second;
    }
}

void dfs_trace(int px, int x, int opt) {
    if (opt == 2) ans.push_back(x);

    for (int y : gph[x]) if (y != px) {
        int opt_y = (dp[y][0] < dp[y][2]) ? 0 : 2;

        if (opt == 1 && !marked[x] && y == y_pick[x]) {
            opt_y = 1;
        }
        else if (opt == 2) {
            opt_y = min_element(dp[y], dp[y] + 3) - dp[y];
        }

        dfs_trace(x, y, opt_y);
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m; cin >> n >> m;
    while (m--) {
        int x, y; cin >> x >> y;
        if (x > y) swap(x, y);
        if (!x) marked.set(y);
        else gph[x].push_back(y), gph[y].push_back(x);
    }

    for (int x = 1; x <= n; ++x) if (!seen[x]) {
        dfs(0, x);
        int opt = min_element(dp[x], dp[x] + 3) - dp[x];
        dfs_trace(0, x, opt);
    }

    cout << ans.size() << '\n';
    for (int x : ans) cout << x << ' ';
    return 0;
}
