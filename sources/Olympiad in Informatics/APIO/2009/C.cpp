/*
 * Asia-Pacific Informatics Olympiad, APIO 2009 C. The Great ATM Robbery
 * BOJ 4013
 * JUNGOL 2423
 *
 * SCC, DAG DP
 * Date: 2021.8.26
 */

#include<iostream>
#include<algorithm>
#include<bitset>
#include<set>
#include<vector>
using namespace std;

constexpr int maxN = 5e5;
vector<int> graph[maxN + 1], graph_rev[maxN + 1],
graph_scc[maxN + 1];
int scc_of[maxN + 1];
int64_t cash_scc[maxN + 1], memo[maxN + 1];
bitset<maxN + 1> visited, restaurant_scc;

void dfs(int v, vector<int> &f) {
    visited.set(v);
    for (int& u : graph[v])
        if (!visited.test(u)) dfs(u, f);
    f.push_back(v);
}
void dfs_rev(int v, int n) {
    visited.set(v);
    scc_of[v] = n;
    for (int& u : graph_rev[v])
        if (!visited.test(u)) dfs_rev(u, n);
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int N, M; cin >> N >> M;
    while (M--) {
        int x, y; cin >> x >> y;
        graph[x].push_back(y);
        graph_rev[y].push_back(x);
    }

    vector<int> f;
    for (int i = 1; i <= N; ++i)
        if (!visited.test(i)) dfs(i, f);
    visited.reset();
    int cN = 0;
    for (auto ri = f.rbegin(); ri != f.rend(); ++ri)
        if (!visited.test(*ri)) dfs_rev(*ri, ++cN);
    for (int i = 1; i <= N; ++i) {
        int ci = scc_of[i], cj;
        vector<int>& g = graph_scc[ci];
        set<int> s;
        for (int& j : graph[i]) {
            if ((cj = scc_of[j]) != ci)
                s.insert(cj);
        }
        g.reserve(g.size() + distance(s.begin(), s.end()));
        g.insert(g.end(), s.begin(), s.end());
    }

    for (int i = 1; i <= N; ++i) {
        int x; cin >> x;
        cash_scc[scc_of[i]] += x;
    }
    int S, P; cin >> S >> P;
    while (P--) {
        int x; cin >> x;
        restaurant_scc.set(scc_of[x]);
    }

    int64_t ans = 0ll;
    visited.reset();
    visited.set(scc_of[S]);
    for (int ci = scc_of[S]; ci <= cN; ++ci) {
        if (!visited.test(ci)) continue;
        memo[ci] += cash_scc[ci];
        if (restaurant_scc.test(ci))
            ans = max(ans, memo[ci]);
        for (const int& cj : graph_scc[ci]) {
            visited.set(cj);
            memo[cj] = max(memo[cj], memo[ci]);
        }
    }

    cout << ans << '\n';
    return 0;
}
