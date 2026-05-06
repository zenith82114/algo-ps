/*
 * Petrozavodsk Programming Camp, Winter 2021, Day 5: Almost Retired Dandelion Contest, ICPC Camp Contest 2 E. Smol Vertex Cover
 * Open Cup 2020/2021 Stage 11: Grand Prix of Nizhny Novgorod E. Smol Vertex Cover
 * BOJ 21086 - general maximum matching, 2-SAT
 * Date: 2024.1.4
 */

#include<bits/stdc++.h>
using namespace std;

vector<int> adj[512];
queue<int> q;
int vis[512], orig[512], par[512], match[512] {}, upd[512] {};
int tag = 0;
int n, m;

int lca(int x, int y) {
    ++tag;
    while (!x || upd[x] != tag) {
        if (x) {
            upd[x] = tag;
            x = orig[par[match[x]]];
        }
        swap(x, y);
    }
    return x;
}

void blossom(int x, int y, int a) {
    while (orig[x] != a) {
        par[x] = y; y = match[x];
        if (vis[y] == 1) { q.emplace(y); vis[y] = 0; }
        orig[x] = orig[y] = a;
        x = par[y];
    }
}

bool bfs(int u) {
    fill(vis+1, vis+n+1, -1);
    iota(orig+1, orig+n+1, 1);
    q = queue<int>(); q.emplace(u); vis[u] = 0;
    while (!q.empty()) {
        int x = q.front(); q.pop();
        for (int y : adj[x]) {
            if (vis[y] == -1) {
                par[y] = x; vis[y] = 1;
                if (!match[y]) {
                    while (y) {
                        int py = par[y];
                        int ny = match[py];
                        match[y] = py; match[py] = y;
                        y = ny;
                    }
                    return true;
                }
                q.emplace(match[y]); vis[match[y]] = 0;
            }
            else if (vis[y] == 0 && orig[x] != orig[y]) {
                int a = lca(orig[x], orig[y]);
                blossom(x, y, a); blossom(y, x, a);
            }
        }
    }
    return false;
}

vector<int> impl[1024];
int clk = 0;
int entry[1024] {}, link[1024] {};
stack<int> st;
bitset<1024> on_st;
int scc_id = 0;
int scc[1024] {};
bitset<512> val;

void dfs(int x) {
    entry[x] = link[x] = ++clk;
    st.emplace(x); on_st.set(x);
    for (int y : impl[x]) {
        if (!entry[y]) {
            dfs(y);
            link[x] = min(link[x], link[y]);
        }
        else if (on_st[y])
            link[x] = min(link[x], entry[y]);
    }
    if (entry[x] == link[x]) {
        scc_id++;
        while (st.top() != x) {
            int y = st.top();
            st.pop(); on_st.reset(y);
            scc[y] = scc_id;
        }
        st.pop(); on_st.reset(x);
        scc[x] = scc_id;
    }
}

bool solve_2sat() {
    fill_n(entry+1, 2*n, 0); clk = 0;
    fill_n(scc+1, 2*n, 0); scc_id = 0;
    val.reset();
    for (int x = 1; x <= 2*n; ++x) if (!entry[x]) dfs(x);
    assert(st.empty());
    assert(!on_st.count());
    for (int x = 1; x <= n; ++x) {
        if (scc[x] == scc[x+n]) return false;
        if (scc[x] < scc[x+n]) val.set(x);
    }
    return true;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m;
    while (m--) {
        int x, y; cin >> x >> y;
        adj[x].emplace_back(y);
        adj[y].emplace_back(x);
    }

    int M = 0;
    for (int x = 1; x <= n; ++x) if (!match[x] && bfs(x)) ++M;

    for (int x = 1; x <= n; ++x) if (!match[x]) {
        impl[x].emplace_back(x+n);
    }
    for (int x = 1; x <= n; ++x) for (int y : adj[x]) if (x < y) {
        impl[x+n].emplace_back(y);
        impl[y+n].emplace_back(x);
        if (match[x] == y) {
            impl[x].emplace_back(y+n);
            impl[y].emplace_back(x+n);
        }
    }
    if (solve_2sat()) {
        cout << M << '\n';
        for (int x = 1; x <= n; ++x) if (val[x]) cout << x << ' ';
        return 0;
    }

    auto del = [] (int x, int y) {
        auto p = find(impl[x].begin(), impl[x].end(), y);
        swap(*p, impl[x].back());
        impl[x].pop_back();
    };

    for (int x = 1; x <= n; ++x) if (!match[x]) {
        del(x, x+n);
        impl[x+n].emplace_back(x);
        if (solve_2sat()) {
            cout << (M+1) << '\n';
            for (int z = 1; z <= n; ++z) if (val[z]) cout << z << ' ';
            return 0;
        }
        impl[x].emplace_back(x+n);
        impl[x+n].pop_back();
    }

    for (int x = 1; x <= n; ++x) if (x < match[x]) {
        int y = match[x];
        del(x, y+n);
        del(y, x+n);
        impl[x+n].emplace_back(x);
        impl[y+n].emplace_back(y);
        if (solve_2sat()) {
            cout << (M+1) << '\n';
            for (int z = 1; z <= n; ++z) if (val[z]) cout << z << ' ';
            return 0;
        }
        impl[x].emplace_back(y+n);
        impl[y].emplace_back(x+n);
        impl[x+n].pop_back();
        impl[y+n].pop_back();
    }

    cout << "not smol"; return 0;
}
