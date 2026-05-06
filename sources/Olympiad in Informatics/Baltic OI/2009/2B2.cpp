/*
 * Baltic Olympiad in Informatics, BOI 2009 Day 2 B. Triangulation
 * BOJ 3351
 *
 * smaller to larger
 * Date: 2026.2.13
 */

#include<bits/stdc++.h>
using namespace std;
constexpr int MAXN = 1e5 + 4;

vector<pair<int, int> > edg;
int chk[MAXN*2];
int tri[MAXN][3];
int clr[MAXN], cnt_total[MAXN];

vector<int> adj[MAXN];
map<int, int> cnt[MAXN];
int ans = 0;

void dfs(int px, int x) {
    cnt[x].emplace(clr[x], 1);

    for (int y : adj[x]) if (y != px) {
        dfs(x, y);
        if (cnt[x].size() < cnt[y].size()) cnt[x].swap(cnt[y]);
        for (auto [k, v] : cnt[y]) cnt[x][k] += v;
        cnt[y].clear();
    }

    vector<pair<int, int> > kv(cnt[x].begin(), cnt[x].end());
    for (auto [k, v] : kv) if (v == cnt_total[k]) cnt[x].erase(k);
    if (x > 1 && cnt[x].empty()) ++ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n; cin >> n; n -= 2;
    for (int x = 1; x <= n; ++x) {
        auto v = tri[x];
        cin >> v[0] >> v[1] >> v[2] >> clr[x];
        cnt_total[clr[x]]++;
        sort(v, v + 3);
        edg.emplace_back(v[0], v[1]);
        edg.emplace_back(v[0], v[2]);
        edg.emplace_back(v[1], v[2]);
    }
    sort(edg.begin(), edg.end());
    edg.erase(unique(edg.begin(), edg.end()), edg.end());
    for (int x = 1; x <= n; ++x) {
        auto v = tri[x]; int e;
        e = lower_bound(edg.begin(), edg.end(), make_pair(v[0], v[1])) - edg.begin();
        if (!chk[e]) chk[e] = x;
        else {
            adj[x].emplace_back(chk[e]);
            adj[chk[e]].emplace_back(x);
        }
        e = lower_bound(edg.begin(), edg.end(), make_pair(v[0], v[2])) - edg.begin();
        if (!chk[e]) chk[e] = x;
        else {
            adj[x].emplace_back(chk[e]);
            adj[chk[e]].emplace_back(x);
        }
        e = lower_bound(edg.begin(), edg.end(), make_pair(v[1], v[2])) - edg.begin();
        if (!chk[e]) chk[e] = x;
        else {
            adj[x].emplace_back(chk[e]);
            adj[chk[e]].emplace_back(x);
        }
    }

    dfs(0, 1);
    cout << ans;
    return 0;
}
