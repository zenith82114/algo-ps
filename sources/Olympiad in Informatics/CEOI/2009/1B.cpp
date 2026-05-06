/*
 * Central Europe Olympiad in Informatics, CEOI 2009, Day 1 B. harbingers
 * BOJ 3319
 * JUNGOL 4982
 *
 * persistent Li Chao tree
 * Date: 2024.3.8
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;
constexpr i64 inf = INT64_MAX;

struct Line {
    i64 y0, m;
    Line(): y0(inf), m(0ll) {}
    Line(i64 y0, i64 m): y0(y0), m(m) {}
    i64 eval(int x) const { return y0 + m*x; };
};

class LiChaoTree {
    struct Node {
        Line f;
        int s, e, l, r;
        Node(int s, int e): s(s), e(e), l(-1), r(-1) {}
    };
    int S, E;
    vector<int> roots;
    vector<Node> nodes;

    void insert_util(int pn, int n, Line& g) {
        if (pn != -1) nodes[n] = nodes[pn];

        int s = nodes[n].s;
        int e = nodes[n].e;
        auto f1 = nodes[n].f;
        auto f2 = g;

        if (f1.eval(s) > f2.eval(s)) swap(f1, f2);
        if (f1.eval(e) <= f2.eval(e)) {
            nodes[n].f = f1;
            return;
        }

        int mid = (s + e)>>1;
        if (f1.eval(mid) < f2.eval(mid)) {
            nodes[n].f = f1;
            nodes[n].r = nodes.size();
            nodes.emplace_back(mid+1, e);
            insert_util(pn == -1? -1 : nodes[pn].r, nodes[n].r, f2);
        } else {
            nodes[n].f = f2;
            nodes[n].l = nodes.size();
            nodes.emplace_back(s, mid);
            insert_util(pn == -1? -1 : nodes[pn].l, nodes[n].l, f1);
        }
    }
public:
    LiChaoTree(int S, int E): S(S), E(E) {
        roots.emplace_back(0);
        nodes.emplace_back(S, E);
    }
    void insert(i64 y0, i64 m) {
        int pn = roots.back();
        roots.emplace_back(nodes.size());
        int n = roots.back();
        nodes.emplace_back(S, E);
        Line g(y0, m);
        insert_util(pn, n, g);
    }
    i64 query(int x) {
        i64 ans = inf;
        int n = roots.back();
        while (n != -1) {
            const auto& [f, s, e, l, r] = nodes[n];
            int mid = (s + e)>>1;
            ans = min(ans, f.eval(x));
            n = x <= mid? l : r;
        }
        return ans;
    }
    void pop() {
        while (roots.back() < (int)nodes.size()) nodes.pop_back();
        roots.pop_back();
    }
};

array<vector<pair<int, int> >, 100005> adj;
array<int, 100005> S, V;
array<i64, 100005> ans;

void dfs(int px, int x, int dep, LiChaoTree& lct) {
    if (x != 1) {
        ans[x] = S[x] + (i64)dep*V[x] + lct.query(V[x]);
    }
    lct.insert(ans[x], -dep);

    for (const auto& [y, w] : adj[x]) if (y != px) {
        dfs(x, y, dep+w, lct);
    }
    lct.pop();
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n; cin >> n;
    for (int i = 1; i < n; ++i) {
        int x, y, w; cin >> x >> y >> w;
        adj[x].emplace_back(y, w);
        adj[y].emplace_back(x, w);
    }
    S[1] = V[1] = 0;
    for (int x = 2; x <= n; ++x) cin >> S[x] >> V[x];

    LiChaoTree lct(0, 1'000'000'000);
    ans[1] = 0;
    dfs(0, 1, 0, lct);
    for (int x = 2; x <= n; ++x) cout << ans[x] << ' ';
    return 0;
}
