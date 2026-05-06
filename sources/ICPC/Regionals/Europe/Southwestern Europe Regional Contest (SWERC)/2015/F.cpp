/*
 * ICPC, Regionals, Europe, Southwestern Europe Regional Contest,
 * SWERC 2015 F. Landscaping
 * BOJ 11682 - max-flow min-cut duality
 * Date: 2023.7.10
 */

#include<bits/stdc++.h>
using namespace std;
using ii = pair<int, int>;

vector<ii> adj[2502]; // <vertex, edge id>
vector<int> cap;

bool inq[2502];
bool seen[2502];
ii pred[2502]; // <vertex, edge id>

bool spfa(int S, int T) {
    fill(seen, seen+T+1, false); seen[S] = true;
    queue<int> q; q.emplace(S);
    while (!q.empty()) {
        int x = q.front(); q.pop(); inq[x] = false;
        for (const auto& [y, k] : adj[x]) if (!seen[y] && cap[k]) {
            seen[y] = true;
            pred[y] = make_pair(x, k);
            if (!inq[y]) {
                q.emplace(y);
                inq[y] = true;
            }
        }
    }
    return seen[T];
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);

    int N, M, A, B; cin >> N >> M >> A >> B;
    const int S = N*M;
    const int T = S+1;

    auto add_edge = [&] (int x, int y, int c, int rc) {
        int k = cap.size();
        adj[x].emplace_back(y, k);
        adj[y].emplace_back(x, k|1);
        cap.emplace_back(c);
        cap.emplace_back(rc);
    };

    for (int i = 0; i < N; ++i)
    for (int j = 0; j < M; ++j) {
        int x = i*M + j;
        char c; cin >> c;
        if (c == '.') add_edge(S, x, B, 0);
        else add_edge(x, T, B, 0);
        if (i) add_edge(x, x-M, A, A);
        if (j) add_edge(x, x-1, A, A);
    }

    int64_t ans = 0;
    while (spfa(S, T)) {
        int c = INT32_MAX;
        for (int x = T; x != S; x = pred[x].first) {
            int k = pred[x].second;
            c = min(c, cap[k]);
        }
        ans += c;
        for (int x = T; x != S; x = pred[x].first) {
            int k = pred[x].second;
            cap[k] -= c;
            cap[k^1] += c;
        }
    }
    cout << ans;
    return 0;
}
