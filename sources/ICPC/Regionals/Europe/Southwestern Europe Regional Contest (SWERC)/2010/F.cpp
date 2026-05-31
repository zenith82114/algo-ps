/*
 * ICPC, Regionals, Europe, Southwestern Europe Regional Contest,
 * SWERC 2010 F. Jumping Monkey
 * JUNGOL 2387
 *
 * BFS, bitmask
 * Date: 2026.5.31
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;
const int MAXN = 21;

int adj[MAXN];
int pred[1<<MAXN], opt[1<<MAXN];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m; cin >> n >> m;
    for (; n | m; cin >> n >> m) {
        for (int x = 0; x < n; ++x) adj[x] = 0;
        while (m--) {
            int x, y; cin >> x >> y;
            adj[x] |= 1<<y;
            adj[y] |= 1<<x;
        }

        const int ALL = (1<<n)-1;
        memset(pred, -1, (1<<n) * sizeof(int)); pred[ALL] = -2;
        queue<int> q; q.push(ALL);

        while (!q.empty()) {
            int s = q.front(); q.pop();
            for (int x = 0; x < n; ++x) {
                int ns = 0;
                for (int y = 0; y < n; ++y) if (((s>>y)&1) && y != x) ns |= adj[y];
                if (pred[ns] == -1) {
                    pred[ns] = s;
                    opt[ns] = x;
                    q.push(ns);
                }
            }
        }

        if (pred[0] == -1) cout << "Impossible\n";
        else {
            vector<int> path;
            for (int s = 0; s != ALL; s = pred[s]) path.push_back(opt[s]);
            reverse(begin(path), end(path));
            cout << path.size() << ':';
            for (int x : path) cout << ' ' << x;
            cout << '\n';
        }
    }

    return 0;
}
