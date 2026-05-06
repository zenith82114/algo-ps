/*
 * Croatian Highschool Competitions in Informatics, 2006, Final Exam #2 B. lubenica
 * BOJ 3176 - sparse table LCA
 * Date: 2021.8.25
 */

#include<iostream>
#include<algorithm>
#include<bitset>
#include<vector>
using namespace std;
constexpr int maxN = 100000, maxlgN = 16;

vector<pair<int, int>> tree[maxN + 1];
int parent[maxlgN + 1][maxN + 1],
minW[maxlgN + 1][maxN + 1], maxW[maxlgN + 1][maxN + 1];
int depth[maxN + 1];
bitset<maxN + 1> visited;

void dfs(int v, int pv) {
    visited.set(v);
    parent[0][v] = pv;
    depth[v] = depth[pv] + 1;
    for (auto& e : tree[v]) {
        int u = e.first, w = e.second;
        if (u != pv && !visited.test(u)) {
            minW[0][u] = maxW[0][u] = w;
            dfs(u, v);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int N; cin >> N;
    int lgN = [](int n) {
        int k = 0;
        while (n >>= 1) ++k;
        return k;
    }(N);
    for (int n = 1; n < N; ++n) {
        int x, y, w; cin >> x >> y >> w;
        tree[x].push_back({ y, w });
        tree[y].push_back({ x, w });
    }

    dfs(1, 0);
    for (int k = 0; k < lgN; ++k) {
        for (int x = 1; x <= N; ++x) {
            int& y = parent[k][x];
            if (y) {
                parent[k + 1][x] = parent[k][y];
                minW[k + 1][x] = min(minW[k][x], minW[k][y]);
                maxW[k + 1][x] = max(maxW[k][x], maxW[k][y]);
            }
        }
    }

    int K; cin >> K;
    while (K--) {
        int x, y; cin >> x >> y;
        int m = maxN + 1, M = 0;
        if (depth[x] < depth[y])
            swap(x, y);
        for (int D = depth[x] - depth[y], k = 0;
            D; D >>= 1, ++k) {
            if (D & 1) {
                m = min(m, minW[k][x]);
                M = max(M, maxW[k][x]);
                x = parent[k][x];
            }
        }
        if (x != y) {
            for (int k = lgN; k >= 0; --k) {
                if (parent[k][x] != parent[k][y]) {
                    m = min({ m, minW[k][x], minW[k][y] });
                    M = max({ M, maxW[k][x], maxW[k][y] });
                    x = parent[k][x];
                    y = parent[k][y];
                }
            }
            m = min({ m, minW[0][x], minW[0][y] });
            M = max({ M, maxW[0][x], maxW[0][y] });
        }
        cout << m << ' ' << M << '\n';
    }

    return 0;
}
