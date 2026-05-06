/*
 * ICPC, Regionals, South Pacific, South Pacific Region,
 * 2016 South Pacific Divisional Contest F. Fusion
 * BOJ 15160 - 0-1 bfs
 * Date: 2025.8.30
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;
constexpr int inf = 0x3f3f3f3f;

char b[1000][1000];
int d[1000][1000];
constexpr int u[] {0,1,0,-1,0};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m; cin >> n >> m;
    int xs = -1, ys = -1, xt = -1, yt = -1;
    for (int x = 0; x < n; ++x)
    for (int y = 0; y < m; ++y) {
        char& c = b[x][y]; cin >> c;
        if (c == 'A') xs = xt, xt = x, ys = yt, yt = y;
    }
    b[xs][ys] = '#';
    int ans = inf;

    for (int i = 0; i < 4; ++i) {
        int x0 = xs + u[i], y0 = ys + u[i + 1];
        if (x0 < 0 || n <= x0 || y0 < 0 || m <= y0 || b[x0][y0] == '#') continue;

        memset(d, inf, sizeof d); d[x0][y0] = 1 + (b[x0][y0] != '.');
        deque<pair<int, int> > q; q.emplace_back(x0, y0);
        int cnt = d[x0][y0];

        while (!q.empty()) {
            auto [x, y] = q.front(); q.pop_front();
            if (b[x][y] == 'A') continue;

            for (int j = 0; j < 4; ++j) {
                int nx = x + u[j], ny = y + u[j + 1];
                if (nx < 0 || n <= nx || ny < 0 || m <= ny || b[nx][ny] == '#') continue;

                int w = (b[nx][ny] != '.');
                if (d[nx][ny] > d[x][y] + w) {
                    if (d[nx][ny] == inf && w) ++cnt;
                    d[nx][ny] = d[x][y] + w;
                    if (w) q.emplace_back(nx, ny);
                    else q.emplace_front(nx, ny);
                }
            }
        }

        if (d[xt][yt]%2 == 0) ans = min(ans, d[xt][yt]/2);
        else if (d[xt][yt] < cnt) ans = min(ans, (d[xt][yt] + 1)/2);
    }

    cout << (ans < inf? ans : -1);
    return 0;
}
