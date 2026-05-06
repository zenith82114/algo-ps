/*
 * ICPC, Regionals, Europe, Central Europe Regional Contest,
 * CERC 2013 E. Escape
 * JUNGOL 2771
 *
 * greedy, smaller to larger
 * Date: 2026.4.10
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;
using task = pair<i64, i64>;
using task_pq = priority_queue<task, vector<task>, greater<>>;
const int MAXN = 2e5 + 4;

int wgt[MAXN];
vector<int> gph[MAXN];
vector<int> path;
bitset<MAXN> on_path;
task_pq pqs[MAXN];

void get_path(int px, int x) {
    if (x == 1) { path.push_back(1); on_path.set(1); return; }
    for (int y : gph[x]) if (y != px) {
        get_path(x, y);
        if (!path.empty()) { path.push_back(x); on_path.set(x); return; }
    }
}

void merge_pq(task_pq& a, task_pq& b) {
    if (a.size() < b.size()) a.swap(b);
    while (!b.empty()) { a.emplace(b.top()); b.pop(); }
}

void build_pq(int px, int x) {
    for (int y : gph[x]) if (y != px) {
        build_pq(x, y);
        merge_pq(pqs[x], pqs[y]);
    }

    i64 rx = max(0, -wgt[x]);
    i64 gx = wgt[x];
    while (!pqs[x].empty()) {
        auto [r, g] = pqs[x].top();
        if (gx <= 0 || rx + gx >= r) {
            rx = max(rx, r - gx);
            gx += g;
            pqs[x].pop();
        } else break;
    }
    if (gx > 0) pqs[x].emplace(rx, gx);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, t; cin >> n >> t;
    for (int x = 1; x <= n; ++x) cin >> wgt[x];
    for (int i = 1; i < n; ++i) {
        int x, y; cin >> x >> y;
        gph[x].push_back(y);
        gph[y].push_back(x);
    }

    get_path(0, t);

    task_pq pq;
    i64 hp = wgt[1];
    bool ans = true;

    for (size_t i = 0; i < path.size() - 1; ++i) {
        for (int y : gph[path[i]]) if (!on_path[y]) {
            build_pq(path[i], y);
            merge_pq(pq, pqs[y]);
        }
        while (!pq.empty()) {
            auto [r, g] = pq.top();
            if (r <= hp) { hp += g; pq.pop(); }
            else break;
        }
        hp += wgt[path[i + 1]];
        if (hp < 0) { ans = false; break; }
    }
    cout << (ans ? "escaped" : "trapped");

    return 0;
}
