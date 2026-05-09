/*
 * 한국정보올림피아드, KOI 2005, 중등부 5/고등부 4. 화물열차
 * JUNGOL 1393
 *
 * difference array, sweep line
 * Date: 2026.5.9
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n; cin >> n;
    vector<pair<int, int> > A(n);
    for (auto& [a1, a2] : A) cin >> a1 >> a2;
    int m; cin >> m;
    vector<pair<int, int> > evt;
    while (m--) {
        int b1, b2; cin >> b1 >> b2;
        for (auto [a1, a2] : A) {
            evt.emplace_back(a1 + b1,     +1);
            evt.emplace_back(a1 + b2 + 1, -1);
            evt.emplace_back(a2 + b1 + 1, -1);
            evt.emplace_back(a2 + b2 + 2, +1);
        }
    }
    sort(begin(evt), end(evt));

    pair<i64, int> ans(-1, 0); // max, -argmax
    i64 sum1 = 0, sum2 = 0;

    for (size_t i = 0; i < evt.size(); ) {
        int k = evt[i].first;
        int v = 0;
        while (i < evt.size() && evt[i].first == k) v += evt[i++].second;
        sum1 += v;
        sum2 += 1ll * k * v;
        ans = max(ans, make_pair((k + 1) * sum1 - sum2, -k));

        if (i < evt.size()) {
            int nk = evt[i].first;
            if (k == nk - 1) continue;
            ans = max(ans, make_pair(nk * sum1 - sum2, -nk + 1));
        }
    }

    cout << (-ans.second - 1);
    return 0;
}
