/*
 * 2018 KAIST 8th ACM-ICPC Mock Competition
 * C. Electronic Circuit
 * QOJ 17864
 *
 * graph theory
 * Date: 2026.7.31
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;
using ii = pair<int, int>;
const int MAXN = 1e5+4;

set<ii> edg;
vector<int> hist[MAXN];
int deg[MAXN];
bitset<MAXN> alive;

ii edge_key(int x, int y) {
    return ii(min(x, y), max(x, y));
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m; cin >> n >> m;
    while (m--) {
        int x, y; cin >> x >> y;

        if (edg.emplace(edge_key(x, y)).second) {
            hist[x].push_back(y);
            hist[y].push_back(x);
            deg[x]++; deg[y]++;
        }
    }

    queue<int> q;
    for (int x = 1; x <= n; ++x) {
        alive.set(x);
        if (deg[x] == 2) q.push(x);
    }

    while (!q.empty()) {
        int x = q.front(); q.pop();
        if (!alive[x] || deg[x] != 2) continue;

        int a = -1, b = -1;
        for (int y : hist[x]) {
            if (edg.count(edge_key(x, y))) (a == -1 ? a : b) = y;
        }
        assert(b != -1);

        edg.erase(edge_key(x, a)); deg[x]--; deg[a]--;
        edg.erase(edge_key(x, b)); deg[x]--; deg[b]--;
        alive.reset(x);

        if (edg.emplace(edge_key(a, b)).second) {
            hist[a].push_back(b);
            hist[b].push_back(a);
            deg[a]++; deg[b]++;
        }
        if (alive[a] && deg[a] == 2) q.push(a);
        if (alive[b] && deg[b] == 2) q.push(b);
    }

    cout << (alive.count() == 2 && edg.size() == 1 ? "Yes" : "No");
    return 0;
}
