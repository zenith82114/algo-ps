/*
 * UCPC 2023 Qualifier B. 물류창고
 * BOJ 28296
 *
 * disjoint sets, small to large
 * Date: 2023.7.10
 */

#include<bits/stdc++.h>
using namespace std;

int dsu[100'001];
map<int, int> mp[100'001];
int64_t ans[50'001];

int root(int x) {
    if (dsu[x] < 0) return x;
    return dsu[x] = root(dsu[x]);
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);

    int N, K, M; cin >> N >> K >> M;
    for (int x = 1; x <= N; ++x) {
        dsu[x] = -1;
        int c; cin >> c; mp[x].emplace(c, 1);
    }

    using iii = tuple<int, int, int>;
    vector<iii> edges(M);
    for (auto& [w, x, y] : edges) cin >> x >> y >> w;
    sort(edges.begin(), edges.end(), greater<>());

    for (auto [w, x, y] : edges) {
        x = root(x), y = root(y);
        if (x == y) continue;
        if (dsu[x] > dsu[y]) swap(x, y);
        if (dsu[x] == dsu[y]) dsu[x]--;
        dsu[y] = x;

        if (mp[x].size() < mp[y].size()) swap(mp[x], mp[y]);
        for (auto& [c, n] : mp[y]) {
            if (!mp[x].count(c)) mp[x].emplace(c, 0);
            ans[c] += (int64_t)w * n * mp[x][c];
            mp[x][c] += n;
        }
        mp[y].clear();
    }

    for (int c = 1; c <= K; ++c) cout << ans[c] << '\n';
    return 0;
}
