/*
 * 트리와 쿼리 5
 * QOJ 18808
 *
 * LCA (HLD), centroid DnC
 * Date: 2022.2.20
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;
using ii = pair<int, int>;
const int MAXN = 1e5 +4, INF = 1e9;

vector<int> gph[MAXN];
array<int, MAXN> par, sz, dep, ch_id, ch_dep, ch_pos, ct_par;
bitset<MAXN> sel, white;
priority_queue<ii, vector<ii>, greater<ii>> pqs[MAXN];

int dfs_hld(int px, int x) {
    par[x] = px;
    sz[x] = 1;
    dep[x] = dep[px] + 1;

    for (int y : gph[x]) if (y != px) sz[x] += dfs_hld(x, y);
    return sz[x];
}

void hld(int x, int ci, int cd, int cp) {
    ch_id[x] = ci;
    ch_dep[x] = cd;
    ch_pos[x] = cp;

    int hv = 0;
    for (int y : gph[x]) if (y != par[x] && (!hv || sz[y] > sz[hv])) hv = y;
    if (hv) hld(hv, ci, cd, cp+1);
    for (int y : gph[x]) if (y != par[x] && y != hv) hld(y, y, cd+1, 0);
}

int get_dist(int x, int y) {
    int d = dep[x] + dep[y];
    while (ch_id[x] != ch_id[y]) {
        if (ch_dep[x] < ch_dep[y]) swap(x, y);
        x = par[ch_id[x]];
    }
    int lca = ch_pos[x] < ch_pos[y] ? x : y;
    return d - 2*dep[lca];
}

int dfs_ctd(int px, int x) {
    sz[x] = 1;
    for (int y : gph[x]) if (y != px && !sel[y]) sz[x] += dfs_ctd(x, y);
    return sz[x];
}

int ct(int px, int x, int m) {
    for (int y : gph[x]) if (y != px && !sel[y] && sz[y] > m) return ct(x, y, m);
    return x;
}

void ctd(int pc, int x) {
    int n = dfs_ctd(pc, x);
    int c = ct(pc, x, n/2);
    ct_par[c] = pc;
    sel[c] = true;
    for (int y : gph[c]) if (!sel[y]) ctd(c, y);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n; cin >> n;
    for (int i = 1; i < n; ++i) {
        int x, y; cin >> x >> y;
        gph[x].push_back(y);
        gph[y].push_back(x);
    }
    dfs_hld(0, 1);
    hld(1, 1, 0, 0);
    ctd(0, 1);

    int m; cin >> m;
    while (m--) {
        int q, x; cin >> q >> x;
        if (q&1) {
            white[x] = !white[x];
            if (white[x]) {
                int y = x;
                while (y) {
                    pqs[y].emplace(get_dist(x, y), x);
                    y = ct_par[y];
                }
            }
        }
        else {
            int r = INF;
            int y = x;
            while (y) {
                auto& pq = pqs[y];
                while (!pq.empty() && !white[pq.top().second]) pq.pop();
                if (!pq.empty()) r = min(r, get_dist(x, y) + pq.top().first);
                y = ct_par[y];
            }
            cout << (r != INF ? r : -1) << '\n';
        }
    }

    return 0;
}
