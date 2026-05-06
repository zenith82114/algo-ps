/*
 * Polish Olympiad in Informatics, POI 2007/2008, Stage 2 Day 2 A. Mafia
 * BOJ 8161 - graph theory; functional graph
 * Date: 2025.3.22
 */

#include<bits/stdc++.h>
using namespace std;
constexpr int MAXN = 1'000'004;

array<int, MAXN> f, indeg, v;
array<vector<int>, MAXN> cc;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n; cin >> n;
    indeg.fill(0);
    for (int x = 1; x <= n; ++x) {
        cin >> f[x];
        ++indeg[f[x]];
    }

    v.fill(0);
    for (int s = 1; s <= n; ++s) if (!v[s]) {
        v[s] = s;
        cc[s].emplace_back(s);
        int x = s;
        while (!v[f[x]]) {
            x = f[x];
            v[x] = s;
            cc[s].emplace_back(x);
        }
        if (v[f[x]] < s) {
            for (int y : cc[s]) v[y] = v[f[x]], cc[v[f[x]]].emplace_back(y);
            cc[s].clear();
        }
    }

    int mn = 0, mx = 0;
    for (int s = 1; s <= n; ++s) if (!cc[s].empty()) {
        vector<int> p;
        queue<int> q;
        int k = 0;
        for (int x : cc[s]) if (!indeg[x]) {
            ++k;
            q.emplace(x);
        }
        while (!q.empty()) {
            int x = q.front(); q.pop();
            p.emplace_back(x);
            if (--indeg[f[x]] == 0) q.emplace(f[x]);
        }
        int d = cc[s].size();
        if (p.empty()) p.emplace_back(cc[s].front());
        while ((int)p.size() < d) p.emplace_back(f[p.back()]);

        int mn1 = 0, mn2 = 0;
        for (int i = 0; i < d; ++i) if (v[p[i]]) v[f[p[i]]] = 0;
        for (int x : p) if (!v[x]) ++mn1;

        for (int x : p) v[x] = 1;
        if (v[p[d - 1]]) v[f[p[d - 1]]] = 0;
        for (int i = 0; i < d - 1; ++i) if (v[p[i]]) v[f[p[i]]] = 0;
        for (int x : p) if (!v[x]) ++mn2;

        mn += min(mn1, mn2);
        mx += (k? d - k : max(1, d - 1));
    }

    cout << mn << ' ' << mx;
    return 0;
}
