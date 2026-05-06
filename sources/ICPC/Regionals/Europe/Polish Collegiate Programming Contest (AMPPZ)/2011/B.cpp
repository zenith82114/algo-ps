/*
 * ICPC, Regionals, Europe, Central Europe Regional Contest,
 * Polish Collegiate Programming Contest, AMPPZ 2011 B. Bytean Road Race
 * BOJ 7907 - dominance drawing of st-planar graph
 * Date: 2026.4.1
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;
constexpr int MAXN = 1e5 +4;

array<int, MAXN> x, y;
int gph[MAXN][2] {};
int ord[MAXN][2] {};

void dfs(int x, int prio, int& clk) {
    ord[x][prio] = -1;
    for (int y : { gph[x][prio], gph[x][prio^1] }) {
        if (y && !ord[y][prio]) dfs(y, prio, clk);
    }
    ord[x][prio] = clk--;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m, k; cin >> n >> m >> k;
    for (int i = 1; i <= n; ++i) cin >> x[i] >> y[i];
    while (m--) {
        int i, j; cin >> i >> j;
        if (x[i] == x[j]) {
            if (y[i] < y[j]) swap(i, j);
            gph[i][0] = j;
        } else {
            if (x[i] > x[j]) swap(i, j);
            gph[i][1] = j;
        }
    }

    int clk = n; dfs(1, 0, clk);
    clk = n; dfs(1, 1, clk);

    while (k--) {
        int i, j; cin >> i >> j;
        if (ord[i][0] > ord[j][0]) swap(i, j);
        cout << (ord[i][1] < ord[j][1] ? "TAK" : "NIE") << '\n';
    }
    return 0;
}
