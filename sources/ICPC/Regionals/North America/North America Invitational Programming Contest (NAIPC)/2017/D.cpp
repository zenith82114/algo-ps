/*
 * North American Invitational Programming Contest, NAIPC 2017 D. Heaps from Trees
 * JUNGOL 3612
 *
 * slope trick, smaller to larger
 * Date: 2026.5.23
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;
const int MAXN = 3e5 + 4;

multiset<int> ms[MAXN];
array<int, MAXN> val, par;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n; cin >> n;
    for (int x = 1; x <= n; ++x) cin >> val[x] >> par[x];

    for (int x = n; x > 0; --x) {
        auto f = ms[x].lower_bound(val[x]);
        if (f != ms[x].end()) ms[x].erase(f);
        ms[x].emplace(val[x]);

        int px = par[x];
        if (ms[x].size() > ms[px].size()) ms[x].swap(ms[px]);
        ms[px].merge(ms[x]);
    }
    cout << ms[0].size();
    return 0;
}
