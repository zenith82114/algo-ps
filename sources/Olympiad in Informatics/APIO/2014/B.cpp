/*
 * Asia-Pacific Informatics Olympiad, APIO 2014 B. Split the sequence
 * BOJ 10067
 * JUNGOL 3011
 *
 * convex hull trick
 * Date: 2022.2.15
 */

#include<bits/stdc++.h>
using namespace std;
using ll = long long;

struct Line {
    int id;
    ll y0, m;
    Line(int id, ll y0, ll m) : id(id), y0(y0), m(m) {};
};
inline ll cx(const Line& a, const Line& b) {
    return (b.y0 - a.y0)/(a.m - b.m);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, K; cin >> N >> K;

    vector<ll> S(N);
    cin >> S[0];
    for (int n = 1; n < N; ++n) {
        cin >> S[n];
        S[n] += S[n-1];
    }

    vector<ll> dp0(N), dp1(N);
    vector<vector<int>> tr(K, vector<int>(N));

    for (int k = 0; k < K; ++k) {
        int sz = 0;
        deque<Line> hl;
        swap(dp0, dp1);

        for (int n = 0; n+1 < N; ++n) {
            Line line(n, dp0[n] - S[n] * S[n], S[n]);

            if (sz && hl[sz-1].m == line.m && hl[sz-1].y0 <= line.y0)
                sz--, hl.pop_back();
            while (sz>1 && cx(line, hl[sz-1]) <= cx(hl[sz-1], hl[sz-2]))
                sz--, hl.pop_back();
            sz++, hl.emplace_back(line);

            while (sz>1 && cx(hl[1], hl[0]) < S[n+1])
                sz--, hl.pop_front();
            dp1[n+1] = hl[0].y0 + hl[0].m * S[n+1];
            tr[k][n+1] = hl[0].id;
        }
    }
    cout << dp1[N-1] << '\n';

    vector<int> res;
    for (int k = K-1, n = N-1; ~k; n = tr[k--][n])
        res.push_back(tr[k][n] +1);
    cout << res.back();
    for (int i = (int)res.size() -2; ~i; --i) {
        if (res[i] <= res[i+1])
            res[i] = res[i+1]+1;
        cout << ' ' << res[i];
    }
    cout << '\n';
    return 0;
}
