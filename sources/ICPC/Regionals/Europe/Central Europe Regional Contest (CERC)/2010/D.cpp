/*
 * ICPC, Regionals, Europe, Central Europe Regional Contest,
 * CERC 2010 D. Defense Lines
 * BOJ 3429
 * JUNGOL 11507
 *
 * segment tree
 * Date: 2023.7.15
 */

#include<bits/stdc++.h>
using namespace std;

class seg_tree {
    vector<int> ar;
    int N;
public:
    seg_tree(int sz) {
        N = 1; while (N < sz) N <<= 1;
        ar.resize(N<<1);
    }
    void update(int i, int x) {
        for (ar[i |= N] = x; i > 1; i >>= 1)
            ar[i>>1] = max(ar[i], ar[i^1]);
    }
    int query(int i) {
        if (i < 0) return 0;
        int j = i|N; i = N;
        int ans = 0;
        for (; i <= j; i >>= 1, j >>= 1) {
            if ( i&1) ans = max(ans, ar[i++]);
            if (~j&1) ans = max(ans, ar[j--]);
        }
        return ans;
    }
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);

    int TC; cin >> TC;
    while (TC--) {
        int N; cin >> N;
        vector<int> v(N); for (int& a : v) cin >> a;
        vector<int> s(N), e(N);
        e[0] = 1;
        for (int i = 1; i < N; ++i) {
            e[i] = v[i-1] < v[i]? e[i-1] + 1 : 1;
        }
        s[N-1] = 1;
        for (int i = N-2; i > -1; --i) {
            s[i] = v[i] < v[i+1]? s[i+1] + 1 : 1;
        }

        vector<int> w(N); iota(w.begin(), w.end(), 0);
        sort(w.begin(), w.end(), [&] (const int& i, const int& j) {
            return v[i] != v[j]? v[i] < v[j] : i > j;
        });

        seg_tree segt(N);

        int ans = 0;
        for (int j : w) {
            int x = segt.query(j - 1);
            ans = max(ans, x + s[j]);
            segt.update(j, e[j]);
        }
        cout << ans << '\n';
    }

    return 0;
}
