/*
 * ICPC, Regionals, Europe, Northwestern Europe Regional Contest,
 * NWERC 2011 D. Piece it together
 * BOJ 3654
 * JUNGOL 15600
 *
 * bipartite matching
 * Date: 2024.3.14
 */

#include<bits/stdc++.h>
using namespace std;
constexpr int INF = INT32_MAX;

int NIL;
char f[500][500];
array<vector<int>, 250'000> adj;
array<bool, 250'000> chk;
array<int, 250'001> level, match;

bool bfs(const vector<int>& U) {
    queue<int> q;
    for (int u : U) {
        if (match[u] == NIL) {
            level[u] = 0;
            q.emplace(u);
        }
        else level[u] = INF;
    }
    level[NIL] = INF;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        if (level[u] >= level[NIL]) continue;
        for (int v : adj[u]) {
            if (level[match[v]] == INF) {
                level[match[v]] = level[u] + 1;
                q.emplace(match[v]);
            }
        }
    }
    return level[NIL] != INF;
}

size_t dfs(int u) {
    if (u == NIL) return 1;
    for (int v : adj[u]) {
        if (level[match[v]] == level[u] + 1 && dfs(match[v])) {
            match[v] = u;
            match[u] = v;
            return 1;
        }
    }
    level[u] = INF;
    return 0;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    constexpr int di[] {-1,1,0,0}, dj[] {0,0,-1,1};

    int tc; cin >> tc;
    while (tc--) {
        int n, m; cin >> n >> m;
        NIL = n*m;
        vector<int> black;
        for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j) {
            cin >> f[i][j];
            int x = i*m + j;
            if (f[i][j] == 'B') black.emplace_back(x);
            if (f[i][j] == 'W') {
                chk[x] = false;
                match[x] = NIL;
            }
        }
        if (black.empty()) { cout << "NO\n"; continue; }

        bool ans = true;

        for (int PARITY : {0, 1}) {
            size_t white = 0;

            for (int x : black) {
                adj[x].clear();
                match[x] = NIL;

                int i = x/m, j = x%m;
                for (int k = 0; k < 4; ++k) {
                    int ni = i + di[k], nj = j + dj[k];
                    if (ni < 0 || ni == n || nj < 0 || nj == m) continue;
                    if ((ni&1) == PARITY && f[ni][nj] == 'W') {
                        int nx = ni*m + nj;
                        if (!chk[nx]) {
                            chk[nx] = true;
                            ++white;
                        }
                        adj[x].emplace_back(nx);
                    }
                }
            }
            if (white != black.size()) { ans = false; break; }

            size_t sz_match = 0;
            while (bfs(black)) {
                for (int x : black) if (match[x] == NIL) sz_match += dfs(x);
            }
            if (sz_match != black.size()) { ans = false; break; }
        }

        cout << (ans? "YES\n" : "NO\n");
    }

    return 0;
}
