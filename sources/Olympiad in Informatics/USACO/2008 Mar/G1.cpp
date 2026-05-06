/*
 * USA Computing Olympiad, USACO March 2008 Contest, Gold 1. Land Acquisition
 * BOJ 6171
 * JUNGOL 1878
 *
 * convex hull trick
 * Date: 2022.12.28
 */

#include<bits/stdc++.h>
using namespace std;

using i64 = int64_t;
struct Line {
    i64 y0, m;
    Line(i64 y0, i64 m): y0(y0), m(m) {};
};
inline i64 cx(const Line& a, const Line& b) {
    return (b.y0 - a.y0)/(a.m - b.m);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int N; cin >> N;

    struct Item { int w, h; };
    vector<Item> A(N);
    for (auto& [w, h] : A) cin >> w >> h;
    sort(A.begin(), A.end(), [](const Item& a, const Item& b) {
        return a.w != b.w? a.w < b.w : a.h > b.h;
    });
    vector<Item> tmp;
    for (const auto& a : A) {
        while (!tmp.empty()) {
            const auto& b = tmp.back();
            if (b.w <= a.w && b.h <= a.h) tmp.pop_back();
            else break;
        }
        tmp.emplace_back(a);
    }
    A.swap(tmp);
    N = A.size();

    i64 dp = (i64)A[0].w * A[0].h;
    deque<Line> hl;
    int sz = 0;

    for (int i = 1; i < N; ++i) {
        Line ln(dp, A[i].h);

        while (sz > 1 && cx(ln, hl[sz-1]) <= cx(hl[sz-1], hl[sz-2]))
            sz--, hl.pop_back();
        sz++, hl.emplace_back(ln);

        while (sz > 1 && cx(hl[1], hl[0]) < A[i].w)
            sz--, hl.pop_front();
        dp = hl[0].y0 + hl[0].m * A[i].w;
        dp = min(dp, (i64)A[i].w * A[0].h);
    }

    cout << dp;
    return 0;
}
