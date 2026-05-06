/*
 * ICPC, Regionals, Northern Eurasia, Northeastern Europe Regional Contest,
 * NEERC 2006 H. Hard Life
 * BOJ 3611 - maximum density subgraph (Goldberg's alg.)
 * Date: 2024.12.29
 */

#include<bits/stdc++.h>
using namespace std;
constexpr double eps = 1e-9;

vector<int> adj[102];
int deg[102] {};
double cap[102][102];
int pred[102];

bool bfs(int s, int t) {
    queue<int> q; q.emplace(s);
    memset(pred, -1, sizeof pred);
    pred[s] = s;
    while (!q.empty()) {
        int x = q.front(); q.pop();
        for (int y : adj[x]) if (pred[y] == -1 && cap[x][y] > eps) {
            pred[y] = x;
            q.emplace(y);
        }
    }
    return pred[t] != -1;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m; cin >> n >> m;
    const int s = 0, t = n + 1;
    for (int x = 1; x <= n; ++x) {
        adj[s].emplace_back(x);
        adj[x].emplace_back(t);
    }
    for (int i = 0; i < m; ++i) {
        int x, y; cin >> x >> y;
        adj[x].emplace_back(y);
        adj[y].emplace_back(x);
        ++deg[x]; ++deg[y];
    }

    double lo = 0, hi = m;
    const double delta = 1. / (n * (n + 1)) - eps;
    vector<int> ans { 1 };

    while (lo + delta <= hi) {
        double g = .5 * (lo + hi);

        for (int x = 1; x <= n; ++x) {
            for (int y : adj[x]) cap[x][y] = cap[y][x] = 1;
            cap[s][x] = m;
            cap[x][s] = 0;
            cap[x][t] = m + 2 * g - deg[x];
            cap[t][x] = 0;
        }

        while (bfs(s, t)) {
            double f = 1e9;
            for (int x = t; x != s; x = pred[x]) f = min(f, cap[pred[x]][x]);
            for (int x = t; x != s; x = pred[x]) {
                cap[pred[x]][x] -= f;
                cap[x][pred[x]] += f;
            }
        }

        vector<int> tmp;
        for (int x = 1; x <= n; ++x) if (pred[x] != -1) {
            tmp.emplace_back(x);
        }
        if (tmp.empty()) hi = g;
        else {
            lo = g;
            ans.swap(tmp);
        }
    }

    cout << ans.size() << '\n';
    for (int x : ans) cout << x << '\n';
    return 0;
}
