/*
 * ICPC, Regionals, Europe, Southwestern Europe Regional Contest,
 * SWERC 2011 B. Coin Collecting
 * BOJ 3836 - matroid intersection
 * Date: 2024.1.2
 */

#include<bits/stdc++.h>
using namespace std;
using ii = pair<int, int>;

int n, m;
ii edges[640];
bitset<640> indep;

vector<int> frst[1280], reg;
int cc[1280];
bitset<1280> vis, in_reg;

vector<int> exch[640];
int pred[640];

void push_reg(int x) {
    if (!in_reg[x]) {
        reg.emplace_back(x);
        in_reg.set(x);
    }
}

void add_edge(int e) {
    auto [x, y] = edges[e];
    push_reg(x); push_reg(y);
    frst[x].emplace_back(y);
    frst[y].emplace_back(x);
}

void del_edge(int e) {
    auto [x, y] = edges[e];
    push_reg(x); push_reg(y);
    frst[x].erase(find(frst[x].begin(), frst[x].end(), y));
    frst[y].erase(find(frst[y].begin(), frst[y].end(), x));
}

void dfs(int x, int c) {
    vis.set(x);
    cc[x] = c;
    for (int y : frst[x]) if (!vis[y]) dfs(y, c);
}

void get_cc() {
    vis.reset();
    for (int x : reg) {
        if (!vis[x]) dfs(x, x);
        in_reg.reset(x);
    }
    reg.clear();
}

bool augment() {
    const int s = m, t = m+1;
    for (int e = 0; e <= s; ++e) exch[e].clear();
    get_cc();

    for (int e = 0; e < m; ++e) if (!indep[e]) {
        auto [x, y] = edges[e];
        if (!indep[e^1]) exch[s].emplace_back(e);
        if (cc[x] != cc[y]) exch[e].emplace_back(t);
    }

    for (int e = 0; e < m; ++e) if (indep[e]) {
        indep.reset(e); del_edge(e);
        get_cc();
        for (int f = 0; f < m; ++f) if (!indep[f]) {
            auto [x, y] = edges[f];
            if (!indep[f^1]) exch[e].emplace_back(f);
            if (cc[x] != cc[y]) exch[f].emplace_back(e);
        }
        indep.set(e); add_edge(e);
    }

    queue<int> q; q.emplace(s);
    vis.reset(); vis.set(s);
    pred[t] = -1;
    while (!q.empty()) {
        int e = q.front(); q.pop();
        if (e == t) break;
        for (int f : exch[e]) if (!vis[f]) {
            q.emplace(f); vis.set(f);
            pred[f] = e;
        }
    }
    if (pred[t] == -1) return false;
    int e = pred[t]; indep.set(e); add_edge(e);
    while (pred[e] != s) {
        e = pred[e]; indep.reset(e); del_edge(e);
        e = pred[e]; indep.set(e); add_edge(e);
    }
    return true;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int mp[10'000];

    for (cin >> m; m; cin >> m) {
        m *= 2;
        n = 0;
        memset(mp, -1, sizeof mp);
        for (int e = 0; e < m; ++e) {
            auto& [x, y] = edges[e]; cin >> x >> y;
            if (mp[x] == -1) mp[x] = n++;
            x = mp[x];
            if (mp[y] == -1) mp[y] = n++;
            y = mp[y];
        }
        for (int x = 0; x < n; ++x) {
            frst[x].clear();
            cc[x] = x;
        }

        int ans = 0;
        indep.reset();
        reg.clear(); in_reg.reset();
        for (int e = 0; e < m; ++e) {
            auto [x, y] = edges[e];
            get_cc();
            if (!indep[e^1] && cc[x] != cc[y]) {
                indep.set(e); add_edge(e);
                ans += 2;
            }
        }
        while (augment()) ans += 2;
        cout << ans << '\n';
    }

    return 0;
}
