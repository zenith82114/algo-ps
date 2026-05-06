/*
 * 한국정보올림피아드, KOI 2011, 중등부 4/고등부 4. 그리드 게임
 * BOJ 2452
 * JUNGOL 2503
 *
 * BFS, heuristic
 * Date: 2026.4.30
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;

constexpr int dir[] {0,-1,0,1,0};

int n, m;
char f[100][100];
int e[100][100];
vector<int> gph[10000];

int dist[10000], max_dist[10000];
int visited[10000] {}, visit_id = 0;
int num_c = 0;
int ans = 1e9;

int full_bfs(int s) {
    int argmax = s;
    queue<int> q; q.push(s);
    memset(dist, 0x3f, sizeof(int) * num_c); dist[s] = 0;

    while (!q.empty()) {
        int u = q.front(); q.pop();
        if (dist[argmax] < dist[u]) argmax = u;
        max_dist[u] = max(max_dist[u], dist[u]);
        for (int v : gph[u]) if (dist[v] > dist[u] + 1) {
            dist[v] = dist[u] + 1;
            q.push(v);
        }
    }

    ans = min(ans, dist[argmax]);
    return argmax;
}

void pruned_bfs(int s) {
    if (max_dist[s] >= ans) return;

    queue<int> q; q.push(s);
    visited[s] = ++visit_id;
    int cur = -1;

    for (; !q.empty() && cur < ans; ++cur) {
        int sz = q.size();
        while (sz--) {
            int u = q.front(); q.pop();
            max_dist[u] = max(max_dist[u], cur);
            for (int v : gph[u]) if (visited[v] != visit_id) {
                visited[v] = visit_id;
                q.push(v);
            }
        }
    }
    ans = cur;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m;
    for (int x = 0; x < n; ++x)
    for (int y = 0; y < m; ++y) cin >> f[x][y];

    memset(e, -1, sizeof e);
    for (int x0 = 0; x0 < n; ++x0)
    for (int y0 = 0; y0 < m; ++y0) if (e[x0][y0] == -1) {
        queue<pair<int, int> > q; q.emplace(x0, y0);
        e[x0][y0] = num_c;
        while (!q.empty()) {
            auto [x, y] = q.front(); q.pop();
            for (int i = 0; i < 4; ++i) {
                int nx = x + dir[i], ny = y + dir[i + 1];
                if (nx < 0 || n <= nx || ny < 0 || m <= ny) continue;
                if (e[nx][ny] == -1 && f[x][y] == f[nx][ny]) {
                    e[nx][ny] = num_c;
                    q.emplace(nx, ny);
                }
            }
        }
        ++num_c;
    }

    for (int x = 0; x < n; ++x)
    for (int y = 0; y < m; ++y)
    for (int i = 0; i < 4; ++i) {
        int nx = x + dir[i], ny = y + dir[i + 1];
        if (nx < 0 || n <= nx || ny < 0 || m <= ny) continue;
        int u = e[x][y], v = e[nx][ny];
        if (u != v) {
            gph[u].push_back(v);
            gph[v].push_back(u);
        }
    }
    for (int i = 0; i < num_c; ++i) {
        sort(gph[i].begin(), gph[i].end());
        gph[i].erase(unique(gph[i].begin(), gph[i].end()), gph[i].end());
    }

    int a = full_bfs(num_c/2);
    int b = full_bfs(a);
    full_bfs(b);

    vector<int> seq(num_c); iota(begin(seq), end(seq), 0);
    sort(begin(seq), end(seq), [](int u, int v) { return max_dist[u] < max_dist[v]; });
    for (int u : seq) pruned_bfs(u);
    cout << ans;
    return 0;
}
