/*
 * Baltic Olympiad in Informatics, BOI 2001 Day 2 A. Knights
 * BOJ 3391
 *
 * Konig's theorem, Dinic's
 * Date: 2025.6.28
 */

#include<bits/stdc++.h>
using namespace std;

const int dx[] { -2,-2,-1,-1,1,1,2,2 };
const int dy[] { -1,1,-2,2,-2,2,-1,1 };

int n, s, t;
bool flag[200][200];
vector<pair<int, int> > adj[40'002];
vector<int> cap;
int level[40'002] {};
unsigned hist[40'002] {};

void add_edge(int u, int v) {
    adj[u].emplace_back(v, cap.size());
    adj[v].emplace_back(u, cap.size() + 1);
    cap.emplace_back(1);
    cap.emplace_back(0);
}

bool bfs() {
    queue<int> q; q.emplace(s);
    fill(level, level + s, -1);
    level[s] = 0; level[t] = -1;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (const auto& [v, e] : adj[u]) {
            if (level[v] == -1 && cap[e]) {
                level[v] = level[u] + 1;
                q.emplace(v);
            }
        }
    }
    return level[t] != -1;
}

int dfs(int u) {
    if (u == t) return 1;
    for (auto& i = hist[u]; i < adj[u].size(); ++i) {
        const auto& [v, e] = adj[u][i];
        if (level[v] == level[u] + 1 && cap[e] && dfs(v)) {
            cap[e] = 0;
            cap[e ^ 1] = 1;
            return 1;
        }
    }
    return 0;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int m; cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int x, y; cin >> x >> y;
        flag[--x][--y] = true;
    }
    s = n*n; t = s + 1;

    for (int x = 0; x < n; ++x)
    for (int y = 0; y < n; ++y) if (!flag[x][y]) {
        int id = x*n + y;
        if ((x ^ y) & 1) add_edge(s, id); else add_edge(id, t);
        for (int k = 0; k < 8; ++k) {
            int xx = x + dx[k];
            int yy = y + dy[k];
            if (xx < 0 || xx >= n || yy < 0 || yy >= n) continue;
            if (flag[xx][yy]) continue;
            if ((x ^ y) & 1) add_edge(id, xx*n + yy);
            else add_edge(xx*n + yy, id);
        }
    }

    int ans = n*n - m;
    while (bfs()) {
        fill(hist, hist + t + 1, 0);
        while (dfs(s)) --ans;
    }
    cout << ans;
    return 0;
}
