/*
 * Baltic Olympiad in Informatics, BOI 2015 Day 2 C. Tug of War
 * BOJ 10783
 *
 * graph theory, DP, bitset
 * Date: 2023.12.22
 */

#include<bits/stdc++.h>
using namespace std;

vector<pair<int, int> > adj[60'001];
int deg[60'001];

int dfs(int px, int x) {
    deg[x] = 0;
    for (const auto& [y, w] : adj[x]) {
        if (y != px && deg[y]) return w - dfs(x, y);
    }
    return 0;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, k; cin >> n >> k;
    for (int i = 0; i < 2*n; ++i) {
        int x, y, w; cin >> x >> y >> w;
        y += n;
        adj[x].emplace_back(y, w); ++deg[x];
        adj[y].emplace_back(x, w); ++deg[y];
    }
    for (int x = 1; x <= 2*n; ++x) if (!deg[x]) {
        cout << "NO"; return 0;
    }

    queue<int> q;
    int c = 0;
    for (int x = 1; x <= 2*n; ++x) if (deg[x] == 1) q.emplace(x);
    while (!q.empty()) {
        int x = q.front(); q.pop();
        --deg[x];
        for (const auto& [y, w] : adj[x]) {
            if (!deg[y]) continue;
            --deg[y];
            c += x <= n? w : -w;
            if (deg[y] == 1) q.emplace(y);
        }
    }

    vector<int> v;
    for (int x = 1; x <= 2*n; ++x) if (deg[x]) {
        auto p = adj[x].end();
        for (auto pp = adj[x].begin(); pp != adj[x].end(); ++pp) {
            if (deg[pp->first]) { p = pp; break; }
        }
        int w = p->second;
        adj[x].erase(p);
        int t = abs(w - dfs(0, x));
        c -= t;
        v.emplace_back(t);
    }
    if (k < c) { cout << "NO"; return 0; }

    bitset<600'001> dp; dp.set(0);
    for (int t : v) { dp = (dp << t) | dp; }
    int s = (- k - c + 1)>>1;
    int e = (k - c)>>1;
    for (int i = max(0, s); i <= e; ++i) if (dp.test(i)) {
        cout << "YES"; return 0;
    }
    cout << "NO"; return 0;
}
