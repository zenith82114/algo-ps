/*
 * Potyczki Algorytmiczne 2011 Round 3
 * A. Journeys
 * QOJ 10381
 *
 * BFS, segment tree, disjoint sets
 * Date: 2026.6.20
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;
using ii = pair<int, int>;

const int MAXN = 5e5 +4, MAXM = 1e5 +4;

class seg_tree {
    int N;
    vector<vector<int>> _ar;

public:
    seg_tree(int sz) {
        N = 1; while (N < sz) N *= 2;
        _ar.resize(2*N);
    }

    void insert(int id, int a, int b) {
        for (a |= N, b |= N; a <= b; a >>= 1, b >>= 1) {
            if ( a&1) _ar[a++].push_back(id);
            if (~b&1) _ar[b--].push_back(id);
        }
    }

    template<typename F>
    void process(int x, F func) {
        for (x |= N; x; x >>= 1) {
            for (int id : _ar[x]) func(id);
            vector<int>().swap(_ar[x]);
        }
    }
};

class disjoint_sets {
    vector<int> _par;

public:
    disjoint_sets(int sz): _par(sz+1, -1) {}

    int lower_bound(int x) {
        return _par[x] < 0 ? x : (_par[x] = lower_bound(_par[x]));
    }

    void pop(int x) {
        assert(_par[x] < 0);
        _par[x] = x+1;
    }
};

ii intvl[2*MAXM];
int dist[MAXN];
bitset<2*MAXM> seen;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m, p; cin >> n >> m >> p;

    seg_tree segt(n+1);

    for (int i = 0; i < m; ++i) {
        int a, b, c, d; cin >> a >> b >> c >> d;
        intvl[2*i  ] = ii(a, b);
        intvl[2*i+1] = ii(c, d);
        segt.insert(2*i,   a, b);
        segt.insert(2*i+1, c, d);
    }

    memset(dist+1, 0x3f, n * sizeof(int)); dist[p] = 0;
    disjoint_sets dsu(n+1); dsu.pop(p);
    queue<int> q; q.push(p);

    while (!q.empty()) {
        int x = q.front(); q.pop();

        segt.process(x, [&](int id) {
            if (!seen[id]) {
                seen.set(id);
                auto [c, d] = intvl[id^1];
                int y = dsu.lower_bound(c);

                while (y <= d) {
                    dist[y] = dist[x] + 1;
                    dsu.pop(y);
                    q.push(y);
                    y = dsu.lower_bound(c);
                }
            }
        });
    }

    for (int x = 1; x <= n; ++x) cout << dist[x] << '\n';
    return 0;
}
