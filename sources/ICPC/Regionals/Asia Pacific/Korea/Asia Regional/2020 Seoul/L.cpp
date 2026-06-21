/*
 * ICPC, Regionals, Asia Pacific, Korea, Asia Regional - Seoul 2020
 * L. Two Buildings
 * QOJ 2533
 *
 * DnC optimization
 * Date: 2026.6.21
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;
using ii = pair<int, int>;

const int MAXN = 1e6;
int a[MAXN];
vector<int> p, q;
i64 ans = 0;

void dnc(int il, int ir, int jl, int jr) {
    int i = (il + ir)/2;
    pair<i64, int> best(-1, -1);

    for (int j = jl; j < jr; ++j) if (p[i] < q[j]) {
        best = max(best, make_pair((i64)(a[p[i]] + a[q[j]])*(q[j] - p[i]), j));
    }

    ans = max(ans, best.first);
    if (il + 1 < ir) {
        dnc(il, i, jl, best.second + 1);
        dnc(i, ir, best.second, jr);
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n; cin >> n;
    for (int i = 0; i < n; ++i) cin >> a[i];

    p.push_back(0);
    for (int i = 1; i < n; ++i) if (a[p.back()] < a[i]) p.push_back(i);
    q.push_back(n-1);
    for (int i = n-2; i > -1; --i) if (a[q.back()] < a[i]) q.push_back(i);
    reverse(begin(q), end(q));

    dnc(0, p.size(), 0, q.size());
    cout << ans;
    return 0;
}
