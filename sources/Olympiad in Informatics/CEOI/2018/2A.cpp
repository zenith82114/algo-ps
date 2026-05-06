/*
 * Central Europe Olympiad in Informatics, CEOI 2018, Day 2 A. Fibonacci Representations
 * BOJ 16029 - Zeckendorf's theorem, BBST, segment tree
 * Date: 2026.1.19
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;
using ii = pair<int, int>;
const int MAXN = 1e5 + 4;
const int MOD = 1e9 + 7;
const int INF = 0x3f3f3f3f;

set<ii> intervals;
vector<ii> events[MAXN];
int clk = 0;

void add_interval(int a, int b) {
    if (a > b) return;
    intervals.emplace(a, b);
    events[clk].emplace_back(a, b);
}

void remove_interval(set<ii>::iterator& p) {
    events[clk].emplace_back(*p);
    intervals.erase(p);
}

void add_fib_out(int x) {
    auto r = intervals.lower_bound(ii(x, x));
    auto l = prev(r);
    auto [al, bl] = *l;
    auto [ar, br] = *r;

    if (bl + 1 == x) {
        remove_interval(l);
        add_interval(al, bl - 2);
        add_fib_out(x + 1);
    } else if (x + 1 == ar) {
        remove_interval(r);
        add_fib_out(br + 1);
    } else {
        int a = x, b = x;
        if (bl + 2 == x) { remove_interval(l); a = al; }
        if (x + 2 == ar) { remove_interval(r); b = br; }
        add_interval(a, b);
    }
}

void add_fib(int x) {
    auto p = prev(intervals.lower_bound(ii(x + 1, x + 1)));
    auto [a, b] = *p;

    if (x < a || b < x) add_fib_out(x);
    else if ((a ^ x) & 1) {
        remove_interval(p);
        add_interval(a, x - 1);
        add_fib_out(b + 1);
    } else {
        remove_interval(p);
        add_interval(a + 1, x - 1);
        for (int y : {a - 2, b + 1}) {
            if (y > -1) add_fib_out(max(1, y));
        }
    }
}

struct matrix {
    int d[2][2];

    void init(int k) {
        d[0][0] = 1; d[0][1] = 0;
        d[1][0] = k; d[1][1] = 1;
    }
    void mul(const matrix& A, const matrix& B) {
        d[0][0] = (1ll*A.d[0][0]*B.d[0][0] + 1ll*A.d[0][1]*B.d[1][0]) % MOD;
        d[0][1] = (1ll*A.d[0][0]*B.d[0][1] + 1ll*A.d[0][1]*B.d[1][1]) % MOD;
        d[1][0] = (1ll*A.d[1][0]*B.d[0][0] + 1ll*A.d[1][1]*B.d[1][0]) % MOD;
        d[1][1] = (1ll*A.d[1][0]*B.d[0][1] + 1ll*A.d[1][1]*B.d[1][1]) % MOD;
    }
};

struct seg_tree {
    struct node {
        matrix m;
        int a, b;
        bool valid;
        void init(ii& v) {
            tie(a, b) = v;
            m.init((b - a) / 2);
            valid = false;
        }
    };

    int N;
    vector<node> tr;

    void init(int sz) {
        N = 1; while (N < sz) N *= 2;
        tr.resize(2*N);
    }
    void init_node(int i, ii& v) { tr[i|N].init(v); }
    void toggle(int i) {
        i |= N;
        tr[i].valid = !tr[i].valid;
        for (i /= 2; i; i /= 2) {
            const auto& lc = tr[2*i];
            const auto& rc = tr[2*i + 1];

            tr[i].valid = lc.valid | rc.valid;
            if (!lc.valid) tr[i] = rc;
            else if (!rc.valid) tr[i] = lc;
            else {
                tr[i].a = lc.a;
                tr[i].b = rc.b;
                int g = rc.a - lc.b;
                tr[i].m.d[0][0] = 1; tr[i].m.d[0][1] = (g - 1) / 2;
                tr[i].m.d[1][0] = 1; tr[i].m.d[1][1] = g / 2;
                matrix temp;
                temp.mul(lc.m, tr[i].m);
                tr[i].m.mul(temp, rc.m);
            }
        }
    }
    int query() const {
        return (tr[1].m.d[0][0] + tr[1].m.d[0][1]) % MOD;
    }
} segt;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    intervals.emplace(-INF, -INF);
    intervals.emplace(+INF, +INF);

    int n; cin >> n;
    for (clk = 0; clk < n; ++clk) { int x; cin >> x; add_fib(x); }

    vector<ii> all;
    all.emplace_back(0, 0);
    for (clk = 0; clk < n; ++clk) {
        all.insert(all.end(), events[clk].begin(), events[clk].end());
    }
    sort(all.begin(), all.end());
    all.erase(unique(all.begin(), all.end()), all.end());

    segt.init(all.size());
    for (int i = 0; i < (int)all.size(); ++i) segt.init_node(i, all[i]);
    segt.toggle(0);

    for (clk = 0; clk < n; ++clk) {
        for (auto v : events[clk]) {
            int i = lower_bound(all.begin(), all.end(), v) - all.begin();
            segt.toggle(i);
        }
        cout << segt.query() << '\n';
    }

    return 0;
}
