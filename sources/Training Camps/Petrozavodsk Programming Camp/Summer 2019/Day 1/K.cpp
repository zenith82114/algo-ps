/*
 * Petrozavodsk Programming Camp, Summer 2019, Day 1: Songyang Chen Contest 2 K. Monster Hunter
 * BOJ 18596 - greedy, priority queue, disjoint sets
 * Date: 2026.4.13
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;
const int MAXN = 1e5+4;

i64 a[MAXN], c[MAXN];
vector<int> gph[MAXN];
int par[MAXN];

struct task {
    i64 a, c; int id;
    bool operator<(const task& other) const {
        return make_pair(max(a, other.a - c), id) < make_pair(max(other.a, a - other.c), other.id);
    }
    bool operator>(const task& other) const { return other < *this; }
};
priority_queue<task, vector<task>, greater<>> pq;

void dfs(int x) {
    for (int y : gph[x]) if (y != par[x]) {
        par[y] = x; dfs(y);
    }
}

int dsu[MAXN];
int dsu_find(int x) {
    return !dsu[x] ? x : (dsu[x] = dsu_find(dsu[x]));
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int tc; cin >> tc;
    while (tc--) {
        int n; cin >> n;
        gph[1].clear();
        a[1] = c[1] = 0;
        for (int x = 2; x <= n; ++x) {
            gph[x].clear();
            cin >> a[x] >> c[x]; c[x] -= a[x];
            pq.push({a[x], c[x], x});
        }
        for (int i = 1; i < n; ++i) {
            int x, y; cin >> x >> y;
            gph[x].push_back(y);
            gph[y].push_back(x);
        }

        dfs(1);
        memset(dsu + 1, 0, n * sizeof(int));

        while (!pq.empty()) {
            auto [ax, cx, x] = pq.top(); pq.pop();
            if (x != dsu_find(x) || ax != a[x] || cx != c[x]) continue;

            int y = dsu_find(par[x]);
            a[y] = max(a[y], ax - c[y]);
            c[y] += cx;
            dsu[x] = y;
            if (y != 1) pq.push({a[y], c[y], y});
        }
        cout << a[1] << '\n';
    }

    return 0;
}
