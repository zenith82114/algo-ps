/*
 * Asia-Pacific Informatics Olympiad, APIO 2019 C. Street Lamps
 * JUNGOL 8211
 *
 * CDQ DnC, BBST
 * Date: 2026.5.12
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;
const int
    MAXN = 3e5 + 4,
    MAXQ = 3e5 + 4;

enum EVENT_TYPE { INS, DEL, QRY };
struct event {
    int t;
    EVENT_TYPE p;
    int l, r;
};

vector<event> events;
int ans[3*MAXQ];

struct vec2 {
    i64 a, b;
    vec2(): a(0), b(0) {}
    vec2(int a, int b): a(a), b(b) {}
    vec2& operator+=(const vec2& v) { a += v.a; b += v.b; return *this; }
    vec2 operator-() const { return vec2(-a, -b); }
};

class seg_tree {
    int N;
    vector<vec2> ar;
public:
    void init(int n) {
        N = 1; while (N < n) N *= 2;
        ar.assign(2*N, vec2());
    }
    void add(int i, vec2 v) {
        for (i |= N; i; i >>= 1) ar[i] += v;
    }
    void clear(int i) {
        add(i, -ar[i | N]);
    }
    vec2 query(int i) {
        int j = N - 1;
        vec2 ret;
        for (i |= N, j |= N; i <= j; i >>= 1, j >>= 1) {
            if ( i&1) ret += ar[i++];
            if (~j&1) ret += ar[j--];
        }
        return ret;
    }
} segt;

void dnc(int s, int e) {
    if (s >= e) return;
    int mid = (s + e) / 2;
    dnc(s, mid); dnc(mid + 1, e);

    vector<int> upd_idx, qry_idx;
    for (int i = s; i <= mid; ++i) {
        if (events[i].p != QRY) upd_idx.push_back(i);
    }
    for (int i = mid + 1; i <= e; ++i) {
        if (events[i].p == QRY) qry_idx.push_back(i);
    }

    sort(begin(upd_idx), end(upd_idx), [](int i, int j) {
        return make_pair(events[i].l, i) < make_pair(events[j].l, j);
    });
    sort(begin(qry_idx), end(qry_idx), [](int i, int j) {
        return make_pair(events[i].l, i) < make_pair(events[j].l, j);
    });

    vector<int> dirty;

    auto j = begin(upd_idx);
    for (int i : qry_idx) {
        const auto& ei = events[i];
        for (; j < end(upd_idx) && events[*j].l <= ei.l; ++j) {
            const auto& ej = events[*j];
            if (ej.p == INS) segt.add(ej.r, vec2(+1, -ej.t));
            else segt.add(ej.r, vec2(-1, +ej.t));
            dirty.push_back(ej.r);
        }
        vec2 ret = segt.query(ei.r);
        ans[i] += ei.t * ret.a + ret.b;
    }

    for (int i : dirty) segt.clear(i);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, q; cin >> n >> q;
    string s; cin >> s; s.insert(begin(s), '0');

    set<pair<int, int>> blocks;
    for (int i = 1; i <= n; ) {
        int j = i;
        while (j <= n && s[i] == s[j]) ++j;
        if (s[i] == '1') {
            blocks.emplace_hint(end(blocks), i, j - 1);
            events.push_back({ 0, INS, i, j - 1 });
        }
        i = j;
    }

    for (int t = 1; t <= q; ++t) {
        string op; cin >> op;
        if (op[0] == 't') {
            int i; cin >> i;

            if (s[i] == '0') {
                int l = i, r = i;
                if (i + 1 <= n && s[i + 1] == '1') {
                    auto f = blocks.lower_bound({ i, i });
                    r = f->second;
                    blocks.erase(f);
                    events.push_back({ t, DEL, i + 1, r });
                }
                if (i - 1 >= 1 && s[i - 1] == '1') {
                    auto f = prev(blocks.lower_bound({ i, i }));
                    l = f->first;
                    blocks.erase(f);
                    events.push_back({ t, DEL, l, i - 1 });
                }
                s[i] = '1';
                blocks.emplace(l, r);
                events.push_back({ t, INS, l, r });
            } else {
                auto f = blocks.lower_bound({ i, i });
                if (f == end(blocks) || f->first > i) f = prev(f);
                auto [l, r] = *f;
                s[i] = '0';
                blocks.erase(f);
                events.push_back({ t, DEL, l, r });
                if (l < i) {
                    blocks.emplace(l, i - 1);
                    events.push_back({ t, INS, l, i - 1 });
                }
                if (i < r) {
                    blocks.emplace(i + 1, r);
                    events.push_back({ t, INS, i + 1, r });
                }
            }
        } else {
            int l, r; cin >> l >> r;
            events.push_back({ t, QRY, l, r - 1 });
        }
    }

    segt.init(n + 1);
    q = events.size();
    dnc(0, q - 1);

    for (int i = 0; i < q; ++i) if (events[i].p == QRY) cout << ans[i] << '\n';
    return 0;
}
