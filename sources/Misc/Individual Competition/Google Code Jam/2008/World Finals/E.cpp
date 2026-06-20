/*
 * Google Code Jam 2008 World Finals
 * E. The Year of Code Jam
 * QOJ 5787
 *
 * max-flow min-cut duality
 * Date: 2026.6.20
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;
using ii = pair<int, int>;

char a[52][52];
vector<ii> gph[52*52 +2];
vector<int> cap;
bitset<52*52 +2> seen, inq;
ii pred[52*52 +2];

bool spfa(int S, int T) {
    seen.reset(); seen.set(S);
    queue<int> q; q.push(S);

    while (!q.empty()) {
        int x = q.front(); q.pop(); inq.reset(x);

        for (auto [y, e] : gph[x]) if (!seen[y] && cap[e]) {
            seen.set(y);
            pred[y] = ii(x, e);
            if (!inq[y]) { q.push(y); inq.set(y); }
        }
    }

    return seen[T];
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int TC; cin >> TC;
    for (int tc = 1; tc <= TC; ++tc) {
        memset(a, '.', sizeof a);
        int n, m; cin >> n >> m;
        for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j) cin >> a[i][j];

        n += 2; m += 2;

        for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j) {
            if (((i^j)&1) && a[i][j] != '?') a[i][j] ^= ('#' ^ '.');
            gph[i*m + j].clear();
        }

        const int S = n*m, T = S+1;
        gph[S].clear(); gph[T].clear();
        cap.clear();

        auto add_edge = [] (int x, int y, int c) {
            int sz = cap.size();
            gph[x].emplace_back(y, sz);
            cap.push_back(c);
            gph[y].emplace_back(x, sz|1);
            cap.push_back(0);
        };

        for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j) {
            int x = i*m + j;

            if (a[i][j] == '#') add_edge(S, x, INT32_MAX);
            if (a[i][j] == '.') add_edge(x, T, INT32_MAX);

            const int dt[] = {0,1,0,-1,0};

            for (int k = 0; k < 4; ++k) {
                int ii = i + dt[k], jj = j + dt[k+1];
                if (ii < 0 || n <= ii || jj < 0 || m <= jj) continue;
                int y = ii*m + jj;
                add_edge(x, y, 1);
            }
        }

        int ans = 2*n*m - n - m;

        while (spfa(S, T)) {
            --ans;
            for (int x = T; x != S; x = pred[x].first) {
                int e = pred[x].second;
                --cap[e]; ++cap[e^1];
            }
        }

        cout << "Case #"<<tc<<": "<< ans << '\n';
    }

    return 0;
}
