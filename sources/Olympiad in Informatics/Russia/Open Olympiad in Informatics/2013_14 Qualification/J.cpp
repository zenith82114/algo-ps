/*
 * Russia Open Olympiad in Informatics Qualification 2013/2014 J. Отличная лекция
 * BOJ 30850 - offline queries, stack, segment tree
 * Date: 2024.5.27
 */

#include<bits/stdc++.h>
using namespace std;
constexpr int N = 500005;
constexpr int MAXQ = 500005;

array<vector<int>, N> adj, cyc, qt, qf;
array<int, N> pred, edge_time, vis;

array<stack<int>, MAXQ> stk;
array<int, MAXQ> ans;

vector<int> roots;

class seg_tree {
    vector<int> ar;
    int n;
public:
    void init(int sz) {
        n = 1; while (n < sz) n *= 2;
        ar.resize(2*n);
    }
    void upd(int i, int x) {
        for (ar[i |= n] = x; i > 1; i >>= 1) {
            ar[i>>1] = max(ar[i], ar[i^1]);
        }
    }
    int qry(int i, int j) {
        int ret = 0;
        for (i |= n, j |= n; i <= j; i >>= 1, j >>= 1) {
            if ( i&1) ret = max(ret, ar[i++]);
            if (~j&1) ret = max(ret, ar[j--]);
        }
        return ret;
    }
} segt;

void find_cycle(int x) {
    static int clk = 0;
    static vector<int> path;
    ++clk;
    path.clear();

    for (; !vis[x]; x = pred[x]? pred[x] : x) {
        vis[x] = clk;
        path.emplace_back(x);
    }
    if (vis[x] == clk) {
        roots.emplace_back(x);
        while (!path.empty() && path.back() != x) {
            cyc[x].emplace_back(path.back());
            path.pop_back();
        }
        // ignore trivial cycle (single node)
        if (pred[x]) cyc[x].emplace_back(x);
    }
}

void process(int x, int depth) {
    for (int i : qt[x]) {
        stk[i].emplace(depth);
    }
    for (int i : qf[x]) if (!stk[i].empty()) {
        ans[i] = min(ans[i], segt.qry(stk[i].top()+1, depth));
    }
}

void unprocess(int x) {
    for (int i : qt[x]) stk[i].pop();
}

void dfs(int x, int& depth) {
    vis[x] = true;
    process(x, depth);
    for (int y : adj[x]) {
        segt.upd(++depth, edge_time[y]);
        if (!vis[y]) dfs(y, depth);
        --depth;
    }
    unprocess(x);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    pred.fill(0);
    edge_time.fill(0);
    int m; cin >> m;
    for (int i = 1; i <= m; ++i) {
        int x, y; cin >> x >> y;
        adj[x].emplace_back(y);
        pred[y] = x;
        edge_time[y] = i;
    }

    int q; cin >> q;
    for (int i = 0; i < q; ++i) {
        ans[i] = INT32_MAX;
        int c; cin >> c;
        while (c--) {
            int x; cin >> x;
            qt[x].emplace_back(i);
        }
        cin >> c;
        while (c--) {
            int x; cin >> x;
            qf[x].emplace_back(i);
        }
    }

    vis.fill(0);
    for (int x = 1; x < N; ++x) if (!vis[x]) find_cycle(x);

    vis.fill(0);
    segt.init(2*N); // edges in cycles can be traversed twice
    int depth = 0;
    for (int x : roots) {
        for (int y : cyc[x]) {
            segt.upd(depth, edge_time[y]);
            process(y, depth++);
        }
        dfs(x, depth);
        for (int y : cyc[x]) {
            unprocess(y); --depth;
        }
    }

    for (int i = 0; i < q; ++i) {
        cout << (ans[i] == INT32_MAX? -1 : ans[i]) << '\n';
    }
    return 0;
}
