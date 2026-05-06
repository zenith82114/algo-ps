/*
 * ICPC, Regionals, Asia Pacific, Thailand,
 * 2013 ACM-ICPC Thailand National Programming Contest G. DVDs
 * BOJ 9345 - segment tree
 * Date: 2021.8.30
 */

#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
typedef unsigned long long ull;

class seg_tree {
    const ull MAXMASK = (1LL << 32) - 1, MINMASK = ~MAXMASK;
    int N;
    vector<int> I;
    vector<ull> A;
    int lc(int n) { return n << 1; }
    int rc(int n) { return n << 1 | 1; }
    ull pack(ull x, ull y) {
        ull z1 = min(x & MINMASK, y & MINMASK),
            z2 = max(x & MAXMASK, y & MAXMASK);
        return z1 | z2;
    }
    void init(int n, int l, int r) {
        A[n] = (ull)l << 32 | r;
        if (l < r) {
            int m = (l + r) / 2;
            init(lc(n), l, m);
            init(rc(n), m + 1, r);
            A[n] = pack(A[lc(n)], A[rc(n)]);
        }
        else I[l] = n;
    }
    void update(int n, ull x) {
        while (n && A[n] != x) {
            A[n] = x;
            x = pack(x, A[n ^ 1]);
            n >>= 1;
        }
    }
    ull query_util(int n, int l, int r, int i, int j) {
        if (l == i && r == j) return A[n];
        int m = (l + r) / 2;
        if (i > m)
            return query_util(rc(n), m + 1, r, i, j);
        if (j <= m)
            return query_util(lc(n), l, m, i, j);
        return pack(query_util(rc(n), m + 1, r, m + 1, j),
                    query_util(lc(n), l, m, i, m));
    }
public:
    seg_tree(int n) {
        N = n;
        I.resize(n);
        int sz = 1;
        while (sz < n) sz <<= 1;
        A.resize(sz<<1);
        init(1, 0, n - 1);
    }
    void swap(int i, int j) {
        ull tmp = A[I[i]];
        update(I[i], A[I[j]]);
        update(I[j], tmp);
    }
    bool query(int i, int j) {
        ull res = query_util(1, 0, N - 1, i, j);
        return res == ((ull)i << 32 | j);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int TC; cin >> TC;
    while (TC--) {
        int N, K; cin >> N >> K;
        seg_tree segt(N);
        while (K--) {
            int q, a, b; cin >> q >> a >> b;
            if (q)
                cout << (segt.query(a, b) ? "YES\n" : "NO\n");
            else segt.swap(a, b);
        }
    }

    return 0;
}
