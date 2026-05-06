/*
 * Croatian Highschool Competitions in Informatics, 2009, Final Exam #2 B. DVAPRAVCA
 * BOJ 3121 - Bulldozer trick
 * Date: 2024.3.3
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;

struct point {
    i64 x, y; int val;
    bool operator<(const point& oth) const {
        return tie(x, y) < tie(oth.x, oth.y);
    }
};

struct vec2 {
    int i, j; i64 dx, dy;
    vec2(int i, int j, const point& a, const point& b)
    : i{i}, j{j}, dx{b.x - a.x}, dy{b.y - a.y} {}
    bool operator<(const vec2& oth) const {
        i64 cx = dy*oth.dx - dx*oth.dy;
        return cx? cx < 0 : tie(i, j) < tie(oth.i, oth.j);
    }
    bool operator==(const vec2& oth) const {
        return dy*oth.dx == dx*oth.dy;
    }
};

class seg_tree {
    struct node {
        int t, p, s, a;
        node(int x): t{x}, p{x}, s{x}, a{x} {}
    };
    vector<node> ar;
    int n;
    void pull(int i) {
        auto& c = ar[i];
        const auto& l = ar[i<<1];
        const auto& r = ar[i<<1|1];
        c.t = l.t + r.t;
        c.p = max(l.p, l.t + r.p);
        c.s = max(l.s + r.t, r.s);
        c.a = max({ l.a, r.a, l.s + r.p });
    }
public:
    seg_tree(int sz) {
        n = 1; while (n < sz) n <<= 1;
        ar.resize(n<<1, 0);
    }
    void set(int i, int x) { ar[n|i] = node(x); }
    void build() {
        for (int i = n-1; i; --i) pull(i);
    }
    void update(int i, int x) {
        set(i, x);
        for (i = (n|i)>>1; i; i >>= 1) pull(i);
    }
    int query() { return ar[1].a; }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n; cin >> n;
    vector<point> pt(n);
    for (auto& [x, y, val] : pt) {
        cin >> x >> y;
        char c; cin >> c;
        val = (c == 'R'? +1 : -n);
    }
    sort(pt.begin(), pt.end());
    if (n == 1) {
        cout << max(0, pt[0].val);
        return 0;
    }

    vector<vec2> v;
    for (int i =   0; i < n; ++i)
    for (int j = i+1; j < n; ++j) {
        v.emplace_back(i, j, pt[i], pt[j]);
    }
    sort(v.begin(), v.end());

    vector<int> pos(n); iota(pos.begin(), pos.end(), 0);

    seg_tree segt(n);
    for (int i = 0; i < n; ++i) segt.set(i, pt[i].val);
    segt.build();

    const int nC2 = v.size();
    int ans = 0;

    for (int st = 0, en = 0; st < nC2; st = en) {
        while (en < nC2 && v[st] == v[en]) ++en;
        for (int id = st; id < en; ++id) {
            int i = v[id].i, j = v[id].j;
            segt.update(pos[i], pt[pos[j]].val);
            segt.update(pos[j], pt[pos[i]].val);
            swap(pos[i], pos[j]);
            swap(pt[pos[i]], pt[pos[j]]);
        }
        ans = max(ans, segt.query());
    }
    cout << ans;
    return 0;
}
