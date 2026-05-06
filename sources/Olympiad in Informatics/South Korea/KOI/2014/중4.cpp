/*
 * 한국정보올림피아드, KOI 2014, 중등부 4. 금광
 * BOJ 10167
 * JUNGOL 2798
 *
 * maximum subarray sum, sweep line
 * Date: 2022.7.2
 */

#include<bits/stdc++.h>
using namespace std;
using ll = long long;

class seg_tree {
    // t: total sum
    // p: max prefix sum
    // s: max suffix sum
    // a: max subarray sum
    struct Node { ll t = 0ll, p = 0ll, s = 0ll, a = 0ll; };
    vector<Node> tree;
    int N;

    void merge_nodes(Node& n, Node& ln, Node& rn) {
        n.t = ln.t + rn.t;
        n.p = max(ln.p, ln.t + rn.p);
        n.s = max(rn.s, rn.t + ln.s);
        n.a = max({ ln.a, rn.a, ln.s + rn.p });
    }
public:
    seg_tree(int sz) {
        N = sz;
        tree.resize(2 * [](int n) {
            if (n & (n-1)) {
                for (int i = 1; i < 32; i <<= 1)
                    n |= (n >> i);
                return n+1;
            }
            return n;
        }(sz));
    }
    void init() {
        for (auto& node : tree)
            node = Node();
    }
    void add(int i, ll x) {
        int n = 1, s = 0, e = N-1;
        while (s != e) {
            int m = (s+e)>>1;
            if (m < i) {
                n = (n<<1)|1;
                s = m+1;
            }
            else {
                n <<= 1;
                e = m;
            }
        }
        tree[n].t += x;
        tree[n].p += x;
        tree[n].s += x;
        tree[n].a += x;
        while (n != 1) {
            if (n & 1)
                merge_nodes(tree[n>>1], tree[n^1], tree[n]);
            else
                merge_nodes(tree[n>>1], tree[n], tree[n^1]);
            n >>= 1;
        }
    }
    ll query() { return tree[1].a; }
};

struct Point { int x, y; ll val; };

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int N; cin >> N;
    vector<Point> P(N);
    for (auto& p : P) cin >> p.x >> p.y >> p.val;

    // compress y
    sort(P.begin(), P.end(), [](const Point& lhs, const Point& rhs){
        return lhs.y < rhs.y;
    });
    int prev_y = P[0].y;
    P[0].y = 0;
    for (int i = 1; i < N; i++) {
        int gt = prev_y < P[i].y;
        prev_y = P[i].y;
        P[i].y = P[i-1].y + gt;
    }

    // sort in x, y
    sort(P.begin(), P.end(), [](const Point& lhs, const Point& rhs){
        return lhs.x != rhs.x ? lhs.x < rhs.x : lhs.y < rhs.y;
    });

    seg_tree segt(N);
    ll ans = 0ll;
    for (int l = 0; l < N; ++l) {
        if (l == 0 || P[l-1].x != P[l].x) {
            segt.init();
            for (int r = l; r < N; ++r) {
                segt.add(P[r].y, P[r].val);
                if (r+1 == N || P[r].x != P[r+1].x)
                    ans = max(ans, segt.query());
            }
        }
    }

    cout << ans << '\n';
    return 0;
}
