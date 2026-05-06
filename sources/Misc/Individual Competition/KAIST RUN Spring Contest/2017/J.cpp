/*
 * 2017 KAIST RUN Spring Contest (HYEA Cup) J. Communism
 * BOJ 14560 - sorting, two pointers
 * Date: 2024.6.16
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;

void go(vector<i64>& s, const vector<i64>& v) {
    constexpr i64 inf = INT64_MAX;
    struct T { i64 val; int idx, k; } ar[3];
    vector<i64> t;

    s.emplace_back(0);
    for (i64 x : v) {
        s.swap(t); s.clear();
        int m = t.size();
        s.reserve(3*m);
        for (int i = 0; i < 3; ++i) {
            ar[i].val = t[0] + (i - 1)*x;
            ar[i].idx = 0;
            ar[i].k = i - 1;
        }
        while (ar[0].idx < m) {
            s.emplace_back(ar[0].val);
            ar[0].val = ++ar[0].idx < m? t[ar[0].idx] + ar[0].k*x : inf;
            if (ar[0].val > ar[1].val) {
                swap(ar[0], ar[1]);
                if (ar[1].val > ar[2].val) swap(ar[1], ar[2]);
            }
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n; cin >> n;
    vector<i64> v(n/2), s1, s2;
    for (i64& x : v) cin >> x;
    go(s1, v);
    v.resize(n - n/2);
    for (i64& x : v) cin >> x;
    go(s2, v);

    i64 d; cin >> d;
    int m = s2.size();
    int lo = 0, hi = 0;
    i64 ans = 0;
    for (auto rit = s1.rbegin(); rit != s1.rend(); ++rit) {
        i64 x = *rit;
        while (lo < m && x + s2[lo] < -d) ++lo;
        while (hi < m && x + s2[hi] <= d) ++hi;
        ans += hi - lo;
    }
    cout << ans;
    return 0;
}
