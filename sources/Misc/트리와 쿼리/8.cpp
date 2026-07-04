/*
 * 트리와 쿼리 8
 * QOJ 18811
 *
 * LCA (sparse table), persistent segment tree
 * Date: 2023.1.2
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;
using ii = pair<int, int>;

class persistent_seg_tree {
    const int MAX_WEIGHT = 1e6;

    int N, lgN;
    struct node { int l = -1, r = -1, val = 0; };
    vector<int> roots;
    vector<node> nodes;
    vector<int> depth;
    vector<vector<int>> parent;

    void init_util(int u, int s, int e) {
        if (s == e) return;
        nodes[u].l = nodes.size();
        nodes[u].r = nodes.size() + 1;
        nodes.emplace_back();
        nodes.emplace_back();
        int m = (s + e)/2;
        init_util(nodes[u].l, s, m);
        init_util(nodes[u].r, m+1, e);
    }
    void insert_util(int pu, int u, int s, int e, int i) {
        if (s == e) {
            nodes[u].val = nodes[pu].val + 1;
            return;
        }
        int m = (s + e)/2;
        if (i <= m) {
            nodes[u].l = nodes.size();
            nodes[u].r = nodes[pu].r;
            nodes.emplace_back();
            insert_util(nodes[pu].l, nodes[u].l, s, m, i);
        }
        else {
            nodes[u].l = nodes[pu].l;
            nodes[u].r = nodes.size();
            nodes.emplace_back();
            insert_util(nodes[pu].r, nodes[u].r, m+1, e, i);
        }
        nodes[u].val = nodes[nodes[u].l].val + nodes[nodes[u].r].val;
    }
    void dfs(int px, int x, const vector<vector<int>>& tree, const vector<int>& weights) {
        for (int y : tree[x]) if (y != px) {
            roots[y] = nodes.size();
            nodes.emplace_back();
            insert_util(roots[x], roots[y], 0, MAX_WEIGHT, weights[y]);
            depth[y] = depth[x] + 1;
            parent[0][y] = x;
            dfs(x, y, tree, weights);
        }
    }
    int query_util(int u1, int u2, int u3, int u4, int s, int e, int k) {
        if (s == e) return s;
        int m = (s + e)/2;
        int d = nodes[nodes[u1].l].val + nodes[nodes[u2].l].val
                - nodes[nodes[u3].l].val - nodes[nodes[u4].l].val;
        if (k <= d)
            return query_util(nodes[u1].l, nodes[u2].l, nodes[u3].l, nodes[u4].l, s, m, k);
        else
            return query_util(nodes[u1].r, nodes[u2].r, nodes[u3].r, nodes[u4].r, m+1, e, k - d);
    }

public:
    persistent_seg_tree(const vector<vector<int>>& tree, const vector<int>& weights) {
        N = tree.size() - 1;
        lgN = [](int n) {
            int k = 0;
            for (; n > 1; n >>= 1) k++;
            return k;
        }(N);

        roots.resize(N+1, 0);
        nodes.emplace_back();
        init_util(0, 0, MAX_WEIGHT);

        roots[1] = nodes.size();
        nodes.emplace_back();
        insert_util(roots[0], roots[1], 0, MAX_WEIGHT, weights[1]);

        depth.resize(N+1, 0);
        parent.resize(lgN+1, vector<int>(N+1, -1));
        dfs(0, 1, tree, weights);

        for (int i = 1; i <= lgN; ++i)
        for (int x = 2; x <= N; ++x) if (parent[i-1][x] > 0) {
            parent[i][x] = parent[i-1][parent[i-1][x]];
        }
    }
    int query(int x, int y, int k) {
        int a = x, b = y;
        if (depth[a] < depth[b]) swap(a, b);
        for (int d = depth[a] - depth[b], k = 0; d; d >>= 1, ++k) {
            if (d&1) a = parent[k][a];
        }

        if (a != b) {
            for (int k = lgN; k > -1; --k) if (parent[k][a] != parent[k][b]) {
                a = parent[k][a];
                b = parent[k][b];
            }
            a = parent[0][a];
        }
        int pa = a != 1? parent[0][a] : 0;
        return query_util(roots[x], roots[y], roots[a], roots[pa], 0, MAX_WEIGHT, k);
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n; cin >> n;
    vector<int> weights(n+1);
    for (int i = 1; i <= n; ++i) cin >> weights[i];

    vector<vector<int>> tree(n+1);
    for (int i = 1; i < n; ++i) {
        int x, y; cin >> x >> y;
        tree[x].push_back(y);
        tree[y].push_back(x);
    }

    persistent_seg_tree psegt(tree, weights);

    int m; cin >> m;
    while (m--) {
        int x, y, k; cin >> x >> y >> k;
        cout << psegt.query(x, y, k) << '\n';
    }
    return 0;
}
