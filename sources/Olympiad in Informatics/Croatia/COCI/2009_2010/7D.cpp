/*
 * Croatian Open Competition in Informatics, COCI 2009/2010, Contest #7 D. SVEMIR
 * BOJ 2887
 * JUNGOL 6154
 *
 * minimum spanning tree
 * Date: 2021.8.2
 */

#include<bits/stdc++.h>
using namespace std;

struct point { int id, pos[3]; };

struct edge {
    int i, j, d;
    edge(int i, int j, int d): i(i), j(j), d(d) {};
    bool operator<(const edge& other) const {
        return d > other.d;
    };
};

class disjoint_sets {
    vector<int> ar;
public:
    disjoint_sets(int sz) : ar(sz, -1) {}
    int find(int x) {
        if (ar[x] < 0) return x;
        return ar[x] = find(ar[x]);
    }
    bool unite(int x, int y) {
        x = find(x), y = find(y);
        if (x == y) return false;
        if (ar[x] < ar[y]) ar[y] = x;
        else {
            if (ar[x] == ar[y]) --ar[y];
            ar[x] = y;
        }
        return true;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int N; cin >> N;
    vector<point> points(N);
    for (int i = 0; i < N; ++i) {
        auto& p = points[i];
        p.id = i;
        cin >> p.pos[0] >> p.pos[1] >> p.pos[2];
    }

    priority_queue<edge> pq;
    for (int d = 0; d < 3; ++d) {
        sort(points.begin(), points.end(), [d](const point& p, const point& q) {
            return p.pos[d] < q.pos[d];
        });
        for (int i = 1; i < N; ++i) {
            auto& p1 = points[i], & p2 = points[i - 1];
            pq.emplace(p1.id, p2.id, p1.pos[d] - p2.pos[d]);
        }
    }

    disjoint_sets dsu(N);
    int cnt = N - 1;
    uint64_t ans = 0;
    while (cnt) {
        auto& e = pq.top();
        if (dsu.unite(e.i, e.j)) { cnt--; ans += e.d; }
        pq.pop();
    }
    cout << ans << '\n';

    return 0;
}
