/*
 * ICPC, Regionals, Europe, Central Europe Regional Contest,
 * CERC 2011 D. Racing Car Trail
 * BOJ 3419
 * JUNGOL 4376
 *
 * bipartite matching
 * Date: 2025.9.6
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;
using grid = char[100][100];

int n, m;
constexpr int dt[] {0,1,0,-1,0};
grid inp, vis;
pair<int, int> mate[100][100];

bool invalid(int x, int y) {
    return (x < 0 || n <= x || y < 0 || m <= y || inp[x][y] == 'X');
}

bool augment(int x, int y) {
    vis[x][y] = 1;
    for (int i = 0; i < 4; ++i) {
        int x2 = x + dt[i], y2 = y + dt[i + 1];
        if (invalid(x2, y2)) continue;
        auto [mx, my] = mate[x2][y2];
        if (mx == -1 || (!vis[mx][my] && augment(mx, my))) {
            mate[x2][y2] = make_pair(x, y);
            mate[x][y] = make_pair(x2, y2);
            return true;
        }
    }
    return false;
}

bool check_alt(int x, int y) {
    vis[x][y] = 1;
    auto [mx, my] = mate[x][y];
    for (int i = 0; i < 4; ++i) {
        int x2 = mx + dt[i], y2 = my + dt[i + 1];
        if (invalid(x2, y2) || vis[x2][y2]) continue;
        vis[x2][y2] = 1;
        if (mate[x2][y2].first == -1 || check_alt(x2, y2)) return true;
    }
    return false;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m;
    for (; n; cin >> n >> m) {
        for (int x = 0; x < n; ++x)
        for (int y = 0; y < m; ++y) {
            cin >> inp[x][y];
            mate[x][y].first = -1;
        }

        for (int x = 0; x < n; ++x)
        for (int y = 0; y < m; ++y) {
            if (inp[x][y] == '.' && mate[x][y].first == -1) {
                memset(vis, 0, sizeof vis);
                augment(x, y);
            }
        }

        for (int x = 0; x < n; ++x) {
            for (int y = 0; y < m; ++y) {
                if (inp[x][y] == 'X') cout << 'X';
                else if (mate[x][y].first == -1) cout << 'B';
                else {
                    memset(vis, 0, sizeof vis);
                    cout << (check_alt(x, y)? 'B' : 'A');
                }
            }
            cout << '\n';
        }
        cout << '\n';
    }

    return 0;
}
