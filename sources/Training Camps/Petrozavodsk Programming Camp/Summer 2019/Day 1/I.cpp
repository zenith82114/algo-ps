/*
 * Petrozavodsk Programming Camp, Summer 2019, Day 1: Songyang Chen Contest 2
 * I. Three Investigators
 * QOJ 7586
 *
 * combinatorics; RSK correspondence, Greene's theorem
 * Date: 2026.6.17
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;

map<int, i64> tableau[5];
i64 ans;

void row_insert(int i, int x, int cx) {
    if (i >= 5) return;
    auto& row = tableau[i];

    while (cx > 0) {
        auto lb = row.upper_bound(x);

        if (lb == row.end()) {
            if (lb != row.begin()) {
                auto p = prev(lb);
                if (p->first == x) p->second += cx;
                else row.emplace_hint(lb, x, cx);
            }
            else row.emplace_hint(lb, x, cx);
            ans += cx;
            return;
        }

        auto [y, cy] = *lb;
        int d = min<i64>(cx, cy);

        if (lb != row.begin()) {
            auto p = prev(lb);
            if (p->first == x) p->second += d;
            else row.emplace_hint(lb, x, d);
        }
        else row.emplace_hint(lb, x, d);

        if (cy == d) row.erase(lb); else lb->second -= d;

        row_insert(i+1, y, d);
        cx -= d;
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int tc; cin >> tc;
    while (tc--) {
        for (auto& t : tableau) t.clear();
        ans = 0;

        int n; cin >> n;
        while (n--) {
            int x; cin >> x;
            row_insert(0, x, x);
            cout << ans << ' ';
        }
        cout << '\n';
    }

    return 0;
}
