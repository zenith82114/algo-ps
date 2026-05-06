/*
 * ICPC Japanese Alumni Group, JAG Spring Contest 2015 L. Wall Making Game
 * BOJ 11717 - Sprague-Grundy theorem, DP
 * Date: 2023.1.12
 */

#include<bits/stdc++.h>
using namespace std;

char A[20][20];
int memo[20][20][20][20];

int grundy_num(int u, int d, int l, int r) {
    if (u > d || l > r) return 0;
    int& ans = memo[u][d][l][r];
    if (ans != -1) return ans;

    set<int> s;
    for (int i = u; i <= d; ++i)
    for (int j = l; j <= r; ++j) if (A[i][j] == '.')
        s.emplace(
            grundy_num(u, i-1, l, j-1) ^ grundy_num(u, i-1, j+1, r) ^
            grundy_num(i+1, d, l, j-1) ^ grundy_num(i+1, d, j+1, r));

    ans = 0;
    while (s.find(ans) != s.end()) ans++;
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int H, W; cin >> H >> W;
    for (int i = 0; i < H; ++i)
    for (int j = 0; j < W; ++j) cin >> A[i][j];

    memset(memo, -1, sizeof memo);
    cout << (grundy_num(0, H-1, 0, W-1)? "First" : "Second") << '\n';

    return 0;
}
