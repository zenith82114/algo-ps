/*
 * Croatian Open Competition in Informatics, COCI 2011/2012, Contest #3 E. PLAĆE
 * BOJ 2820
 * JUNGOL 8336
 *
 * segment tree, Euler tour technique
 * Date: 2022.2.10
 */

#include<bits/stdc++.h>
using namespace std;

vector<int> ini, etr;
vector<vector<int>> adj;
vector<pair<int, int>> seg;

void dfs(int pu, int u, int& cnt) {
    etr[cnt] = ini[u];
    seg[u].first = cnt++;
    for (int& v : adj[u]) {
        if (v != pu)
            dfs(u, v, cnt);
    }
    etr[cnt] = ini[u];
    seg[u].second = cnt++;
}

class seg_tree {
    int N;
    vector<int> A;
    int lc(int n) { return n<<1; }
    int rc(int n) { return n<<1 | 1; }
    void add_seg_util(int n, int l, int r, int i, int j, int x) {
        if (l != i || r != j) {
            int m = (l + r) / 2;
            if (j <= m)
                add_seg_util(lc(n), l, m, i, j, x);
            else if (m < i)
                add_seg_util(rc(n), m+1, r, i, j, x);
            else {
                add_seg_util(lc(n), l, m, i, m, x);
                add_seg_util(rc(n), m+1, r, m+1, j, x);
            }
        }
        else A[n] += x;
    }
public:
    void init(vector<int>& etr) {
        N = etr.size();
        int sz = 1;
        while (sz < N) sz <<= 1;
        A.assign(sz<<1, 0);
        for (int i = 0; i < N; ++i) {
            int n = 1, l = 0, r = N-1;
            while (l < r) {
                int m = (l + r) / 2;
                if (m < i) {
                    n = rc(n);
                    l = m+1;
                }
                else {
                    n = lc(n);
                    r = m;
                }
            }
            A[n] = etr[i];
        }
    }
    void add_seg(int i, int j, int x) {
        if (i > j) return;
        add_seg_util(1, 0, N-1, i, j, x);
    }
    int query(int i) {
        int n = 1, l = 0, r = N-1;
        int ret = A[1];
        while (l < r) {
            int m = (l + r) / 2;
            if (m < i) {
                n = rc(n);
                l = m+1;
            }
            else {
                n = lc(n);
                r = m;
            }
            ret += A[n];
        }
        return ret;
    }
} segt;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int N, M; cin >> N >> M;
    ini.resize(N+1);
    adj.resize(N+1);
    cin >> ini[1];
    for (int v = 2; v <= N; ++v) {
        int w; cin >> ini[v] >> w;
        adj[v].emplace_back(w);
        adj[w].emplace_back(v);
    }

    etr.resize(N<<1);
    seg.resize(N+1);
    int cnt = 0;
    dfs(0, 1, cnt);

    segt.init(etr);
    while (M--) {
        char c; cin >> c;
        int v, x;
        if (c == 'p') {
            cin >> v >> x;
            segt.add_seg(seg[v].first+1, seg[v].second-1, x);
        }
        else if (c == 'u') {
            cin >> v;
            cout << segt.query(seg[v].first) << '\n';
        }
    }

    return 0;
}
