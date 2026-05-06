/*
 * JOI Open Contest, JOI Open Contest 2016 B. Selling RNA Strands
 * BOJ 12898/16780
 * JUNGOL 5480
 *
 * trie, Euler tour, sweep line, segment tree
 * Date: 2026.3.30
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;
constexpr int
    MAXM = 2e6 +4,
    TRIE_SIZE = 2e6 +4,
    SEGT_BASE = 1<<21;

struct trie {
    static constexpr array<int, 128> ctoi = []() {
        array<int, 128> a{};
        a['A']=0;a['C']=1;a['G']=2;a['U']=3;
        return a;
    }();
    int chd[TRIE_SIZE][4];
    int et[TRIE_SIZE][2];
    int sz;
    int clk;

    void init() {
        memset(chd[0], 0, sizeof chd[0]);
        sz = 1;
        clk = 0;
    }
    template <typename Iterator>
    void add(Iterator first, Iterator last) {
        int x = 0;
        for (auto it = first; it != last; ++it) {
            int i = ctoi[(int)*it];
            if (!chd[x][i]) {
                chd[x][i] = sz;
                memset(chd[sz], 0, sizeof chd[sz]);
                et[sz][0] = 0;
                ++sz;
            }
            x = chd[x][i];
        }

    }
    void dfs(int x = 0) {
        et[x][0] = clk++;
        for (int y : chd[x]) if (y && !et[y][0]) dfs(y);
        et[x][1] = clk - 1;
    }
    template <typename Iterator>
    pair<int, int> query(Iterator first, Iterator last) {
        int x = 0;
        for (auto it = first; it != last; ++it) {
            int i = ctoi[(int)*it];
            if (!chd[x][i]) return {-1, -1};
            x = chd[x][i];
        }
        return {et[x][0], et[x][1]};
    }
} tp, tq;

struct seg_tree {
    int tr[2*SEGT_BASE];

    void init() { memset(tr, 0, sizeof tr); }
    void add(int i) {
        for (i |= SEGT_BASE; i; i >>= 1) ++tr[i];
    }
    int query(int i, int j) {
        int ans = 0;
        for (i |= SEGT_BASE, j |= SEGT_BASE; i <= j; i >>= 1, j >>= 1) {
            if ( i&1) ans += tr[i++];
            if (~j&1) ans += tr[j--];
        }
        return ans;
    }
} segt;

pair<int, int> yrange[MAXM];
int ans[MAXM] {};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    tp.init(); tq.init();
    int n, m; cin >> n >> m;
    vector<string> dict(n);
    for (string& s : dict) {
        cin >> s;
        tp.add(s.begin(), s.end());
        tq.add(s.rbegin(), s.rend());
    }
    tp.dfs(); tq.dfs();

    using event = tuple<int, int, int>;
    vector<event> ev; ev.reserve(n + 2*m);

    for (const string& s : dict) {
        int x = tp.query(s.begin(), s.end()).first;
        int y = tq.query(s.rbegin(), s.rend()).first;
        ev.emplace_back(x, 0, y);
    }
    for (int i = 0; i < m; ++i) {
        string p, q; cin >> p >> q;
        auto [x1, x2] = tp.query(p.begin(), p.end());
        yrange[i] = tq.query(q.rbegin(), q.rend());
        if (x1 != -1 && yrange[i].first != -1) {
            ev.emplace_back(x1, -1, i);
            ev.emplace_back(x2, +1, i);
        }
    }
    sort(ev.begin(), ev.end());

    segt.init();
    for (auto& [_, type, y_or_id] : ev) {
        if (type == 0) segt.add(y_or_id);
        else {
            auto [y1, y2] = yrange[y_or_id];
            ans[y_or_id] += type * segt.query(y1, y2);
        }
    }

    for (int i = 0; i < m; ++i) cout << ans[i] << '\n';
    return 0;
}
