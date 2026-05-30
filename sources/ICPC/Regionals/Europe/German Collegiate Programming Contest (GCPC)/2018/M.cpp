/*
 * ICPC, Regionals, Europe, Northwestern Europe Regional Contest,
 * German Collegiate Programming Contest, GCPC 2018 M. Mountaineers
 * JUNGOL 12855
 *
 * disjoint sets, smaller to larger
 * Date: 2026.5.30
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;
using ii = pair<int, int>;
const int MAXQ = 1e5 + 4;

int height[504][504];
set<int> qids[504][504];
int ans[MAXQ];

struct disjoint_sets {
    ii ar[504][504];

    ii _find(int x, int y) {
        auto [px, py] = ar[x][y];
        if (!px) return ii(x, y);
        return ar[x][y] = _find(px, py);
    }

    void init(int n, int m) {
        for (int x = 1; x <= n; ++x)
        for (int y = 1; y <= m; ++y) ar[x][y] = ii(0, 0);
    }

    void unite(int x1, int y1, int x2, int y2, int h) {
        tie(x1, y1) = _find(x1, y1); tie(x2, y2) = _find(x2, y2);
        if (x1 == x2 && y1 == y2) return;

        if (qids[x1][y1].size() < qids[x2][y2].size()) {
            swap(x1, x2), swap(y1, y2);
        }
        auto& t1 = qids[x1][y1], & t2 = qids[x2][y2];
        for (int i : t2) {
            if (t1.find(i) != t1.end()) {
                ans[i] = h;
                t1.erase(i);
            }
            else t1.emplace(i);
        }
        t2.clear();

        ar[x2][y2] = ii(x1, y1);
    }
} dsu;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m, q; cin >> n >> m >> q;
    int nm = n*m;
    vector<tuple<int, int, int>> evt; evt.reserve(nm);
    for (int x = 1; x <= n; ++x)
    for (int y = 1; y <= m; ++y) {
        cin >> height[x][y];
        evt.emplace_back(height[x][y], x, y);
    }
    sort(begin(evt), end(evt));
    for (int i = 0; i < q; ++i) {
        int x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
        if (x1 == x2 && y1 == y2) ans[i] = height[x1][y1];
        else {
            qids[x1][y1].emplace(i);
            qids[x2][y2].emplace(i);
        }
    }

    constexpr int dt[] {0,-1,0,1,0};
    dsu.init(n, m);

    for (int s = 0, e = 0; s < nm; s = e) {
        int h = get<0>(evt[s]);
        while (e < nm && get<0>(evt[e]) == h) ++e;

        for (int j = s; j < e; ++j) {
            auto [_, x, y] = evt[j];

            for (int k = 0; k < 4; ++k) {
                int nx = x + dt[k], ny = y + dt[k+1];
                if (nx < 1 || n < nx || ny < 1 || m < ny) continue;
                if (height[nx][ny] <= h) dsu.unite(x, y, nx, ny, h);
            }
        }
    }

    for (int i = 0; i < q; ++i) cout << ans[i] << '\n';
    return 0;
}
