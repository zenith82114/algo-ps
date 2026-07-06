/*
 * 트리와 쿼리 4
 * QOJ 18807
 *
 * LCA (RMQ on Euler tour), centroid DnC, priority queue
 * Date: 2026.7.6
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;
using ii = pair<int, int>;

const int MAXN = 1e5 +4, INF = 1e9;

int n, N;
array<vector<pair<int, int> >, MAXN> gph;
vector<int> eut;
array<int, MAXN> dep, lvl, vis;

void make_eut(int px, int x) {
    vis[x] = eut.size();
    eut.push_back(x);

    for (auto [y, w] : gph[x]) if (y != px) {
        dep[y] = dep[x] + w;
        lvl[y] = lvl[x] + 1;
        make_eut(x, y);
        eut.push_back(x);
    }
}

int get_dist(int x, int y) {
    int l = vis[x], r = vis[y];
    if (l > r) swap(l, r);

    int lca = 0;
    for (l |= N, r |= N; l <= r; l >>= 1, r >>= 1) {
        if (l&1) {
            if (lvl[lca] > lvl[eut[l]]) lca = eut[l];
            ++l;
        }
        if (~r&1) {
            if (lvl[lca] > lvl[eut[r]]) lca = eut[r];
            --r;
        }
    }
    return dep[x] + dep[y] - 2*dep[lca];
}

array<int, MAXN> sz, ct_par;
bitset<MAXN> sel;

int get_sz(int px, int x) {
    sz[x] = 1;
    for (auto [y, w] : gph[x]) if (y != px && !sel[y]) {
        sz[x] += get_sz(x, y);
    }
    return sz[x];
}

int get_ct(int px, int x, int m) {
    for (auto [y, w] : gph[x]) {
        if (y != px && !sel[y] && sz[y] > m) {
            return get_ct(x, y, m);
        }
    }
    return x;
}

void make_ct_tree(int pc, int x) {
    int k = get_sz(pc, x);
    int c = get_ct(pc, x, k/2);
    ct_par[c] = pc;
    sel.set(c);
    for (auto [y, w] : gph[c]) if (!sel[y]) make_ct_tree(c, y);
}

class max_heap {
    priority_queue<int> heap, lazy;

    void _sync() {
        while (!heap.empty() && !lazy.empty() && heap.top() == lazy.top()) {
            heap.pop(); lazy.pop();
        }
    }

public:
    void push(int x) { heap.push(x); }
    void erase(int x) { lazy.push(x); }
    int top() { _sync(); return heap.top(); }
    void pop() { _sync(); heap.pop(); }
    size_t size() { return heap.size() - lazy.size(); }
};

// subtree_dists[c] = { dist(pc, x)
//                         ; pc is parent centroid of c
//                         ; x is a white vertex in CT(c) }
// max_dists[pc] = { max(subtree_dists[c]) ; pc is parent centroid of c }
array<max_heap, MAXN> subtree_dists, max_dists;

// { max_path(x) ; for all x }
max_heap max_paths;

bitset<MAXN> white;
int white_cnt;

int max_path(int c) {
    int ans = -INF;

    if (max_dists[c].size() > 1) {
        int top1 = max_dists[c].top(); max_dists[c].pop();
        int top2 = max_dists[c].top(); max_dists[c].push(top1);
        ans = max(ans, top1 + top2);
    }
    if (white[c]) ans = max(ans, 0);

    return ans;
}

void init() {
    for (int x = 1; x <= n; ++x) {
        for (int c = x, pc = ct_par[x]; pc != 0; c = pc, pc = ct_par[pc]) {
            subtree_dists[c].push(get_dist(pc, x));
        }
    }

    for (int c = 1; c <= n; ++c) {
        max_dists[c].push(0);

        int pc = ct_par[c];
        if (pc) max_dists[pc].push(subtree_dists[c].top());
    }

    white.set();
    white_cnt = n;

    for (int c = 1; c <= n; ++c) max_paths.push(max_path(c));
}

void toggle(int x) {
    for (int c = x; c != 0; c = ct_par[c]) max_paths.erase(max_path(c));

    white.flip(x);
    white_cnt += white[x] ? 1 : -1;

    if (white[x]) max_dists[x].push(0);
    else max_dists[x].erase(0);

    for (int c = x, pc = ct_par[x]; pc != 0; c = pc, pc = ct_par[pc]) {
        if (subtree_dists[c].size() > 0) max_dists[pc].erase(subtree_dists[c].top());

        int d = get_dist(pc, x);
        if (white[x]) subtree_dists[c].push(d);
        else subtree_dists[c].erase(d);

        if (subtree_dists[c].size() > 0) max_dists[pc].push(subtree_dists[c].top());
    }

    for (int c = x; c != 0; c = ct_par[c]) max_paths.push(max_path(c));
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;
    for (int i = 1; i < n; ++i) {
        int x, y, w; cin >> x >> y >> w;
        gph[x].emplace_back(y, w);
        gph[y].emplace_back(x, w);
    }

    dep[1] = 0;
    lvl[1] = 0;
    make_eut(0, 1);

    N = eut.size();
    while (N & (N-1)) N += N & (-N);
    eut.resize(2*N);
    copy(eut.begin(), eut.begin() + N, eut.begin() + N);
    lvl[0] = INF;

    for (int i = N-1; i > 0; --i) {
        int x = eut[2*i], y = eut[2*i+1];
        eut[i] = lvl[x] < lvl[y]? x : y;
    }

    make_ct_tree(0, 1);
    init();

    int q; cin >> q;
    while (q--) {
        int op; cin >> op;

        if (op&1) { int x; cin >> x; toggle(x); }
        else cout << (white_cnt? max_paths.top() : -1) << '\n';
    }

    return 0;
}
