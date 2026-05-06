/*
 * ICPC, Regionals, Northern Eurasia, Northeastern Europe Regional Contest,
 * NEERC 2012 L. Labyrinth of the Minotaur
 * BOJ 4001 - BFS, prefix sum, binary search
 * Date: 2024.8.13
 */

#include<bits/stdc++.h>
using namespace std;

using int2d = int[1502][1502];
int2d world {}, lh {}, rh {}, vis;
const int dx[] = { 1, 0, -1, 0, 1, 1, -1, -1 };
const int dy[] = { 0, 1, 0, -1, 1, -1, 1, -1 };

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int w, h; cin >> w >> h;
    for (int x = 1; x <= h; ++x) {
        string s; cin >> s;
        for (int y = 0; y < w; ++y) world[x][y + 1] = s[y] & 1;
    }

    auto bfs = [h, w] (int sx, int sy, int2d& p) {
        for (int x = 0; x <= h + 1; ++x)
        for (int y = 0; y <= w + 1; ++y) vis[x][y] = 0;
        queue<pair<int, int> > q; q.emplace(sx, sy);
        vis[sx][sy] = 1;

        while (q.size()) {
            auto [x, y] = q.front(); q.pop();
            for (int k = 0; k < 8; ++k) {
                int nx = x + dx[k], ny = y + dy[k];
                if (nx < 0 || nx > h + 1 || ny < 0 || ny > w + 1) continue;
                if (vis[nx][ny]) continue;
                vis[nx][ny] = 1;
                if (world[nx][ny]) q.emplace(nx, ny);
                else p[nx][ny] = 1;
            }
        }
    };

    for (int y = 2; y <= w; ++y) world[0][y] = 1;
    for (int x = 0; x < h; ++x) world[x][w + 1] = 1;
    bfs(0, w + 1, lh);
    for (int x = 2; x <= h; ++x) world[x][0] = 1;
    for (int y = 1; y < w; ++y) world[h + 1][y] = 1;
    bfs(h + 1, 0, rh);
    for (int x = 0; x <= h + 1; ++x) {
        world[x][0] = world[x][w + 1] = 0;
        lh[x][0] = lh[x][w + 1] = 0;
        rh[x][0] = rh[x][w + 1] = 0;
    }
    for (int y = 0; y <= w + 1; ++y) {
        world[0][y] = world[h + 1][y] = 0;
        lh[0][y] = lh[h + 1][y] = 0;
        rh[0][y] = rh[h + 1][y] = 0;
    }
    world[1][1] = world[h][w] = 1;

    for (int x = 1; x <= h; ++x)
    for (int y = 1; y <= w; ++y) {
        world[x][y] += world[x - 1][y] + world[x][y - 1] - world[x - 1][y - 1];
        lh[x][y] += lh[x - 1][y] + lh[x][y - 1] - lh[x - 1][y - 1];
        rh[x][y] += rh[x - 1][y] + rh[x][y - 1] - rh[x - 1][y - 1];
    }

    auto f = [] (int x, int y, int d, const int2d& p) -> bool {
        int x2 = x + d - 1, y2 = y + d - 1;
        return p[x2][y2] - p[x - 1][y2] - p[x2][y - 1] + p[x - 1][y - 1] > 0;
    };

    auto bs = [h, w, f] (int x, int y, const int2d& p) -> int {
        int lo = 0, hi = min(h - x, w - y) + 1;
        while (lo + 1 < hi) {
            int mid = (lo + hi) / 2;
            (f(x, y, mid, p)? hi : lo) = mid;
        }
        return hi;
    };

    int ansx = -1, ansy = -1, ansd = 1500;
    for (int x = 1; x <= h; ++x)
    for (int y = 1; y <= w; ++y) {
        int d = max(bs(x, y, lh), bs(x, y, rh));
        if (f(x, y, d, world) || !f(x, y, d, lh) || !f(x, y, d, rh)) continue;
        if (ansd > d) {
            ansx = x, ansy = y, ansd = d;
        }
    }
    if (ansx == -1) cout << "Impossible";
    else cout << ansd << ' ' << ansy << ' ' << ansx;

    return 0;
}
