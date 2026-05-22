/*
 * ICPC, Regionals, Europe, Northwestern Europe Regional Contest,
 * NWERC 2012 A. Admiral
 * BOJ 3640
 * JUNGOL 3100
 *
 * min cost flow
 * Date: 2022.10.3
 */

#include<bits/stdc++.h>
using namespace std;

struct adj_entry {
    int v, e_id;
    adj_entry(int v, int i) : v(v), e_id(i) {}
};
vector<vector<adj_entry> > adj;

struct edge {
    bool cap; int wei;
    edge(bool c, int w) : cap(c), wei(w) {}
};
vector<edge> edges;

void add_edge(int u, int v, int w) {
    int sz = edges.size();
    adj[u].emplace_back(v, sz);
    adj[v].emplace_back(u, sz|1);
    edges.emplace_back(true, w);
    edges.emplace_back(false, -w);
};

vector<bool> in_q;
vector<int> dist;
vector<pair<int, int> > pred;

void spfa(int s, int t) {
    constexpr int INF = INT_MAX;
    queue<int> q; q.emplace(s);
    fill(in_q.begin(), in_q.end(), false);
    fill(dist.begin(), dist.end(), INF); dist[s] = 0;

    while (!q.empty()) {
        int u = q.front(); q.pop(); in_q[u] = false;
        for (const auto &it : adj[u]) {
            const int &v = it.v;
            const edge &e = edges[it.e_id];
            if (dist[v] > dist[u] + e.wei && e.cap) {
                dist[v] = dist[u] + e.wei;
                pred[v] = make_pair(u, it.e_id);
                if (!in_q[v]) {
                    q.emplace(v); in_q[v] = true;
                }
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    auto in  = [](int u) { return u<<1; };
    auto out = [](int u) { return u<<1|1; };

    cin >> std::ws;
    while (cin.peek() != EOF) {
        int V, E; cin >> V >> E;

        adj.clear(); adj.resize(V<<1);
        edges.clear();

        for (int u = 0; u < V; ++u)
            add_edge(in(u), out(u), 0);
        while (E--) {
            int u, v, w; cin >> u >> v >> w;
            add_edge(out(--u), in(--v), w);
        }

        in_q.resize(V<<1);
        dist.resize(V<<1);
        pred.resize(V<<1);
        const int S = out(0), T = in(V-1);
        int ans = 0;

        spfa(S, T);
        for (int v = T; v != S; v = pred[v].first) {
            edge &e  = edges[pred[v].second];
            edge &re = edges[pred[v].second ^ 1];
            ans += e.wei;
            e.cap = false; re.cap = true;
        }
        spfa(S, T);
        for (int v = T; v != S; v = pred[v].first) {
            edge &e  = edges[pred[v].second];
            edge &re = edges[pred[v].second ^ 1];
            ans += e.wei;
            e.cap = false; re.cap = true;
        }

        cout << ans << '\n';
        cin >> std::ws;
    }

    return 0;
}
