/*
 * 트리와 쿼리 12
 * QOJ 18815
 *
 * offline dynamic connectivity (DnC)
 * Date: 2025.8.16
 *
 * Works for general graphs too. (BOJ 16911)
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;
using ii = pair<int, int>;
const int MAXN = 1e5 +4;

struct interval {
    int x, y, s, e;
    interval(int x, int y, int s, int e): x(x), y(y), s(s), e(e) {};
};
vector<interval> intv;
map<ii, int> mp;
vector<ii> que, unions[1<<18];
int dsu[MAXN];

int _find(int x) { return dsu[x] < 0? x : _find(dsu[x]); }

ii unite(int x, int y) {
    x = _find(x), y = _find(y);
    if (x == y) return {-1, 0};
    if (dsu[x] < dsu[y]) swap(x, y);
    ii log(x, dsu[x]);
    dsu[y] += dsu[x]; dsu[x] = y;
    return log;
}

void rollback(const ii& log) {
    auto [x, v] = log;
    if (x == -1) return;
    int y = dsu[x];
    dsu[y] -= (dsu[x] = v);
}

void add_util(int i, int s, int e, const interval& t) {
    if (t.e <= s || e <= t.s) return;
    if (t.s <= s && e <= t.e) unions[i].emplace_back(t.x, t.y);
    else {
        int mid = (s + e)/2;
        add_util(i<<1, s, mid, t);
        add_util(i<<1|1, mid, e, t);
    }
}

void solve_util(int i, int s, int e) {
    vector<ii> logs;
    for (auto [x, y] : unions[i]) logs.emplace_back(unite(x, y));
    if (s + 1 == e) {
        auto [x, y] = que[s];
        cout << (_find(x) == _find(y)) << '\n';
    } else {
        int mid = (s + e)/2;
        solve_util(i<<1, s, mid);
        solve_util(i<<1|1, mid, e);
    }
    while (!logs.empty()) { rollback(logs.back()); logs.pop_back(); }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m; cin >> n >> m;
    int q = 0;
    while (m--) {
        int t, x, y; cin >> t >> x >> y;
        if (x > y) swap(x, y);
        ii key(x, y);
        if (t == 1) mp.emplace(key, q);
        else if (t == 2) {
            if (mp[key] < q) intv.emplace_back(x, y, mp[key], q);
            mp.erase(key);
        } else {
            que.emplace_back(x, y);
            ++q;
        }
    }
    for (const auto& [key, v] : mp) {
        auto [x, y] = key;
        intv.emplace_back(x, y, v, q);
    }
    mp.clear();

    for (const auto& t : intv) add_util(1, 0, q, t);
    memset(dsu, -1, sizeof dsu);
    solve_util(1, 0, q);
    return 0;
}
