/*
 * 한국정보올림피아드, KOI 1999, 중등부 3. 같은 길이 막대기 만들기
 * JUNGOL 1552
 *
 * ICPC, Regionals, Europe, Central Europe Regional Contest,
 * CERC 1995 H. Sticks
 * JUNGOL 2170
 *
 * backtracking, heuristics (NP-complete)
 * Date: 2026.5.24
 */

#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

// How many backtracking nodes to explore per restart;
// low enough that infeasible k values are abandoned quickly,
// high enough that feasible k values are found reliably
const int NODE_LIMIT = 1e4;

int n, k;
int a[50], ssum[50], gid[50];
bitset<50> used;
int nodes;

bool go(int len, int start, int g) {
    // node limit exceeded
    if (++nodes > NODE_LIMIT) return false;
    // solution found
    if ((int)used.count() == n) return true;
    // current group complete; start next one
    if (len == k) return go(0, 0, g + 1);

    int min_unused = 0;
    for (int i = n - 1; i >= 0; --i) if (!used[i]) {
        min_unused = a[i]; break;
    }

    for (int i = start; i < n; ++i) {
        // gap too large
        if (len + ssum[i] < k) return false;

        if (used[i] || len + a[i] > k) continue;

        // duplicate skip
        if (i > 0 && !used[i-1] && a[i-1] == a[i]) continue;

        // gap too small
        int gap = k - (len + a[i]);
        if (gap > 0 && gap < min_unused) continue;

        // try adding i
        used.set(i); gid[i] = g;
        if (go(len + a[i], i + 1, g)) return true;
        used.reset(i);

        // first-fit failure
        if (len == 0) return false;

        // exact-fit failure
        if (len + a[i] == k) return false;
    }

    return false;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;
    for (int i = 0; i < n; ++i) cin >> a[i];

    sort(a, a + n, greater<int>());
    int s = accumulate(a, a + n, 0);
    ssum[n-1] = a[n-1];
    for (int i = n-2; i >= 0; --i) ssum[i] = ssum[i+1] + a[i];

    for (k = a[0]; k <= s/2; ++k) if (s % k == 0) {
        used.reset();
        nodes = 0;

        if (go(0, 0, 0)) {
            cout << k << '\n';
            for (int g = 0; g < s/k; ++g) {
                for (int i = 0; i < n; ++i) if (gid[i] == g) cout << a[i] << ' ';
                cout << '\n';
            }
            return 0;
        }
    }

    // k == s
    cout << s << '\n';
    for (int i = 0; i < n; ++i) cout << a[i] << ' ';
    return 0;
}
