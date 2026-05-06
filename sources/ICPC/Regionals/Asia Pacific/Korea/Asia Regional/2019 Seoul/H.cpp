/*
 * ICPC, Regionals, Asia Pacific, Korea,
 * Asia Regional - Seoul 2019 H. Strike Zone
 * BOJ 17975
 * JUNGOL 4391
 *
 * maximum subarray sum segment tree, sweep line
 * Date: 2023.1.6
 */

#include<bits/stdc++.h>
using namespace std;

class seg_tree {
    struct Node { int t = 0, p = 0, s = 0, a = 0; };
    vector<Node> tree;
    int N;
public:
    seg_tree(int sz) {
        for (N = 1; N < sz; N <<= 1);
        tree.resize(N<<1);
    }
    void init() {
        for (auto& node : tree) node = Node();
    }
    void add(int i, int x) {
        auto& ni = tree[i |= N];
        ni.t += x;
        ni.p += x;
        ni.s += x;
        ni.a += x;
        for (i >>= 1; i; i >>= 1) {
            auto& ni = tree[i];
            auto& nl = tree[i<<1];
            auto& nr = tree[i<<1|1];
            ni.t = nl.t + nr.t;
            ni.p = max(nl.p, nl.t + nr.p);
            ni.s = max(nr.s, nr.t + nl.s);
            ni.a = max({ nl.a, nr.a, nl.s + nr.p });
        }
    }
    int query() { return tree[1].a; }
};


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    struct Point {
        int x, y; bool s;
        Point(int x, int y, bool s): x(x), y(y), s(s) {}
    };
    vector<Point> P;

    int N1; cin >> N1;
    while (N1--) {
        int x, y; cin >> x >> y;
        P.emplace_back(x, y, true);
    }
    int N2; cin >> N2;
    while (N2--) {
        int x, y; cin >> x >> y;
        P.emplace_back(x, y, false);
    }
    int N = P.size();

    sort(P.begin(), P.end(), [](const Point& p1, const Point& p2){
        return p1.y < p2.y;
    });
    int prev_y = P[0].y;
    P[0].y = 0;
    for (int i = 1; i < N; ++i) {
        int gt = prev_y < P[i].y;
        prev_y = P[i].y;
        P[i].y = P[i-1].y + gt;
    }

    sort(P.begin(), P.end(), [](const Point& p1, const Point& p2){
        return p1.x != p2.x ? p1.x < p2.x : p1.y < p2.y;
    });

    seg_tree segt(N);
    int c1, c2; cin >> c1 >> c2;
    int ans = 0;
    for (int i = 0; i < N; ++i) {
        if (i == 0 || P[i-1].x != P[i].x) {
            segt.init();
            for (int j = i; j < N; ++j) {
                segt.add(P[j].y, P[j].s? c1 : -c2);
                if (j+1 == N || P[j].x != P[j+1].x)
                    ans = max(ans, segt.query());
            }
        }
    }

    cout << ans << '\n';
    return 0;
}
