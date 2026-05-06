/*
 * ICPC, Regionals, Asia Pacific, Korea,
 * Seoul Nationalwide Internet Competition 2019 J. Star Trek
 * BOJ 17526
 *
 * Li Chao tree
 * Date: 2023.1.9
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;
constexpr i64 inf = INT64_MAX;

struct Line {
    i64 y0, m;
    Line(): y0(inf), m(0ll) {}
    Line(i64 y0, i64 m): y0(y0), m(m) {}
    i64 eval(int x) const { return y0 + m * x; };
};

class LiChaoTree {
    struct Node {
        int s, e;
        Line f;
        int l = -1, r = -1;
        Node(int s, int e): s(s), e(e) {}
    };
    vector<Node> nodes;

    void insert_util(int n, Line& g) {
        int s = nodes[n].s;
        int e = nodes[n].e;
        auto f1 = nodes[n].f;
        auto f2 = g;

        if (f1.eval(s) > f2.eval(s)) swap(f1, f2);
        if (f1.eval(e) <= f2.eval(e)) {
            nodes[n].f = f1;
            return;
        }

        int m = (s + e)>>1;
        if (f1.eval(m) < f2.eval(m)) {
            nodes[n].f = f1;
            if (nodes[n].r == -1) {
                nodes[n].r = nodes.size();
                nodes.emplace_back(m+1, e);
            }
            insert_util(nodes[n].r, f2);
        }
        else {
            nodes[n].f = f2;
            if (nodes[n].l == -1) {
                nodes[n].l = nodes.size();
                nodes.emplace_back(s, m);
            }
            insert_util(nodes[n].l, f1);
        }
    }
public:
    LiChaoTree(int s, int e) {
        nodes.emplace_back(s, e);
    }
    void insert(Line& g) { insert_util(0, g); }
    i64 query(int x) {
        i64 ans = inf;
        int n = 0;
        while (n != -1) {
            const auto& cur = nodes[n];
            int m = (cur.s + cur.e)>>1;
            ans = min(ans, cur.f.eval(x));
            n = x <= m? cur.l : cur.r;
        }
        return ans;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int N; cin >> N;
    vector<int> x(N+1, 0);
    for (int i = 2; i <= N; ++i) cin >> x[i];
    partial_sum(x.begin(), x.end(), x.begin());

    vector<int> p(N), s(N);
    for (int i = 1; i < N; ++i) cin >> p[i] >> s[i];

    LiChaoTree lct(0, x[N]);
    i64 dp = 0ll;
    for (int i = 1; i < N; ++i) {
        Line ln(dp + p[i] - (i64)s[i] * x[i], s[i]);
        lct.insert(ln);
        dp = lct.query(x[i+1]);
    }
    cout << dp << '\n';

    return 0;
}
