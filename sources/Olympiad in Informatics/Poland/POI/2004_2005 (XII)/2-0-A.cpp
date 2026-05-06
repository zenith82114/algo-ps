/*
 * Polish Olympiad in Informatics, POI 2004/2005, Stage 2 Day 0 A. A Journey to Mars
 * BOJ 7962 - prefix sum, sliding window minimum with deque
 * Date: 2025.3.26
 */

#include<bits/stdc++.h>
using namespace std;

int n, t = 0;
array<int, 1'000'004> p, d;
bitset<1'000'004> ans;

void solve(int rev) {
    deque<pair<int64_t, int> > q;
    int64_t s = 0;
    for (int i = 0; i < n; ++i) {
        s += p[i] - d[i];
        while (!q.empty() && s < q.back().first) q.pop_back();
        q.emplace_back(s, i);
    }
    if (q.front().first >= 0) ans.set(0);

    for (int i = 0; i < n - 1; ++i) {
        s += p[i] - d[i];
        while (!q.empty() && s < q.back().first) q.pop_back();
        if (!q.empty() && q.front().second == i) q.pop_front();
        q.emplace_back(s, i);
        if (q.front().first >= s - t) ans.set(rev? n - i - 1 : i + 1);
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> p[i] >> d[i];
        t += p[i] - d[i];
    }
    solve(0);
    reverse(p.begin() + 1, p.begin() + n);
    reverse(d.begin(), d.begin() + n);
    solve(1);
    for (int i = 0; i < n; ++i) cout << (ans[i]? "TAK" : "NIE") << '\n';

    return 0;
}
