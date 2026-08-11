/*
 * Croatian Open Competition in Informatics, COCI 2006/2007, Contest #6
 * F. PROSTOR
 * QOJ 17580
 *
 * sweep line, 2D Fenwick tree
 * Date: 2026.8.11
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;
using ii = pair<int, int>;
const int MAXN = 1e5;

struct fenwick_tree_2D {
    static const int N = 1e3;
    int ar[N][N];

    void clear() { memset(ar, 0, sizeof ar); }

    void add(int x, int y, int v) {
		for (int i = x; i < N; i += i&-i)
        for (int j = y; j < N; j += j&-j) ar[i][j] += v;
    }

    int _query_prefix(int x, int y) {
        int res = 0;
        for (int i = x; i > 0; i -= i&-i)
        for (int j = y; j > 0; j -= j&-j) res += ar[i][j];
        return res;
    }

    int query(int x1, int x2, int y1, int y2) {
        return _query_prefix(x2, y2)
            - _query_prefix(x1-1, y2)
            - _query_prefix(x2, y1-1)
            + _query_prefix(x1-1, y1-1);
    }
};
fenwick_tree_2D segt[2];

int coords[3][MAXN][2];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n; cin >> n;
    for (int i = 0; i < n; ++i) {
        for (auto ax : coords) cin >> ax[i][0];
        for (auto ax : coords) cin >> ax[i][1];
        for (auto ax : coords) if (ax[i][0] > ax[i][1]) swap(ax[i][0], ax[i][1]);
    }

    i64 ans = 0;
    for (int ax : {0, 1, 2}) {
        auto X = coords[ax];
        auto Y = coords[(ax+1)%3];
        auto Z = coords[(ax+2)%3];

        /* XY case */

        vector<int> rectX;
        vector<ii> evt;

        for (int i = 0; i < n; ++i) {
            if (X[i][0] == X[i][1]) rectX.push_back(i);
            if (Y[i][0] == Y[i][1]) evt.emplace_back(i, 0), evt.emplace_back(i, 1);
        }

        sort(begin(rectX), end(rectX), [&X](int i1, int i2) {
            return X[i1][0] < X[i2][0];
        });

        sort(begin(evt), end(evt), [&X](const ii& e1, const ii& e2) {
            auto [i1, s1] = e1; auto [i2, s2] = e2;
            return ii(X[i1][s1], s1) < ii(X[i2][s2], s2);
        });

        size_t p = 0;
        segt[0].clear(), segt[1].clear();

        for (int j : rectX) {
            int x = X[j][0];

            auto gate = [&evt, &X](size_t p, int x) {
                if (p >= evt.size()) return false;
                auto [i, s] = evt[p];
                return (X[i][s] < x) || (X[i][s] == x && s == 0);
            };

            for (; gate(p, x); ++p) {
                auto [i, s] = evt[p];
                segt[0].add(Y[i][0], Z[i][0], 1-2*s);
                segt[1].add(Y[i][0], Z[i][1], 1-2*s);
            }

            ans += segt[0].query(Y[j][0], Y[j][1], 0, Z[j][1]);
            ans -= segt[1].query(Y[j][0], Y[j][1], 0, Z[j][0]-1);
        }

        /* XX case */

        evt.clear();
        for (int i : rectX) evt.emplace_back(i, 0), evt.emplace_back(i, 1);

        sort(begin(evt), end(evt), [&Y](const ii& e1, const ii& e2) {
            auto [i1, s1] = e1; auto [i2, s2] = e2;
            return ii(Y[i1][s1], s1) < ii(Y[i2][s2], s2);
        });

        p = 0;
        segt[0].clear(), segt[1].clear();

        for (auto [i, s] : evt) {
            if (s == 0) {
                ans += segt[0].query(X[i][0], X[i][0], 0, Z[i][1]);
                ans -= segt[1].query(X[i][0], X[i][0], 0, Z[i][0]-1);
            }

            segt[0].add(X[i][0], Z[i][0], 1-2*s);
            segt[1].add(X[i][0], Z[i][1], 1-2*s);
        }
    }

    cout << ans;
    return 0;
}
