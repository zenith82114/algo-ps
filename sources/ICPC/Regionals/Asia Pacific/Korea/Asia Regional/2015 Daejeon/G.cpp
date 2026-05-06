/*
 * ICPC, Regionals, Asia Pacific, Korea,
 * Asia Regional - Daejeon 2015 C. Grid
 * BOJ 11495
 *
 * maximum flow
 * Date: 2022.1.30
 */

#include<bits/stdc++.h>
using namespace std;
constexpr int MAX = 2502, INF = INT32_MAX;

struct Edge {
    int to, cap;
    Edge(int t, int c): to(t), cap(c) {}
};
array<vector<Edge>, MAX> adj;
array<int, MAX> level, adj_len, hist;
int S, T;

bool bfs() {
    queue<int> q; q.push(S);
    for (int u = 0; u <= T; ++u) level[u] = -1;
    level[S] = 0;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (const auto& e : adj[u]) {
            if (e.cap > 0 && level[e.to] < 0) {
                level[e.to] = level[u]+1;
                q.push(e.to);
            }
        }
    }
    return level[T] != -1;
}

int dfs(int u, int f) {
    if (u == T)
        return f;
    for (int& i = hist[u]; i < adj_len[u]; ++i) {
        auto& e = adj[u][i];
        if (e.cap > 0 && level[e.to] == level[u]+1) {
            int r = dfs(e.to, min(f, e.cap));
            if (r > 0) {
                e.cap -= r;
                for (auto& re : adj[e.to]) {
                    if (re.to == u) {
                        re.cap += r;
                        break;
                    }
                }
                return r;
            }
        }
    }
    return 0;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int TC; cin >> TC;
    while (TC--) {
        int N, M; cin >> N >> M;
        S = N*M; adj[S].clear();
        T = S+1; adj[T].clear();
        int C = 0;
        for (int n = 0, p = 0; n < N; ++n) {
            for (int m = 0; m < M; ++m, ++p) {
                int c; cin >> c;
                C += c;
                adj[p].clear();
                if ((n^m) & 1) {
                    adj[S].emplace_back(p, c);
                    adj[p].emplace_back(S, 0);
                }
                else {
                    adj[p].emplace_back(T, c);
                    adj[T].emplace_back(p, 0);
                }
                c = (n^m) & 1 ? INF : 0;
                if (n > 0)
                    adj[p].emplace_back(p-M, c);
                if (n < N-1)
                    adj[p].emplace_back(p+M, c);
                if (m > 0)
                    adj[p].emplace_back(p-1, c);
                if (m < M-1)
                    adj[p].emplace_back(p+1, c);
            }
        }
        for (int p = 0; p <= T; ++p)
            adj_len[p] = adj[p].size();

        int F = 0;
        while (bfs()) {
            for (int p = 0; p <= T; ++p) hist[p] = 0;
            int f;
            while ((f = dfs(S, INF)) > 0) F += f;
        }
        cout << C - F << '\n';
    }

    return 0;
}
