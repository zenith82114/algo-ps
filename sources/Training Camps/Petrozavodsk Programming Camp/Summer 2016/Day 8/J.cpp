/*
 * Petrozavodsk Programming Camp, Summer 2016, Day 8: DPRK Contest
 * J. Jong Hyok and String
 * QOJ 12930
 *
 * suffix automaton
 * Date: 2026.8.1
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;
using ii = pair<int, int>;
const int MAX_STATES = 4e5+4;

struct suffix_automaton {
    struct state {
        array<int, 27> next;
        int len=0, link=-1;
        int run=0;
    };

    state st[MAX_STATES];
    int sz, last;

    int _ctoi(char c) { return c == '#' ? 26 : (c - 'a'); }

    void init() {
        sz = 1;
        last = 0;
        st[0].next.fill(-1);
    }

    void push_back(char c, int run) {
        int cur = sz++;
        st[cur].next.fill(-1);
        st[cur].len = st[last].len + 1;
        st[cur].run = run;

        int i = _ctoi(c);
        int x = last;
        while (x != -1 && st[x].next[i] == -1) {
            st[x].next[i] = cur;
            x = st[x].link;
        }

        if (x == -1) st[cur].link = 0;
        else {
            int y = st[x].next[i];

            if (st[y].len == st[x].len + 1) st[cur].link = y;
            else {
                int clone = sz++;
                st[clone].next = st[y].next;
                st[clone].len = st[x].len + 1;
                st[clone].link = st[y].link;
                st[clone].run = 0;
                st[y].link = st[cur].link = clone;

                while (x != -1 && st[x].next[i] == y) {
                    st[x].next[i] = clone;
                    x = st[x].link;
                }
            }
        }

        last = cur;
    }

    void dp() {
        vector<int> ord(sz);
        iota(begin(ord), end(ord), 0);
        sort(begin(ord), end(ord), [this](int x, int y) {
            return st[x].len > st[y].len;
        });

        for (int y : ord) {
            int x = st[y].link;
            st[x].run = max(st[x].run, st[y].run);
        }
    }

    int query(const string& q) {
        int x = 0;
        for (char c : q) {
            int i = _ctoi(c);
            if (st[x].next[i] == -1) return 0;
            x = st[x].next[i];
        }

        return min(st[x].len, st[x].run) - st[st[x].link].len;
    }
} sam;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    sam.init();
    int n, m; cin >> n >> m;

    while (n--) {
        string p; cin >> p;
        for (int i = 0; i < (int)p.size(); ++i) sam.push_back(p[i], i+1);
        sam.push_back('#', 0);
    }
    sam.dp();

    while (m--) {
        string q; cin >> q;
        cout << sam.query(q) << '\n';
    }
    return 0;
}
