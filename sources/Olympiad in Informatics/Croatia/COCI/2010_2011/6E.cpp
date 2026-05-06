/*
 * Croatian Open Competition in Informatics, COCI 2010/2011, Contest #6 E. STEP
 * BOJ 2849
 * JUNGOL 2438
 *
 * maximum subarray sum segment tree
 * Date: 2023.7.10
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;

class seg_tree {
    struct Node {
        i64 t, p, s, a;
        Node(int x): t(x), p(x), s(x), a(x) {}
    };
    vector<Node> ar;
    int N;
    void pull(int i) {
        auto& n = ar[i];
        auto& l = ar[i<<1];
        auto& r = ar[i<<1|1];
        n.t = l.t + r.t;
        n.p = max(l.p, l.t + r.p);
        n.s = max(l.s + r.t, r.s);
        n.a = max({ l.a, r.a, l.s + r.p });
    }
public:
    seg_tree(int sz, int b) {
        N = 1; while (N < sz) N <<= 1;
        ar.resize(N<<1, -N);
        for (int i = b; i < sz; i += 2) ar[N|i] = Node(1);
        for (int i = N-1; i; --i) pull(i);
    }
    void flip(int i) {
        i |= N; ar[i] = Node(ar[i].t == 1? -N : 1);
        for (i >>= 1; i; i >>= 1) pull(i);
    }
    i64 query() { return ar[1].a; }
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);

    int N, Q; cin >> N >> Q;
    seg_tree segt1(N+1, 1), segt2(N+1, 2);
    while (Q--) {
        int i; cin >> i;
        segt1.flip(i); segt2.flip(i);
        cout << max(segt1.query(), segt2.query()) << '\n';
    }

    return 0;
}
