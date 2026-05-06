/*
 * 한국정보올림피아드, KOI 2022 2차대회, 중등부 4/고등부 3. 레벨 업
 * BOJ 25405
 * JUNGOL 5202
 *
 * binary search
 * Date: 2023.7.2
 * cf. https://www.youtube.com/watch?v=Y0WgGnnIWbk @ 2:25:25~
 */

#include<bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    using i64 = int64_t;

    int N; cin >> N;
    vector<int> v(N); for (int& a : v) cin >> a;
    sort(v.begin(), v.end());
    int M, K; cin >> M >> K;
    i64 S = (i64)M * K;

    int l = v[K-1], r = v[K-1] + M + 1;
    i64 s = 0;
    while (l < r) {
        int m = (l>>1) + (r>>1) + (l&r&1);
        s = 0;
        for (int a : v) {
            if (a >= m) break;
            s += min(M, m - a);
        }
        if (s <= S) l = m+1; else r = m;
    }

    const int x = l-1;
    for (int& a : v) {
        if (a >= x) break;
        S -= min(M, x - a);
        a = min(a + M, x);
    }
    r = upper_bound(v.begin(), v.end(), x) - v.begin();
    for (int i = 1; i <= S; ++i) ++v[r - i];
    for (int a : v) cout << a << ' ';
    return 0;
}
