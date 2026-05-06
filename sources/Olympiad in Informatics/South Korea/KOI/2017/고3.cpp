/*
 * 한국정보올림피아드, KOI 2017, 고등부 3. 요리 강좌
 * BOJ 14869
 * JUNGOL 3080
 *
 * DP with deque
 * Date: 2023.7.6
 */

#include<bits/stdc++.h>
using namespace std;
using ii = pair<int, int>;

constexpr int inf = 1e9;

// ps[i][j] = price sum of courses [1..i] at academy j
int ps[3001][3001];

// dp[i][j] = min cost {
//    courses [1..i] taken
//    # of courses taken is in range [S..E] for each academy
//    course i taken at academy j, but not i+1
//    inf if impossible
// }
int dp[3001][3001];

int ban[3001];
deque<ii> dq[3001];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);

    int N, M, S, E, T; cin >> N >> M >> S >> E >> T;
    for (int j = 1; j <= N; ++j) {
        ps[0][j] = 0;
        for (int i = 1; i <= M; ++i) {
            cin >> ps[i][j];
            ps[i][j] += ps[i-1][j];
        }
    }
    for (int j = 1; j <= N; ++j) cin >> ban[j];

    for (int i = 1; i <= M; ++i) {
        for (int j = 1; j <= N; ++j) {
            dp[i][j] = (S <= i && i <= E? ps[i][j] : inf);
            if (!dq[j].empty())
                dp[i][j] = min(dp[i][j], dq[j].front().first + ps[i][j] + T);
        }

        if (i+1 >= 2*S) {
            ii a0 = { inf, inf }; ii a1 = a0; ii a2 = a0;
            for (int j = 1; j <= N; ++j) {
                ii x { dp[i-S+1][j], j };
                if      (x < a0) { swap(a2, a1); swap(a1, a0); a0 = x; }
                else if (x < a1) { swap(a2, a1); a1 = x; }
                else if (x < a2) { a2 = x; }
            }
            auto [y0, j0] = a0;
            auto [y1, j1] = a1;
            auto [y2, j2] = a2;
            for (int j = 1; j <= N; ++j) {
                int y;
                if (j0 != j && j0 != ban[j]) y = y0;
                else if (j1 != j && j1 != ban[j]) y = y1;
                else y = y2;
                y -= ps[i-S+1][j];

                auto& dqj = dq[j];
                if (!dqj.empty() && dqj.front().second == i-E) dqj.pop_front();
                while (!dqj.empty() && dqj.back().first >= y) dqj.pop_back();
                dqj.emplace_back(y, i-S+1);
            }
        }
    }

    int ans = inf;

    // S or more courses taken at the last academy
    for (int j = 1; j <= N; ++j) ans = min(ans, dp[M][j]);

    // less than S courses taken at the last academy
    for (int i = max(S, M-S+1); i < M; ++i) {
        ii a0 = { inf, inf }; ii a1 = a0; ii a2 = a0;
        for (int j = 1; j <= N; ++j) {
            ii x { dp[i][j], j };
            if      (x < a0) { swap(a2, a1); swap(a1, a0); a0 = x; }
            else if (x < a1) { swap(a2, a1); a1 = x; }
            else if (x < a2) { a2 = x; }
        }
        auto [y0, j0] = a0;
        auto [y1, j1] = a1;
        auto [y2, j2] = a2;
        for (int j = 1; j <= N; ++j) {
            int y;
            if (j0 != j && j0 != ban[j]) y = y0;
            else if (j1 != j && j1 != ban[j]) y = y1;
            else y = y2;
            ans = min(ans, y - ps[i][j] + ps[M][j] + T);
        }
    }

    cout << ans;
    return 0;
}
