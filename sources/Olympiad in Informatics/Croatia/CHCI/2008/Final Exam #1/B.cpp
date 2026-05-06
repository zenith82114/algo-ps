/*
 * Croatian Highschool Competitions in Informatics, 2008, Final Exam #1 B. PUTEVI
 * BOJ 1289 - tree DP
 * Date: 2023.5.23
 */

#include<bits/stdc++.h>
using namespace std;

struct mint {
    static int MOD;
    int val;
    mint(): val(0) {}
    mint(int v) {
        val = (-MOD <= v && v < MOD)? v : v % MOD;
        if (val < 0) val += MOD;
    }

    friend istream& operator>>(istream& is, mint& x) {
        is >> x.val; return is;
    }
    friend ostream& operator<<(ostream& os, const mint& x) {
        return os << x.val;
    }

    mint operator+(const mint& x) const { return mint(*this) += x; }
    mint& operator+=(const mint& x) {
        if ((val += x.val) >= MOD) val -= MOD;
        return *this;
    }
    mint operator*(const mint& x) const { return mint(*this) *= x; }
    mint& operator*=(const mint& x) {
        val = (1LL * val * x.val) % MOD; return *this;
    }
};
int mint::MOD = 1'000'000'007;

array<vector<pair<int, mint> >, 100'001> adj;
array<pair<mint, mint>, 100'001> memo;

void dfs(int px, int x) {
    auto& [fx, gx] = memo[x]; fx = 0; gx = 0;
    mint t;
    for (const auto& [y, w] : adj[x]) if (y != px) {
        dfs(x, y);
        auto wfy1 = w * (memo[y].first + 1);
        fx += wfy1;
        gx += t * wfy1;
        t += wfy1;
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);

    int N; cin >> N;
    for (int i = 1; i < N; ++i) {
        int x, y; mint w; cin >> x >> y >> w;
        adj[x].emplace_back(y, w);
        adj[y].emplace_back(x, w);
    }
    dfs(0, 1);
    mint ans;
    for (int i = 1; i <= N; ++i) { auto& [f, g] = memo[i]; ans += f + g; }
    cout << ans;
    return 0;
}
