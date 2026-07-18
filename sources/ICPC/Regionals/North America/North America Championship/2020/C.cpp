/*
 * ICPC, Regionals, North America Championship 2020
 * C. Bomas
 * QOJ 3163
 *
 * sweep line, BBST, greedy, DP
 * Date: 2026.7.18
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;
using ii = pair<int, int>;
const int MAXC = 2e5+4;

struct circle { int x, y, r; } circles[MAXC];

struct arc {
    static int x_now;
    int id, up;

    arc(int i, int u): id(i), up(u) {}

    double eval() const {
        const auto& c = circles[id];
        double dy = sqrt(1ll*c.r*c.r - 1ll*(x_now - c.x)*(x_now - c.x));
        return c.y + (up ? dy : -dy);
    }

    bool operator<(const arc& oth) const {
        if (id == oth.id) return up < oth.up;
        return eval() < oth.eval();
    }
};
int arc::x_now = 0;

int n, q;
vector<ii> evt;
set<arc> s;
set<arc>::iterator iter[MAXC][2];

int par[MAXC] {};
vector<int> gph[MAXC];
int dp[MAXC] {};
bool sel[MAXC] {};

void dfs(int i) {
    for (int j : gph[i]) if (j != par[i]) {
        dfs(j);
        dp[i] += dp[j];
        sel[i] |= sel[j];
    }

    if (i <= n) {
        if (!sel[i]) ++dp[i];
        sel[i] = !sel[i];
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> q;
    for (int i = 1; i <= n + q; ++i) {
        auto& c = circles[i];
        cin >> c.x >> c.y >> c.r;

        evt.emplace_back(i, 0);
        evt.emplace_back(i, 1);
    }

    sort(begin(evt), end(evt), [](const ii& a, const ii& b) {
        auto& ca = circles[a.first];
        auto& cb = circles[b.first];
        int xa = ca.x + (a.second ? ca.r : -ca.r);
        int xb = cb.x + (b.second ? cb.r : -cb.r);
        if (xa != xb) return xa < xb;
        return a.first < b.first;
    });

    for (auto [i, t] : evt) {
        auto& c = circles[i];
        arc::x_now = c.x - c.r;

        if (t == 0) {
            arc a(i, 0);
            auto f = s.lower_bound(a);

            if (f == s.end()) par[i] = 0;
            else par[i] = f->up ? f->id : par[f->id];
            gph[par[i]].push_back(i);

            iter[i][0] = s.emplace(i, 0).first;
            iter[i][1] = s.emplace(i, 1).first;
        } else {
            s.erase(iter[i][0]);
            s.erase(iter[i][1]);
        }
    }

    dfs(0);
    for (int i = n + 1; i <= n + q; ++i) cout << (dp[i] + !sel[i]) << '\n';
    return 0;
}
