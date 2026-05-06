/*
 * ICPC Japanese Alumni Group, JAG Summer Camp 2017 Day 3 K. Permutation Period
 * BOJ 16825 - sqrt decomposition
 * Date: 2026.1.1
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;
constexpr int MAXN = 1e5 + 4;

int g[MAXN], gr[MAXN];
vector<pair<int, int> > que;
vector<int> dyn;
bitset<MAXN> is_dyn;
pair<int, int> skip[MAXN];
bitset<MAXN> vis;

struct LCMManager {
    static const int MOD = 1e9 + 7;
    int spf[MAXN];
    int freq[MAXN];
    int inv[MAXN];
    i64 ans;
    vector<pair<int, int> > logs[2];

    void init(int n) {
        memset(spf, 0, sizeof spf);
        memset(freq, 0, sizeof freq);
        ans = 1;

        for (int i = 2; i <= n; ++i) if (!spf[i]) {
            spf[i] = i;
            for (i64 j = (i64)i * i; j <= n; j += i) if (!spf[j]) spf[j] = i;
            i64 tmp = i;
            inv[i] = 1;
            for (int e = MOD - 2; e; e /= 2) {
                if (e&1) inv[i] = tmp * inv[i] % MOD;
                tmp = tmp * tmp % MOD;
            }
        }
    }

    void add(int len, bool dyn) {
        while (len > 1) {
            int p = spf[len], e = 0;
            while (spf[len] == p) len /= spf[len], e++;
            if (freq[p] < e) {
                logs[dyn].emplace_back(p, freq[p]);
                for (; freq[p] < e; ++freq[p]) ans = (ans * p) % MOD;
            }
        }
    }

    void rollback(bool dyn) {
        auto& log = logs[dyn];
        while (!log.empty()) {
            auto [p, e] = log.back(); log.pop_back();
            for (; freq[p] > e; --freq[p]) ans = (ans * inv[p]) % MOD;
        }
    }
} manager;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, q; cin >> n >> q;
    iota(g, g + n + 1, 0);
    iota(gr, gr + n + 1, 0);
    manager.init(n);

    const int BLK = max(16, (int)round(sqrt(n + .5)));
    for (int i = 0; i < q; i += BLK) {
        que.resize(min(BLK, q - i));
        for (auto& [x, y] : que) {
            cin >> x >> y;
            dyn.push_back(x); is_dyn.set(x);
            dyn.push_back(y); is_dyn.set(y);
        }

        // build skip table
        for (int x = 1; x <= n; ++x) skip[x].first = 0;
        for (int x : dyn) if (!skip[gr[x]].first) {
            int y = gr[x]; skip[y] = {x, 1};
            int cnt = 1;
            while (!is_dyn[y]) { y = gr[y]; skip[y] = {x, ++cnt}; }
        }

        // static cycles
        for (int x = 1; x <= n; ++x) if (!skip[x].first) {
            int y = x, len = 0;
            while (!skip[y].first) {
                skip[y].first = x;
                y = g[y], ++len;
            }
            manager.add(len, false);
        }

        for (auto [x, y] : que) {
            swap(gr[g[x]], gr[g[y]]);
            swap(g[x], g[y]);
            swap(skip[x], skip[y]);

            // dynamic cycles
            for (int x : dyn) vis.reset(x);
            for (int x : dyn) if (!vis[x]) {
                int y = x, len = 0;
                while (!vis[y]) {
                    vis.set(y);
                    y = skip[y].first;
                    len += skip[y].second;
                }
                manager.add(len, true);
            }
            cout << manager.ans << '\n';
            manager.rollback(true);
        }

        manager.rollback(false);
        for (int x : dyn) is_dyn.reset(x);
        dyn.clear();
    }

    return 0;
}
