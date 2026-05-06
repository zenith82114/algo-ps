/*
 * ICPC, Regionals, Northern Eurasia,
 * Northwestern Russia Regional Contest Northern Subregional 2004 K. K-th Number
 * BOJ 7469 - persistent segment tree
 * Date: 2023.1.2
 */

#include<bits/stdc++.h>
using namespace std;

class persistent_seg_tree {
    struct Node {
        int l = -1, r = -1, val = 0;
    };
    vector<int> roots;
    vector<Node> nodes;
    int N;
    void init_util(int n, int s, int e) {
        if (s == e) return;
        nodes[n].l = nodes.size();
        nodes[n].r = nodes.size() + 1;
        nodes.emplace_back();
        nodes.emplace_back();
        int m = (s + e)>>1;
        init_util(nodes[n].l, s, m);
        init_util(nodes[n].r, m+1, e);
    }
    void insert_util(int pn, int n, int s, int e, int i) {
        if (s == e) {
            nodes[n].val++;
            return;
        }
        int m = (s + e)>>1;
        if (i <= m) {
            nodes[n].l = nodes.size();
            nodes[n].r = nodes[pn].r;
            nodes.emplace_back();
            insert_util(nodes[pn].l, nodes[n].l, s, m, i);
        }
        else {
            nodes[n].l = nodes[pn].l;
            nodes[n].r = nodes.size();
            nodes.emplace_back();
            insert_util(nodes[pn].r, nodes[n].r, m+1, e, i);
        }
        nodes[n].val = nodes[nodes[n].l].val + nodes[nodes[n].r].val;
    }
    int query_util(int n1, int n2, int s, int e, int k) {
        if (s == e) return s;
        int m = (s + e)>>1;
        int d = nodes[nodes[n2].l].val - nodes[nodes[n1].l].val;
        if (k <= d)
            return query_util(nodes[n1].l, nodes[n2].l, s, m, k);
        else
            return query_util(nodes[n1].r, nodes[n2].r, m+1, e, k - d);
    }
public:
    persistent_seg_tree(int N): N(N) {
        roots.emplace_back(0);
        nodes.emplace_back();
        init_util(0, 0, N-1);
    }
    void insert(int i) {
        int pn = roots.back();
        roots.emplace_back(nodes.size());
        nodes.emplace_back();
        insert_util(pn, roots.back(), 0, N-1, i);
    }
    int query(int i, int j, int k) {
        return query_util(roots[i-1], roots[j], 0, N-1, k);
    }
};

class Compressor {
    vector<int> ar;
public:
    Compressor(vector<int>& data): ar(data) {
        sort(ar.begin(), ar.end());
    }
    int encode(int x) {
        return lower_bound(ar.begin(), ar.end(), x) - ar.begin();
    }
    int decode(int i) { return ar[i]; }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int N, M; cin >> N >> M;
    vector<int> A(N);
    for (int& a : A) cin >> a;

    Compressor cmp(A);
    persistent_seg_tree pst(N);
    for (int& a : A) pst.insert(cmp.encode(a));

    while (M--) {
        int i, j, k; cin >> i >> j >> k;
        cout << cmp.decode(pst.query(i, j, k)) << '\n';
    }

    return 0;
}
