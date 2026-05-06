/*
 * 한국정보올림피아드, KOI 2003, 중등부 2. 경찰차
 * BOJ 2618
 * JUNGOL 1820
 *
 * DP
 * Date: 2021.7.26
 */

#include<iostream>
#include<algorithm>
using namespace std;

typedef pair<int, int> coord;
constexpr auto call_1 = true, call_2 = false;

int dp[1001][1001];
coord pos[1001];
bool call[1001][1001];

inline int dist(coord& a, coord& b) {
    return abs(a.first - b.first) + abs(a.second - b.second);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, W; cin >> N >> W;
    for (int w = 1; w <= W; ++w) {
        int i, j; cin >> i >> j;
        pos[w] = make_pair(i, j);
    }

    fill_n(dp[W], W + 1, 0);
    for (int i = W - 1; i >= 0; --i) {
        dp[i][W] = 0;
        auto pos_i = i ? pos[i] : make_pair(1, 1);
        for (int j = W - 1; j >= 0; --j) {
            if (i && i == j) continue;
            auto pos_j = j ? pos[j] : make_pair(N, N);
            int k = max(i, j) + 1;
            int dp1 = dist(pos_i, pos[k]) + dp[k][j];
            int dp2 = dist(pos_j, pos[k]) + dp[i][k];
            if (dp1 < dp2) {
                dp[i][j] = dp1;
                call[i][j] = call_1;
            } else {
                dp[i][j] = dp2;
                call[i][j] = call_2;
            }
        }
    }
    cout << dp[0][0] << '\n';

    int i = 0, j = 0, k = 1;
    while (i < W && j < W) {
        if (call[i][j] == call_1) {
            cout << "1\n";
            i = k++;
        } else {
            cout << "2\n";
            j = k++;
        }
    }

    return 0;
}
