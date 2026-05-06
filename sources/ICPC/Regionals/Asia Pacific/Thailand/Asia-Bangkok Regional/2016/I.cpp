/*
 * ICPC, Regionals, Asia Pacific, Thailand,
 * 2016 ACM-ICPC Asia-Bangkok Regional Contest I. Sky Tax
 * BOJ 13896 - sparse table LCA
 * Date: 2022.11.14
 */

#include<bits/stdc++.h>
using namespace std;

#define MAXN 100'001
#define MAXLGN 17

array<vector<int>, MAXN> tree;
array<array<int, MAXN>, MAXLGN> par;
array<int, MAXN> dep, sz;

void dfs(int pu, int u) {
    dep[u] = dep[pu] + 1;
    par[0][u] = pu;
    sz[u] = 1;
    for (const int& v : tree[u]) if (v != pu) {
        dfs(u, v);
        sz[u] += sz[v];
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int TC; cin >> TC;
    for (int tc = 1; tc <= TC; tc++) {
        cout << "Case #" << tc << ":\n";

        int N, Q, R; cin >> N >> Q >> R;

        for (int i = 1; i <= N; ++i)
            tree[i].clear();
        for (int i = 1; i < N; ++i) {
            int a, b; cin >> a >> b;
            tree[a].emplace_back(b);
            tree[b].emplace_back(a);
        }

        dep[0] = -1;
        dfs(0, 1);

        const int lgN = [](int n) {
            int k = 0;
            for (; n > 1; n >>= 1) ++k;
            return k;
        }(N);
        for (int i = 1; i <= lgN; ++i)
        for (int u = 1; u <= N; ++u)
            par[i][u] = par[i-1][par[i-1][u]];

        while (Q--) {
            int s, X; cin >> s >> X;

            if (s == 0) R = X;
            else {
                if (X == R)
                    cout << N << '\n';
                else if (dep[R] <= dep[X])
                    cout << sz[X] << '\n';
                else {
                    int h = dep[R] - dep[X];
                    int r = R;
                    for (int i = lgN; ~i; --i) {
                        if ((1<<i) < h) {
                            h -= (1<<i);
                            r = par[i][r];
                        }
                    }
                    if (par[0][r] == X)
                        cout << (N - sz[r]) << '\n';
                    else
                        cout << sz[X] << '\n';
                }
            }
        }
    }

    return 0;
}
