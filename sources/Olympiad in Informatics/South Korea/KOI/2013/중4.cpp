/*
 * 한국정보올림피아드, KOI 2013, 중등부 4. 수족관 2
 * BOJ 8985
 * JUNGOL 2639
 *
 * DnC, segment tree
 * Date: 2023.6.18
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;
using ii = pair<int, int>;

vector<ii> rp;
vector<int> psum;

class seg_tree {
    vector<ii> ar;
    int N;
public:
    void init() {
        int sz = rp.size();
        N = 1; while (N < sz) N *= 2;
        ar.resize(2*N);
        for (int i = 0; i < sz; ++i)
            ar[N|i] = { rp[i].second, i };
        for (int i = sz; i < N; ++i)
            ar[N|i] = { INT_MAX, -1 };
        for (int i = N-1; i; --i)
            ar[i] = min(ar[i<<1], ar[i<<1|1]);
    }
    ii query(int i, int j) {
        ii ans { INT_MAX, -1 };
        for (i |= N, j |= N; i <= j; i >>= 1, j >>= 1) {
            if ( i&1) ans = min(ans, ar[i++]);
            if (~j&1) ans = min(ans, ar[j--]);
        }
        return ans;
    }
} segt;

pair<double, i64> dnc(int l, int r, int y_prev) {
    auto [y_min, k] = segt.query(l, r);
    int holes = psum[r] - (l? psum[l-1] : 0);
    if (!holes) return { 0., 0 };

    i64 volume = (i64)(y_min - y_prev) * (rp[r].first - (l? rp[l-1].first : 0));
    double time = (double)volume / holes;
    double time_l = 0., time_r = 0.;
    if (l < k) {
        auto ret = dnc(l, k-1, y_min);
        time_l = ret.first;
        volume += ret.second;
    }
    if (k < r) {
        auto ret = dnc(k+1, r, y_min);
        time_r = ret.first;
        volume += ret.second;
    }
    return { time + max(time_l, time_r), volume };
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);

    int N; cin >> N;
    int x, y; cin >> x >> y;
    for (int i = 3; i < N; i += 2) {
        cin >> x >> y >> x >> y;
        rp.emplace_back(x, y);
    }
    cin >> x >> y;
    N = rp.size();

    int K; cin >> K;
    psum.resize(N);
    while (K--) {
        cin >> x >> y >> x >> y;
        int i = lower_bound(rp.begin(), rp.end(), make_pair(x, y)) - rp.begin();
        ++psum[i];
    }
    partial_sum(psum.begin(), psum.end(), psum.begin());

    segt.init();

    i64 vol_init = 0LL;
    for (int i = 0; i < N; ++i) {
        const auto& [x, y] = rp[i];
        vol_init += (i64)y * (x - (i? rp[i-1].first : 0));
    }
    auto ans = dnc(0, N-1, 0);
    cout << fixed << setprecision(2) << ans.first << '\n' << vol_init - ans.second;

    return 0;
}
