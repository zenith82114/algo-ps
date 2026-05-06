/*
 * Asia-Pacific Informatics Olympiad, APIO 2019 B. Bridges
 * BOJ 17635
 *
 * sqrt decomposition, rollback dsu
 * Date: 2025.8.15
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;
constexpr int MAXN = 5e4, MAXM = 1e5, MAXQ = 1e5;
constexpr double HPARAM = 3.;

struct edge { int x, y, w; } edg[MAXM];
struct query { int type, target, weight; } que[MAXQ];
int ans[MAXQ];

bitset<MAXM> upd;
vector<int> unions[MAXQ];
int dsu[MAXN];
stack<pair<int, int> > logs;

int _find(int x) { return dsu[x] < 0? x : _find(dsu[x]); }

int get_size(int x) { return -dsu[_find(x)]; }

void unite(int x, int y, bool logging) {
    x = _find(x), y = _find(y);
    if (x == y) return;
    if (dsu[x] < dsu[y]) swap(x, y);
    if (logging) logs.emplace(x, dsu[x]);
    dsu[y] += dsu[x];
    dsu[x] = y;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m; cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        auto& ei = edg[i];
        cin >> ei.x >> ei.y >> ei.w; --ei.x; --ei.y;
    }
    int q; cin >> q;
    for (int i = 0; i < q; ++i) {
        auto& qi = que[i];
        cin >> qi.type >> qi.target >> qi.weight; --qi.target;
    }
    const int k = max(1, (int)round(HPARAM * sqrt((m*log2(m + 1) + n) / log2(n + 1)) + .5));

    for (int bs = 0, be = 0; bs < q; bs = be) {
        be = min(bs + k, q);

        vector<int> qids_1, qids_2, eids_const;

        for (int i = bs; i < be; ++i) {
            auto& qi = que[i];
            if (qi.type & 1) {
                qids_1.emplace_back(i);
                upd.set(qi.target);
            } else {
                qids_2.emplace_back(i);
            }
        }
        for (int i = 0; i < m; ++i) if (!upd[i]) eids_const.emplace_back(i);

        for (int i = bs; i < be; ++i) {
            auto& qi = que[i];
            if (qi.type & 1) edg[qi.target].w = qi.weight;
            else for (int j : qids_1) {
                if (edg[que[j].target].w >= qi.weight) {
                    unions[i].emplace_back(que[j].target);
                }
            }
        }

        sort(begin(qids_2), end(qids_2),
            [](int i, int j) { return que[i].weight > que[j].weight; });
        sort(begin(eids_const), end(eids_const),
            [](int i, int j) { return edg[i].w > edg[j].w; });

        fill(dsu, dsu + n, -1);

        auto iter = begin(eids_const);
        for (int i : qids_2) {
            auto& qi = que[i];
            while (iter < end(eids_const) && edg[*iter].w >= qi.weight) {
                unite(edg[*iter].x, edg[*iter].y, false);
                ++iter;
            }
            for (int j : unions[i]) unite(edg[j].x, edg[j].y, true);
            ans[i] = get_size(qi.target);
            while (!logs.empty()) {
                auto [x, v] = logs.top(); logs.pop();
                int y = dsu[x];
                dsu[y] -= (dsu[x] = v);
            }
        }

        for (int i = bs; i < be; ++i) {
            if (que[i].type & 1) upd.reset(que[i].target);
            else unions[i].clear();
        }
    }

    for (int i = 0; i < q; ++i) if (ans[i]) cout << ans[i] << '\n';
    return 0;
}
