/*
 * Open Cup 2019/2020 Stage 18: Grand Prix of Bytedance F. Subset Sum
 * BOJ 23492 - Pisinger's O(nW) knapsack
 * Date: 2024.2.19
 */

#include<bits/stdc++.h>
using namespace std;

int w[20001];
int s[2][40001];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int tc; cin >> tc; while (tc--) {
        int n, C; cin >> n >> C;
        int W = -1;
        int top = 0;
        for (int i = 1; i <= n; ++i) {
            cin >> w[top+1];
            if (w[top+1] > C) continue;
            W = max(W, w[++top]);
        }
        if (!top) { cout << "0\n"; continue; }
        n = top;

        int b = 0, w_bar = 0;
        while (b+1 <= n && w_bar <= C) w_bar += w[++b];
        if (w_bar <= C) { cout << w_bar << '\n'; continue; }
        w_bar -= w[b];

        auto dp = [C, W] (int t, int u) -> int& { return s[t][u-C+W]; };

        for (int u = C-W+1; u <= C; ++u) dp(1, u) = 0;
        for (int u = C+1; u <= C+W; ++u) dp(1, u) = 1;
        dp(1, w_bar) = b;

        for (int t = b; t <= n; ++t) {
            for (int u = C-W+1; u <= C+W; ++u) {
                dp(0, u) = dp(1, u);
            }
            for (int u = C-W+1; u <= C; ++u) {
                dp(1, u+w[t]) = max(dp(1, u+w[t]), dp(0, u));
            }
            for (int u = C+w[t]; u >= C+1; --u) {
                for (int j = dp(1, u)-1; j >= dp(0, u); --j) {
                    dp(1, u-w[j]) = max(dp(1, u-w[j]), j);
                }
            }
        }

        int ans = C;
        while (dp(1, ans) == 0) --ans;
        cout << ans << '\n';
    }

    return 0;
}
