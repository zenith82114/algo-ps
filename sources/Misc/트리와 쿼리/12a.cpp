/*
 * 트리와 쿼리 12
 * QOJ 18815
 *
 * offline dynamic connectivity (sqrt decomposition)
 * Date: 2026.3.6
 *
 * Works for general graphs too. (BOJ 16911)
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;
using ii = pair<int, int>;
constexpr int MAXN = 1e5 + 4, MAXM = 1e5;

class disjoint_sets {
    int ar[MAXN];

public:
    void reset(int n) { fill(ar, ar + n + 1, -1); }
    int find(int x) {
        return ar[x] < 0 ? x : (ar[x] = find(ar[x]));
    }
    void unite(int x, int y) {
        x = find(x); y = find(y);
        if (x == y) return;
        if (ar[x] > ar[y]) swap(x, y);
        ar[x] += ar[y]; ar[y] = x;
    }
    bool query(int x, int y) { return find(x) == find(y); }
} dsu;

struct query { int type, x, y, eid; };
vector<query> queries;
vector<ii> edges;
bitset<MAXM> active, dynamic;
vector<ii> gph[MAXN];
bitset<MAXN> seen;

int dfs(int x, int t, vector<int>& dirty) {
    if (x == t) return true;
    seen.set(x);
    dirty.push_back(x);
    for (auto [y, j] : gph[x]) {
        if (!seen[y] && active[j]) {
            if (dfs(y, t, dirty)) return 1;
        }
    }
    return 0;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m; cin >> n >> m;
    queries.resize(m);
    for (auto& q : queries) {
        cin >> q.type >> q.x >> q.y;
        if (q.x > q.y) swap(q.x, q.y);
        if (q.type == 1) edges.emplace_back(q.x, q.y);
    }
    sort(begin(edges), end(edges));
    edges.erase(unique(begin(edges), end(edges)), end(edges));

    for (auto& q : queries) if (q.type != 3) {
        q.eid = lower_bound(begin(edges), end(edges), ii(q.x, q.y)) - begin(edges);
    }

    const int bsz = (int)round(sqrt(m + .5));
    for (int base = 0; base < m; base += bsz) {
        for (int i = base; i < min(base + bsz, m); ++i) {
            auto& q = queries[i];
            if (q.type != 3) dynamic.set(q.eid);
        }

        dsu.reset(n);
        for (size_t j = 0; j < edges.size(); ++j) if (active[j] && !dynamic[j]) {
            auto& [x, y] = edges[j];
            dsu.unite(x, y);
        }

        for (int i = base; i < min(base + bsz, m); ++i) {
            auto& q = queries[i];
            if (q.type != 3) {
                if (dynamic[q.eid]) {
                    gph[dsu.find(q.x)].emplace_back(dsu.find(q.y), q.eid);
                    gph[dsu.find(q.y)].emplace_back(dsu.find(q.x), q.eid);
                }
            }
        }

        for (int i = base; i < min(base + bsz, m); ++i) {
            auto& q = queries[i];
            if (q.type == 1) active.set(q.eid);
            else if (q.type == 2) active.reset(q.eid);
            else {
                vector<int> dirty;
                int res = dfs(dsu.find(q.x), dsu.find(q.y), dirty);
                for (int x : dirty) seen.reset(x);
                cout << res << '\n';
            }
        }

        for (int i = base; i < min(base + bsz, m); ++i) {
            auto& q = queries[i];
            if (q.type != 3) {
                dynamic.reset(q.eid);
                gph[dsu.find(q.x)].clear();
                gph[dsu.find(q.y)].clear();
            }
        }
    }

    return 0;
}
