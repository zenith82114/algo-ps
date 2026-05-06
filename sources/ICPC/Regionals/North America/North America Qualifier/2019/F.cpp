/*
 * ICPC, Regionals, North America, North America Qualification Contest,
 * ICPC North America Qualifier 2019 F. Prospecting
 * BOJ 17590 - greedy, smaller to larger
 * Date: 2026.4.16
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;
const int MAXN = 2e5+4;
const i64 INF = 1e16;

int n, t;
array<i64, MAXN> req, gain;
vector<int> gph[MAXN];
int par[MAXN];

vector<int> path;
bitset<MAXN> on_path;

i64 dp(int x) {
    i64 s = 0;
    for (int y : gph[x]) s += dp(y);
    return max(req[x] - 1, -gain[x] + s);
}

i64 solve_worst_case() {
    i64 ans = req[t];
    for (int i = (int)path.size() - 2; i >= 0; --i) {
        int x = path[i];
        for (int y : gph[x]) if (!on_path[y]) ans += dp(y);
        if (i > 0) ans = max(req[x], ans - gain[x]);
    }
    return ans;
}

using task = pair<i64, i64>;
using task_pq = priority_queue<task, vector<task>, greater<>>;
task_pq pqs[MAXN];

void merge_pq(task_pq& a, task_pq& b) {
    if (a.size() < b.size()) a.swap(b);
    while (!b.empty()) { a.emplace(b.top()); b.pop(); }
}

void build_pq(int x) {
    for (int y : gph[x]) if (y != par[x]) {
        build_pq(y);
        merge_pq(pqs[x], pqs[y]);
    }

    i64 rx = req[x], gx = gain[x];
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

i64 solve_best_case() {
    build_pq(0);

    i64 hp = 0, ans = 0;
    while (!pqs[0].empty()) {
        auto [r, g] = pqs[0].top(); pqs[0].pop();
        if (hp < r) { ans += r - hp; hp = r; }
        if (g > INF/2) break;   // safe boundary to detect motherlode
        hp += g;
    }
    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;
    par[0] = -1;
    req[0] = gain[0] = 0;
    for (int x = 1; x < n; ++x) {
        cin >> par[x] >> gain[x] >> req[x];
        gph[par[x]].push_back(x);
        if (gain[x] == -1) gain[x] = INF, t = x;
        else gain[x] -= req[x];
    }

    for (int x = t; x != -1; x = par[x]) {
        path.push_back(x); on_path.set(x);
    }
    reverse(path.begin(), path.end());

    cout << solve_worst_case() << ' ';
    cout << solve_best_case();

    return 0;
}
