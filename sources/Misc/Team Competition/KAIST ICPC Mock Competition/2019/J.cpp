/*
 * 2019 KAIST 9th ICPC Mock Competition J. Parklife
 * BOJ 17517 - slope trick, smaller to larger
 * Date: 2026.3.31
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;
constexpr int MAXN = 25e4 +4;

array<int, MAXN> s, e, v;
vector<int> gph[MAXN];
priority_queue<i64> pqs[MAXN];

void dfs(int x) {
    vector<i64> tmp;
    for (int y : gph[x]) {
        dfs(y);
        if (pqs[x].size() < pqs[y].size()) pqs[x].swap(pqs[y]);
        while (!pqs[y].empty()) {
            tmp.push_back(pqs[x].top() + pqs[y].top());
            pqs[x].pop(); pqs[y].pop();
        }
        for (i64 t : tmp) pqs[x].push(t);
        tmp.clear();
    }
    pqs[x].push(v[x]);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n; cin >> n;
    for (int i = 1; i <= n; ++i) cin >> s[i] >> e[i] >> v[i];

    vector<int> ord(n); iota(ord.begin(), ord.end(), 1);
    sort(ord.begin(), ord.end(), [](int i, int j) {
        return make_pair(s[i], -e[i]) < make_pair(s[j], -e[j]);
    });
    s[0] = 0; e[0] = 1e6; v[0] = 0;

    vector<int> stk { 0 };
    for (int i : ord) {
        while (e[stk.back()] <= s[i]) stk.pop_back();
        gph[stk.back()].push_back(i);
        stk.push_back(i);
    }

    dfs(0);
    i64 ans = 0;
    for (int k = 1; k <= n; ++k) {
        if (!pqs[0].empty()) ans += pqs[0].top(), pqs[0].pop();
        cout << ans << ' ';
    }
    return 0;
}
