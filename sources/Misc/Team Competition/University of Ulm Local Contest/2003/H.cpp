/*
 * University of Ulm Local Contest 2003 H. Largest Rectangle in a Histogram
 * BOJ 1725 - monotone stack
 * Date: 2022.9.22
 */

#include<bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    using pii = pair<int, int>;

    int N; cin >> N;
    stack<pii> stk;
    int ans = 0;

    for (int i = 0; i < N; ++i) {
        int h; cin >> h;
        int it = i;
        while (!stk.empty() && h < stk.top().second) {
            it = stk.top().first;
            int& ht = stk.top().second;
            ans = max(ans, ht * (i - it));
            stk.pop();
        }
        stk.emplace(it, h);
    }
    while (!stk.empty()) {
        auto& [it, ht] = stk.top();
        ans = max(ans, ht * (N - it));
        stk.pop();
    }

    cout << ans;
    return 0;
}
