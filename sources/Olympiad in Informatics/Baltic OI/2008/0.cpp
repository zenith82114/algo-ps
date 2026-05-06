/*
 * Baltic Olympiad in Informatics, BOI 2008 0. Mafia
 * BOJ 1210
 *
 * max-flow min-cut duality
 * Date: 2022.4.3
 */

#include<bits/stdc++.h>
using namespace std;

using i64 = int64_t;
const int INF = INT_MAX;
const int SIZE = 402;

array<array<int, SIZE>, SIZE> cap;
array<bool, SIZE> visited;
array<int, SIZE> pred;

inline int IN(int n) { return n<<1; }
inline int OUT(int n) { return n<<1|1; }

bool bfs(const int N, const int S, const int T) {
    queue<int> q;
    visited.fill(false);
    visited[IN(S)] = true;
    q.emplace(IN(S));
    while (!q.empty()) {
        int u = q.front(); q.pop();
        int vb = u&1 ? IN(1) : OUT(1);
        int ve = u&1 ? IN(N) : OUT(N);
        for (int v = vb; v <= ve; v += 2) {
            if (!visited[v] && cap[u][v] > 0) {
                visited[v] = true;
                pred[v] = u;
                if (v == OUT(T))
                    return true;
                q.emplace(v);
            }
        }
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int N, M, S, T;
    cin >> N >> M >> S >> T;
    for (int n = 1; n <= N; ++n)
        cin >> cap[IN(n)][OUT(n)];
    while (M--) {
        int u, v; cin >> u >> v;
        cap[OUT(u)][IN(v)] = INF;
        cap[OUT(v)][IN(u)] = INF;
    }

    pred[IN(S)] = 0;
    while (bfs(N, S, T)) {
        int f = INF;
        for (int u = OUT(T); u != IN(S); u = pred[u])
            f = min(f, cap[pred[u]][u]);
        for (int u = OUT(T); u != IN(S); u = pred[u]) {
            cap[pred[u]][u] -= f;
            cap[u][pred[u]] += f;
        }
    }

    for (int n = 1; n <= N; ++n) {
        if (visited[IN(n)] && !visited[OUT(n)])
            cout << n << ' ';
    }
    cout << '\n';
    return 0;
}
