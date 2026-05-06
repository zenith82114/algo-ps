/*
 * 한국정보올림피아드, 지역본선 2015, 고등부 4. 공중도시
 * BOJ 10806
 * JUNGOL 2865
 *
 * bridges, greedy
 * Date: 2023.8.22
 */

#include<bits/stdc++.h>
using namespace std;

class disjoint_sets {
    vector<int> ar;
public:
    void init(int n) { ar.resize(n, -1); }
    int find(int x) {
        if (ar[x] < 0) return x;
        return ar[x] = find(ar[x]);
    }
    void unite(int x, int y) {
        x = find(x), y = find(y);
        if (x == y) return;
        if (ar[x] == ar[y]) ar[x]--;
        if (ar[x] > ar[y]) swap(x, y);
        ar[y] = x;
    }
} dsu;

vector<pair<int, int> > edges;
vector<pair<int, int> > graph[100'001];
int dfn[100'001] {}, low[100'001] {};
int clk = 0;
bool is_bridge[200'000] {};

vector<int> tree[100'001];
vector<int> leaves;

void dfs_graph(int pid, int x) {
    dfn[x] = low[x] = ++clk;
    for (const auto& [y, id] : graph[x]) if (id != pid) {
        if (!dfn[y]) {
            dfs_graph(id, y);
            low[x] = min(low[x], low[y]);
            if (dfn[x] < low[y]) is_bridge[id] = true;
        } else {
            low[x] = min(low[x], dfn[y]);
        }
    }
}

void dfs_tree(int px, int x) {
    if (tree[x].size() == 1u) leaves.emplace_back(x);
    for (int y : tree[x]) if (y != px) dfs_tree(x, y);
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);

    int n, m; cin >> n >> m;
    for (int id = 0; id < m; ++id) {
        int x, y; cin >> x >> y;
        edges.emplace_back(x, y);
        graph[x].emplace_back(y, id);
        graph[y].emplace_back(x, id);
    }

    dsu.init(n+1);
    dfs_graph(-1, 1);
    for (int id = 0; id < m; ++id) if (!is_bridge[id]) {
        const auto& [x, y] = edges[id];
        dsu.unite(x, y);
    }
    for (auto [x, y] : edges) {
        x = dsu.find(x), y = dsu.find(y);
        if (x == y) continue;
        tree[x].emplace_back(y);
        tree[y].emplace_back(x);
    }
    dfs_tree(0, dsu.find(1));

    int k = leaves.size();
    cout << (k+1)/2;
    for (int i = 0; i < k/2; ++i) {
        cout << '\n' << leaves[i] << ' ' << leaves[i + k/2];
    }
    if (k&1) {
        cout << '\n' << leaves.front() << ' ' << leaves.back();
    }
    return 0;
}
