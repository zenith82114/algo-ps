/*
 * Asia-Pacific Informatics Olympiad, APIO 2010 A. Commando
 * BOJ 4008
 * JUNGOL 2553
 *
 * convex hull trick
 * Date: 2022.2.15
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;

struct Line {
    i64 y0, m;
    Line(i64 y0, i64 m) : y0(y0), m(m) {};
};
inline i64 cx(const Line& a, const Line& b) {
    return (b.y0 - a.y0)/(a.m - b.m);
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);

    int N; cin >> N;
    i64 a, b, c; cin >> a >> b >> c;
    vector<i64> S(N);
    for (i64& s : S) cin >> s;
    partial_sum(S.begin(), S.end(), S.begin());

    i64 dp = a*S[0]*S[0] + b*S[0] + c;
    int sz = 1;
    deque<Line> hl;
    hl.emplace_back(0, 0);
    for (int n = 0; n+1 < N; ++n) {
        Line line(dp + a*S[n]*S[n] - b*S[n], -2*a*S[n]);

        if (sz && hl[sz-1].m == line.m && hl[sz-1].y0 <= line.y0)
            sz--, hl.pop_back();
        while (sz > 1 && cx(line, hl[sz-1]) <= cx(hl[sz-1], hl[sz-2]))
            sz--, hl.pop_back();
        sz++, hl.emplace_back(line);

        while (sz > 1 && cx(hl[1], hl[0]) < S[n+1])
            sz--, hl.pop_front();
        dp = hl[0].y0 + hl[0].m*S[n+1] + a*S[n+1]*S[n+1] + b*S[n+1] + c;
    }

    cout << dp << '\n';
    return 0;
}
