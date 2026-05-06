/*
 * 한국정보올림피아드, KOI 2011, 고등부 3. 트리 분할
 * BOJ 2454
 * JUNGOL 2505
 *
 * greedy, tree DP
 * Date: 2024.8.3
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;
const int
    MAXN = 3e5 + 4,
    INF = 1e9;

int k;
vector<int> tree[MAXN];

pair<int, int> dfs(int px, int x) {
    int sum_a = 0;
    int min1_b = INF, min2_b = INF;

    for (int y : tree[x]) if (y != px) {
        auto [a, b] = dfs(x, y);
        sum_a += a;
        if (min1_b > b) min2_b = min1_b, min1_b = b;
        else if (min2_b > b) min2_b = b;
    }

    if (min1_b + min2_b <= k) return { sum_a - 1, INF };
    if (min1_b <= k) return { sum_a, min1_b + 1 };
    return { sum_a + 1, 1 };
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n; cin >> n >> k;
    for (int i = 1; i < n; ++i) {
        int x, y; cin >> x >> y;
        tree[x].push_back(y);
        tree[y].push_back(x);
    }

    cout << dfs(0, 1).first;
    return 0;
}
