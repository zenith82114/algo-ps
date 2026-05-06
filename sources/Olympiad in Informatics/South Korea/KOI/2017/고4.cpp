/*
 * 한국정보올림피아드, KOI 2017, 고등부 4. 조개 줍기
 * BOJ 14870
 * JUNGOL 3081
 *
 * DP, segment tree, two pointers
 * Date: 2023.7.26
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;

class seg_tree {
    vector<i64> ar;
    int N;
public:
    void init(const vector<i64>& v) {
        int sz = v.size();
        N = 1; while (N < sz) N <<= 1;
        ar.resize(N<<1);
        copy(v.begin(), v.end(), ar.begin() + N);
    }
    void add(int i, int j, int k) {
        for (i |= N, j |= N; i <= j; i >>= 1, j >>= 1) {
            if ( i&1) ar[i++] += k;
            if (~j&1) ar[j--] += k;
        }
    }
    i64 query(int i) const {
        i64 ans = 0;
        for (i |= N; i; i >>= 1) ans += ar[i];
        return ans;
    }
} segt[1501];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);

    int N; cin >> N;
    vector<i64> dp0(N+1), dp1(N+1);
    i64 ans = 0;

    segt[0].init(dp1);
    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= N; ++j) {
            cin >> dp1[j];
            dp1[j] += max(dp0[j], dp1[j-1]);
            ans += dp1[j];
        }
        segt[i].init(dp1);
        dp1.swap(dp0);
    }
    cout << ans << '\n';

    vector<int> st(N+1), ed(N+1);
    auto f = [] (int i, int j) { return segt[i].query(j); };

    for (int q = 0; q < N; ++q) {
        char op; int i0, j0; cin >> op >> i0 >> j0;
        int k = op == 'U'? +1 : -1;

        st[i0] = ed[i0] = j0;
        for (int& e = ed[i0]; e < N; ++e) {
            auto left = f(i0, e);
            auto up = f(i0-1, e+1);
            if (left < up || left + k < up) break;
        }

        int i1 = i0+1;
        for (; i1 <= N; ++i1) {
            int& s = st[i1] = st[i1-1]; int& e = ed[i1] = ed[i1-1];
            for (; s <= N; ++s) {
                auto left = f(i1, s-1);
                auto up = f(i1-1, s);
                if (left <= up && left <= up + k) break;
            }
            if (s > e) break;
            for (; e < N; ++e) {
                auto left = f(i1, e);
                auto up = f(i1-1, e+1);
                if (left < up || left + k < up) break;
            }
        }

        for (int i = i0; i < i1; ++i) {
            ans += k * (ed[i] - st[i] + 1);
            segt[i].add(st[i], ed[i], k);
        }
        cout << ans << '\n';
    }

    return 0;
}
