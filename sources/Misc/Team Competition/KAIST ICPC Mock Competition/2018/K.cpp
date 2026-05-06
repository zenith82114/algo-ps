/*
 * 2018 KAIST 8th ACM-ICPC Mock Competition K. Utilitarianism
 * BOJ 16191 - Aliens trick
 * Date: 2023.2.17
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;
constexpr int SZ = 250'001;

vector<pair<int, int>> tree[SZ];
/*
 * [][0]: not matched
 * [][1]: better(matched, not matched)
 */
i64 val[SZ][2];
int cnt[SZ][2];

void dfs(int pu, int u, i64 lmd) {
    val[u][0] = 0ll;
    cnt[u][0] = 0;
    for (const auto& [v, w] : tree[u]) if (v != pu) {
        dfs(u, v, lmd);
        val[u][0] += val[v][1];
        cnt[u][0] += cnt[v][1];
    }
    val[u][1] = val[u][0];
    cnt[u][1] = cnt[u][0];
    for (const auto& [v, w] : tree[u]) if (v != pu) {
        i64 tval = val[u][0] - val[v][1] + val[v][0] + w - lmd;
        int tcnt = cnt[u][0] - cnt[v][1] + cnt[v][0] + 1;
        if (val[u][1] < tval) {
            val[u][1] = tval;
            cnt[u][1] = tcnt;
        }
        else if (val[u][1] == tval && cnt[u][1] < tcnt)
            cnt[u][1] = tcnt;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int N, K; cin >> N >> K;
    for (int i = 1; i < N; ++i) {
        int u, v, w; cin >> u >> v >> w;
        tree[u].emplace_back(v, w);
        tree[v].emplace_back(u, w);
    }

    i64 lb = -1e12, ub = 1e12;
    dfs(0, 1, lb);
    if (cnt[1][1] < K) { cout << "Impossible"; return 0; }

    while (lb < ub) {
        i64 lmd = (lb + ub)>>1;
        dfs(0, 1, lmd);
        if (cnt[1][1] < K) ub = lmd;
        else lb = lmd+1;
    }
    dfs(0, 1, --lb);
    cout << val[1][1] + lb * K;
    return 0;
}
