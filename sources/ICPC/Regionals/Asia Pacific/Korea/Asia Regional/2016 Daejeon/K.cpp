/*
 * ICPC, Regionals, Asia Pacific, Korea,
 * Asia Regional - Daejeon 2016 K. Rounding
 * BOJ 13569
 *
 * circulation; Dinic's
 * Date: 2023.8.23
 */

#include<bits/stdc++.h>
using namespace std;

vector<int> adj[404];
int val[201][201] {};
int cap[404][404] {};
int level[404], adjsz[404], hist[404];

bool bfs(int s1, int t1) {
    memset(level, -1, sizeof level);
    queue<int> q; q.emplace(s1);
    level[s1] = 0;
    while (!q.empty()) {
        int x = q.front(); q.pop();
        for (int y : adj[x]) if (cap[x][y] && !~level[y]) {
            level[y] = level[x] + 1;
            q.emplace(y);
        }
    }
    return level[t1] != -1;
}

int dfs(int x, int f, int t1) {
    if (x == t1) return f;
    for (int& i = hist[x]; i < adjsz[x]; ++i) {
        int y = adj[x][i];
        if (cap[x][y] && level[y] == level[x] + 1) {
            int r = dfs(y, min(f, cap[x][y]), t1);
            if (r) {
                cap[x][y] -= r;
                cap[y][x] += r;
                return r;
            }
        }
    }
    return 0;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);

    int n, m; cin >> n >> m;
    const int s0 = n+m, s1 = n+m+1, t0 = n+m+2, t1 = n+m+3;

    string s;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> s; char b = s.back();
            s.pop_back(); s.pop_back();
            int& c = val[i][j] = stoi(s);
            cap[s1][n+j] += c;
            cap[i][t1] += c;
            cap[i][n+j] = b == '0'? 0 : 1;
        }
        cin >> s; char b = s.back();
        s.pop_back(); s.pop_back();
        int& c = val[i][m] = stoi(s);
        cap[s1][i] += c;
        cap[s0][t1] += c;
        cap[s0][i] = b == '0'? 0 : 1;
    }
    for (int j = 0; j < m; ++j) {
        cin >> s; char b = s.back();
        s.pop_back(); s.pop_back();
        int& c = val[n][j] = stoi(s);
        cap[s1][t0] += c;
        cap[n+j][t1] += c;
        cap[n+j][t0] = b == '0'? 0 : 1;
    }
    cap[t0][s0] = INT32_MAX;

    for (int x = 0; x <= t1; ++x)
    for (int y = x+1; y <= t1; ++y) if (cap[x][y] | cap[y][x]) {
        adj[x].emplace_back(y);
        adj[y].emplace_back(x);
    }

    for (int x = 0; x <= t1; ++x) adjsz[x] = adj[x].size();

    while (bfs(s1, t1)) {
        memset(hist, 0, sizeof hist);
        while (dfs(s1, INT32_MAX, t1));
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) cout << (val[i][j] + cap[n+j][i]) << ' ';
        cout << (val[i][m] + cap[i][s0]) << '\n';
    }
    for (int j = 0; j < m; ++j) cout << (val[n][j] + cap[t0][n+j]) << ' ';
    return 0;
}
