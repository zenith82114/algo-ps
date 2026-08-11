/*
 * Central Europe Olympiad in Informatics, CEOI 2014, Day 1
 * C. Question
 * QOJ 13613
 *
 * ad-hoc
 * Date: 2026.8.11
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;
using ii = pair<int, int>;

vector<bitset<12>> db;

void build_db(int i) {
    static bitset<12> s;

    if (s.count() == 6) { db.push_back(s); return; }

    for (int j = i; j < 12; ++j) {
        s.set(j);
        build_db(j+1);
        s.reset(j);
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    build_db(0);

    int role; cin >> role;
    int n, t; cin >> n >> t;

    if (role&1) {
        while (t--) {
            int x, y; cin >> x >> y;
            for (int h = 0; h < 12; ++h) {
                if (db[x][h] && !db[y][h]) { cout << (h+1) << '\n'; break; }
            }
        }
    } else {
        while (t--) {
            int q, h; cin >> q >> h;
            cout << (db[q][h-1] ? "yes" : "no") << '\n';
        }
    }

    return 0;
}
