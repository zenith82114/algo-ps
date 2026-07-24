/*
 * Petrozavodsk Programming Camp, Winter 2023, Day 2: GP of ainta
 * D. Lonely King
 * QOJ 6538
 *
 * tree DP, Li Chao tree, smaller to larger
 * Date: 2026.7.24
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;
using ii = pair<int, int>;
const int MAXN = 2e5+4;
const i64 INF = 1e18;

struct line {
    i64 y0, m;

    line(): y0(INF), m(0) {}
    line(i64 y0, i64 m): y0(y0), m(m) {}
    i64 eval(int x) const { return y0 + m*x; };
};

struct li_chao_tree {
    struct node {
        int s, e;
        line f;
        int l = -1, r = -1;
        node(int s, int e): s(s), e(e) {}
    };
    vector<node> nodes;
    i64 y_global = 0;

    void clear(int x_min=0, int x_max=1e6) {
        nodes.clear();
        nodes.emplace_back(x_min, x_max);
    }

    size_t size() const { return nodes.size(); }

    void _insert_util(int n, line& g) {
        int s = nodes[n].s;
        int e = nodes[n].e;
        auto f1 = nodes[n].f;
        auto f2 = g;

        if (f1.eval(s) > f2.eval(s)) swap(f1, f2);
        if (f1.eval(e) <= f2.eval(e)) {
            nodes[n].f = f1;
            return;
        }

        int m = (s + e)/2;
        if (f1.eval(m) < f2.eval(m)) {
            nodes[n].f = f1;
            if (nodes[n].r == -1) {
                nodes[n].r = nodes.size();
                nodes.emplace_back(m+1, e);
            }
            _insert_util(nodes[n].r, f2);
        } else {
            nodes[n].f = f2;
            if (nodes[n].l == -1) {
                nodes[n].l = nodes.size();
                nodes.emplace_back(s, m);
            }
            _insert_util(nodes[n].l, f1);
        }
    }

    void insert(line g) { _insert_util(0, g); }

    void add_global(i64 d) { y_global += d; }

    i64 query(int x) const {
        i64 ans = INF;

        for (int n = 0; n != -1;) {
            const auto& cur = nodes[n];
            int m = (cur.s + cur.e)/2;
            ans = min(ans, cur.f.eval(x));
            n = x <= m ? cur.l : cur.r;
        }
        return ans + y_global;
    }
};

vector<int> gph[MAXN];
int C[MAXN];
i64 temp[MAXN];
li_chao_tree lct[MAXN];

void dfs(int px, int x) {
    if (gph[x].size() == 1) {
        lct[x].insert(line(0, C[x]));
        return;
    }

    i64 gx = 0;
    for (int y : gph[x]) if (y != px) {
        dfs(x, y);
        gx += (temp[y] = lct[y].query(C[x]));
    }
    for (int y : gph[x]) if (y != px) lct[y].add_global(gx - temp[y]);

    int hy = 0;
    for (int y : gph[x]) if (y != px) {
        if (!hy || lct[hy].size() < lct[y].size()) hy = y;
    }
    lct[x] = std::move(lct[hy]);
    for (int y : gph[x]) if (y != px && y != hy) {
        for (const auto& nd : lct[y].nodes) {
            line f = nd.f;
            f.y0 += lct[y].y_global - lct[x].y_global;
            lct[x].insert(f);
        }
        lct[y].clear();
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n; cin >> n;
    for (int x = 2; x <= n; ++x) {
        int px; cin >> px;
        gph[px].push_back(x);
        gph[x].push_back(px);
    }
    for (int x = 1; x <= n; ++x) cin >> C[x], lct[x].clear();

    i64 ans = 0;
    for (int y : gph[1]) {
        dfs(1, y);
        ans += lct[y].query(C[1]);
    }
    cout << ans;
    return 0;
}
