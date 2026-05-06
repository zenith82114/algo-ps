/*
 * ICPC Japanese Alumni Group, JAG Practice Contest for ACM-ICPC Asia Regional 2015 J. Longest Shortest Path
 * BOJ 13091 - LP dual, min cost flow
 * Date: 2024.6.8
 */

#include<bits/stdc++.h>
using namespace std;
constexpr int MAXN = 202;

struct edge {
    int id, from, to;
    double cap, cost;
    edge(int id, int from, int to, int cap, int cost)
    : id(id), from(from), to(to), cap(cap), cost(cost) {}
};

array<vector<int>, MAXN> adj;
vector<edge> edges;

void add_edge(int x, int y, int d, int c) {
    static int id = -1;
    adj[x].emplace_back(++id);
    edges.emplace_back(id, x, y, c, d);
    adj[y].emplace_back(++id);
    edges.emplace_back(id, y, x, 0, -d);
}

array<double, MAXN> dist;
array<int, MAXN> pred;
queue<int> q;
bitset<MAXN> inq;

bool spfa(int s, int t) {
    q.emplace(s);
    dist.fill(1e9); dist[s] = 0.;
    while (!q.empty()) {
        int x = q.front(); q.pop();
        inq.reset(x);
        for (int id : adj[x]) {
            auto& e = edges[id];
            if (e.cap > 1e-9 && dist[e.to] > dist[x] + e.cost + 1e-9) {
                dist[e.to] = dist[x] + e.cost;
                pred[e.to] = id;
                if (!inq[e.to]) {
                    q.emplace(e.to);
                    inq.set(e.to);
                }
            }
        }
    }
    return dist[t] < 1e8;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int N, M, P, s, t; cin >> N >> M >> P >> s >> t;
    while (M--) {
        int x, y, d, c; cin >> x >> y >> d >> c;
        add_edge(x, y, d, c);
    }

    double F = 0., C = 0.;
    double ans = 1e9;
    while (spfa(s, t)) {
        double dF = 1e9;
        for (int x = t; x != s; x = edges[pred[x]].from) {
            dF = min(dF, edges[pred[x]].cap);
        }
        for (int x = t; x != s; x = edges[pred[x]].from) {
            edge& e = edges[pred[x]];
            C += dF * e.cost;
            e.cap -= dF;
            edges[e.id^1].cap += dF;
        }
        F += dF;
        ans = min(ans, (C + P)/F);
    }

    cout << fixed << setprecision(9) << ans;
    return 0;
}
