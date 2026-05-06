/*
 * 한국정보올림피아드, KOI 2005, 고등부 3. 소방차
 * BOJ 2586
 * JUNGOL 2017
 *
 * slope trick
 * Date: 2023.9.12
 */

#include<bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);

    vector<int> X(1'000'005);
    int n, m; cin >> n >> m;
    while (n--) { int i; cin >> i; ++X[i]; }
    while (m--) { int i; cin >> i; --X[i]; }
    partial_sum(X.begin(), X.end(), X.begin());

    priority_queue<int> pq;
    int64_t y0 = 0;
    for (int x : X) {
        y0 += abs(x);
        if (x < 0) pq.emplace(0);
        else { pq.emplace(x); pq.emplace(x); }
        pq.pop();
    }
    while (!pq.empty()) {
        y0 -= min(pq.top(), X.back());
        pq.pop();
    }
    cout << y0;
    return 0;
}
