/*
 * ICPC Japanese Alumni Group, JAG Spring Contest 2015 A. Balanced Paths
 * BOJ 11706 - centroid DnC
 * Date: 2026.1.2
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;
constexpr int MAXN = 1e5 + 4;

char label[MAXN];
vector<int> g[MAXN];
int sz[MAXN];
bitset<MAXN> is_ct;
int lpath[MAXN];    // start in subtree[x], end at x
int rpath[MAXN];    // start from a child of x, end in subtree[x]
vector<int> dirty;

int get_sz(int px, int x) {
    sz[x] = 1;
    for (int y : g[x]) if (y != px && !is_ct[y]) {
        sz[x] += get_sz(x, y);
    }
    return sz[x];
}

int get_ct(int px, int x, int m) {
    for (int y : g[x]) if (y != px && !is_ct[y] && sz[y] > m) {
        return get_ct(x, y, m);
    }
    return x;
}

int cnt_lpath(int px, int x, int a, int b) {
    if (label[x] == '(') (a ? a-- : b++); else a++;
    int ret = (!a ? rpath[b] : 0);
    for (int y : g[x]) if (y != px && !is_ct[y]) {
        ret += cnt_lpath(x, y, a, b);
    }
    return ret;
}

int cnt_rpath(int px, int x, int a, int b) {
    if (label[x] == ')') (b ? b-- : a++); else b++;
    int ret = (!b ? lpath[a] : 0);
    for (int y : g[x]) if (y != px && !is_ct[y]) {
        ret += cnt_rpath(x, y, a, b);
    }
    return ret;
}

void upd_lpath(int px, int x, int a, int b) {
    if (label[x] == '(') (a ? a-- : b++); else a++;
    if (!a) lpath[b]++, dirty.push_back(b);
    for (int y : g[x]) if (y != px && !is_ct[y]) upd_lpath(x, y, a, b);
}

void upd_rpath(int px, int x, int a, int b) {
    if (label[x] == ')') (b ? b-- : a++); else b++;
    if (!b) rpath[a]++, dirty.push_back(a);
    for (int y : g[x]) if (y != px && !is_ct[y]) upd_rpath(x, y, a, b);
}

i64 ctd_dnc(int x) {
    const int c = get_ct(0, x, get_sz(0, x)/2);
    is_ct.set(c);

    for (int a : dirty) lpath[a] = rpath[a] = 0;
    dirty.clear();

    const int lc = (label[c] == '(');
    if (lc) lpath[1] = 1, dirty.push_back(1);
    rpath[0] = 1; dirty.push_back(0);

    i64 ret = 0;
    for (int y : g[c]) if (!is_ct[y]) {
        ret += cnt_lpath(c, y, lc^1, lc) + cnt_rpath(c, y, 0, 0);
        upd_lpath(c, y, lc^1, lc);
        upd_rpath(c, y, 0, 0);
    }

    for (int y : g[c]) if (!is_ct[y]) ret += ctd_dnc(y);
    return ret;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n; cin >> n;
    for (int x = 1; x <= n; ++x) cin >> label[x];
    for (int i = 1; i < n; ++i) {
        int x, y; cin >> x >> y;
        g[x].push_back(y);
        g[y].push_back(x);
    }

    cout << ctd_dnc(1);
    return 0;
}
