/*
 * 2018 KAIST 8th ACM-ICPC Mock Competition A. Coloring Roads
 * BOJ 16181 - HLD, stack
 * Date: 2024.12.30
 */

#include<bits/stdc++.h>
using namespace std;
constexpr int MAXN = 200005, MAXC = 200005;

array<vector<int>, MAXN> tree;
array<int, MAXN> par, sz, ch_no, ch_pos, ccnt;
array<stack<pair<int, int> >, MAXN> stks;
array<int, MAXC> cnt;

void dfs(int px, int x) {
    par[x] = px;
    sz[x] = 1;
    for (int y : tree[x]) if (y != px) {
        dfs(x, y);
        sz[x] += sz[y];
    }
}

void hld(int x, int cn) {
    ch_no[x] = cn;
    ch_pos[x] = (x == cn? 0 : ch_pos[par[x]] + 1);
    if (x == cn) stks[x].emplace(0, 0);
    ++(stks[cn].top().second);

    int hy = 0;
    for (int y : tree[x]) {
        if (y != par[x] && sz[hy] < sz[y]) hy = y;
    }
    if (hy) hld(hy, cn);
    for (int y : tree[x]) {
        if (y != par[x] && y != hy) hld(y, y);
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, C, Q; cin >> n >> C >> Q;
    if (n == 1) {
        while (Q--) cout << C << '\n';
        return 0;
    }

    for (int i = 1; i < n; ++i) {
        int x, y; cin >> x >> y;
        tree[x].emplace_back(y);
        tree[y].emplace_back(x);
    }
    sz[0] = 0;
    dfs(0, 1);
    hld(1, 1);
    cnt.fill(0);
    cnt[0] = n - 1;
    ccnt.fill(0);
    ccnt[0] = C;
    ccnt[n - 1] = 1;

    while (Q--) {
        int x, c, m; cin >> x >> c >> m;
        for (; x; x = par[ch_no[x]]) {
            auto& stk = stks[ch_no[x]];
            int p = ch_pos[x] + (ch_no[x] == 1? 0 : 1);
            if (!p) continue;
            int sum = 0;
            while (!stk.empty() && sum < p) {
                auto& [c2, k] = stk.top();
                int delta = min(p - sum, k);
                sum += delta;
                k -= delta;
                --ccnt[cnt[c2]];
                cnt[c2] -= delta;
                ++ccnt[cnt[c2]];
                if (!k) stk.pop();
            }
            if (!stk.empty() && stk.top().first == c) stk.top().second += p;
            else stk.emplace(c, p);
            --ccnt[cnt[c]];
            cnt[c] += p;
            ++ccnt[cnt[c]];
        }
        cout << (ccnt[m] + (cnt[0] == m? -1 : 0)) << '\n';
    }

    return 0;
}
