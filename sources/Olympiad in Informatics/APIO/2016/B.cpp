/*
 * Asia-Pacific Informatics Olympiad, APIO 2016 B. Fireworks
 * BOJ 12736
 * JUNGOL 3613
 *
 * slope trick, smaller to larger
 * Date: 2023.2.22
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;
constexpr int MAXN = 3e5 + 4;

vector<pair<int, int>> tree[MAXN];
priority_queue<i64> pqs[MAXN];

i64 dfs(int u) {
    auto& pqu = pqs[u];
    if (tree[u].size()) {
        i64 y0 = 0L;
        for (const auto& [v, c] : tree[u]) {
            y0 += c + dfs(v);
            i64 m = max((i64)tree[v].size(), 1L);

            auto& pqv = pqs[v];
            for (; m > 1L; --m) pqv.pop();
            i64 a = pqv.top(); pqv.pop();
            i64 b = pqv.top(); pqv.pop();
            pqv.emplace(a + c);
            pqv.emplace(b + c);

            if (pqu.size() < pqv.size()) swap(pqu, pqv);
            while (!pqv.empty()) {
                pqu.emplace(pqv.top()); pqv.pop();
            }
        }
        return y0;
    }
    else {
        pqu.emplace(0L);
        pqu.emplace(0L);
        return 0L;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M; cin >> N >> M;
    int V = N + M;
    for (int v = 2; v <= V; ++v) {
        int u, c; cin >> u >> c;
        tree[u].emplace_back(v, c);
    }

    auto& pq = pqs[1];
    i64 y0 = dfs(1);
    i64 m = tree[1].size();
    for (; m > 1L; --m) pq.pop();

    i64 x = pq.top(); pq.pop();
    while (!pq.empty()) {
        y0 += (--m) * (x - pq.top());
        x = pq.top(); pq.pop();
    }
    y0 += (--m) * x;
    cout << y0;
    return 0;
}
