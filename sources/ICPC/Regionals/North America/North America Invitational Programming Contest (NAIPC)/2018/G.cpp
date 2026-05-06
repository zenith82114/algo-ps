/*
 * North American Invitational Programming Contest, NAIPC 2018 G. Rainbow Graph
 * BOJ 16046 - matroid intersection
 * Date: 2023.12.29
 */

#include<bits/stdc++.h>
using namespace std;
using ii = pair<int, int>;

int n, m;
ii edges[128];
int wei[128];
char color[128];

class oracle {
    int dsu[128];
    char ignore;
    int find(int x) {
        return dsu[x] < 0? x : dsu[x] = find(dsu[x]);
    }
public:
    oracle(char c): ignore(c) {}
    void clear() { fill_n(dsu+1, n, -1); }
    void add(int i) {
        if (color[i] == ignore) return;
        auto [x, y] = edges[i];
        x = find(x); y = find(y);
        if (x == y) return;
        if (dsu[x] < dsu[y]) swap(x, y);
        if (dsu[x] == dsu[y]) --dsu[y];
        dsu[x] = y;
    }
    bool query() {
        for (int x = 1; x < n; ++x) if (find(x) != find(x+1)) return false;
        return true;
    }
} oracle1('R'), oracle2('B');

vector<ii> exch_graph[128];
bitset<128> indep;
queue<int> q;
bitset<128> inq;
int dist[128], pred[128];

bool augment() {
    const int s = m, t = m+1;
    for (int x = 0; x < t; ++x) exch_graph[x].clear();
    for (int x = 0; x < m; ++x) {
        if (!indep[x]) {
            indep.set(x);
            oracle1.clear(); oracle2.clear();
            for (int z = 0; z < m; ++z) if (!indep[z]) {
                oracle1.add(z); oracle2.add(z);
            }
            if (oracle1.query()) exch_graph[s].emplace_back(x, -wei[x]);
            if (oracle2.query()) exch_graph[x].emplace_back(t, 0);
            indep.reset(x);
        } else for (int y = 0; y < m; ++y) if (!indep[y]) {
            indep.reset(x); indep.set(y);
            oracle1.clear(); oracle2.clear();
            for (int z = 0; z < m; ++z) if (!indep[z]) {
                oracle1.add(z); oracle2.add(z);
            }
            if (oracle1.query()) exch_graph[x].emplace_back(y, -wei[y]);
            if (oracle2.query()) exch_graph[y].emplace_back(x, +wei[x]);
            indep.set(x); indep.reset(y);
        }
    }

    fill_n(dist, m+2, INT32_MAX>>1);
    q.emplace(s); dist[s] = 0;
    pred[t] = -1;
    while (!q.empty()) {
        int x = q.front(); q.pop(); inq.reset(x);
        for (const auto& [y, w] : exch_graph[x]) {
            if (dist[y] > dist[x] + w) {
                dist[y] = dist[x] + w;
                pred[y] = x;
                if (!inq[y]) { q.emplace(y); inq.set(y); }
            }
        }
    }
    if (pred[t] == -1) return false;
    for (int x = t; x != s; x = pred[x]) indep.flip(x);
    return true;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        auto& [x, y] = edges[i];
        cin >> x >> y >> wei[i] >> color[i];
    }

    oracle1.clear(); oracle2.clear();
    for (int i = 0; i < m; ++i) { oracle1.add(i); oracle2.add(i); }
    if (!oracle1.query() || !oracle2.query()) {
        for (int i = 0; i < m; ++i) cout << "-1\n";
        return 0;
    }

    vector<int> ans(m, -1);
    for (int& a : ans) {
        a = 0;
        for (int x = 0; x < m; ++x) if (!indep[x]) a += wei[x];
        if (!augment()) break;
    }
    reverse(ans.begin(), ans.end());
    for (int a : ans) cout << a << '\n';
    return 0;
}
