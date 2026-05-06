/*
 * ICPC, Regionals, Northern Eurasia,
 * Northwestern Russia Regional Contest Northern Subregional 2012 H. Hospital
 * BOJ 7777 - network flow; vertex-disjoint paths
 * Date: 2024.2.23
 */

#include<bits/stdc++.h>
using namespace std;
using ii = pair<int, int>;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    vector<ii> adj[2048];
    vector<int> cap;

    auto vin =  [] (int x) { return x<<1; };
    auto vout = [] (int x) { return x<<1|1; };
    auto add_edge = [&adj, &cap] (int x, int y) {
        int e = cap.size();
        adj[x].emplace_back(y, e);
        adj[y].emplace_back(x, e|1);
        cap.emplace_back(1);
        cap.emplace_back(0);
    };

    int n, k; cin >> n >> k;
    for (int x = 1; x <= n; ++x) add_edge(vin(x), vout(x));
    for (int x = 1; x <= k; ++x) {
        int d; cin >> d;
        while (d--) {
            int y; cin >> y; add_edge(vout(y), vin(x));
        }
    }
    for (int x = k+1; x <= n; ++x) add_edge(0, vin(x));

    queue<int> q; q.emplace(0);
    bitset<2048> vis; vis.set(0);
    vector<ii> pred(2048, ii(-1, -1));
    while (!q.empty()) {
        int x = q.front(); q.pop();
        for (auto [y, e] : adj[x]) if (!vis[y] && cap[e]) {
            q.emplace(y);
            vis.set(y);
            pred[y] = ii(x, e);
        }
    }

    vector<int> ans1;
    for (int x = 1; x <= n; ++x) if (pred[vout(x)].first == -1) {
        ans1.emplace_back(x);
    }

    vector<ii> ans2;

    for (int x = 1; x <= n; ++x) if (pred[vout(x)].first != -1) {
        for (int e = 0; e < (int)cap.size(); ++e) cap[e] = ~e&1;
        int z = vout(x);
        while (z != 0) {
            auto [pz, e] = pred[z];
            cap[e] = 0; cap[e^1] = 1;
            z = pz;
        }
        q.emplace(0);
        vis.reset(); vis.set(0);
        while (!q.empty()) {
            int xx = q.front(); q.pop();
            for (auto [yy, e] : adj[xx]) if (!vis[yy] && cap[e]) {
                q.emplace(yy);
                vis.set(yy);
            }
        }
        for (int y = x+1; y <= n; ++y) {
            if (pred[vout(y)].first != -1 && !vis[vout(y)]) {
                ans2.emplace_back(x, y);
            }
        }
    }

    cout << ans1.size() << '\n';
    for (int x : ans1) cout << x << ' ';
    cout << '\n' << ans2.size() << '\n';
    if (ans2.size() <= 10000u) {
        for (auto [x, y] : ans2) cout << x << ' ' << y << '\n';
    }
    return 0;

}
