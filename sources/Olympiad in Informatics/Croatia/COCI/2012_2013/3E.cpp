/*
 * Croatian Open Competition in Informatics, COCI 2012/2013, Contest #3 E. HERKABE
 * BOJ 3080
 * JUNGOL 3717
 *
 * DnC
 * Date: 2024.2.25
 */

#include<bits/stdc++.h>
using namespace std;

inline void mul_mod(int& x, int y) {
    x = (int)((int64_t)x*y%1'000'000'007);
}

int dnc(const vector<string>& v, int l, int r, int pos) {
    if (l == r) return 1;

    int m = 0;
    int ans = 1;
    if ((int)v[l].size() == pos) { ++l; ++m; }

    for (int s = l, e = l; s < r; s = e) {
        while (e < r && v[s][pos] == v[e][pos]) ++e;
        mul_mod(ans, dnc(v, s, e, pos+1));
        mul_mod(ans, ++m);
    }
    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n; cin >> n;
    vector<string> v(n); for (auto& w : v) cin >> w;
    sort(v.begin(), v.end());
    cout << dnc(v, 0, n, 0);
    return 0;
}
