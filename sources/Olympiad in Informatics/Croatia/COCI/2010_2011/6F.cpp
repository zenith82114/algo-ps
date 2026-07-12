/*
 * Croatian Open Competition in Informatics, COCI 2010/2011, Contest #6
 * F. VODA
 * QOJ 17011
 *
 * connection profile DP
 * Date: 2026.7.12
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;
using ii = pair<int, int>;
const int MOD = 10007;

int n, m;
char grid[10][10];

struct state {
    int x, y, from_up;
    vector<int> profile;

    void merge(int a, int b) {
        if (a > b) swap(a, b);

        for (int x = 0; x < n; ++x) {
            if (profile[x] == b) profile[x] = a;
        }
    }

    void normalize() {
        int remap[20];
        memset(remap, -1, sizeof remap);
        remap[0] = 0;
        remap[1] = 1;
        int next = 2;

        for (int x = 0; x < n; ++x) {
            if (remap[profile[x]] == -1) remap[profile[x]] = next++;
        }
        for (int x = 0; x < n; ++x) profile[x] = remap[profile[x]];
        from_up = remap[from_up];
    }

    friend bool operator<(const state& a, const state& b) {
        if (a.x != b.x) return a.x < b.x;
        if (a.y != b.y) return a.y < b.y;
        if (a.from_up != b.from_up) return a.from_up < b.from_up;
        return a.profile < b.profile;
    }
};

map<state, int> dp;

int solve(state& s) {
    auto it = dp.find(s);
    if (it != dp.end()) return it->second;

    int ret = 0;

    if (s.x == n) {
        if (s.y < m-1) {
            if (s.from_up > 0) return 0;
            s.x = 0; ++s.y;
            ret = solve(s);
            s.x = n; --s.y;
            return ret;
        } else {
            if (s.from_up != 1) return 0;
            for (int x = 0; x < n; ++x) if (s.profile[x] != 0) return 0;
            return 1;
        }
    }

    int from_up = s.from_up;
    int from_left = s.profile[s.x];

    if (grid[s.x][s.y] == '#') {
        if (from_up != 0 || from_left != 0) return 0;
        ++s.x;
        ret = solve(s);
        --s.x;
        return dp[s] = ret;
    }

    if (from_up != 0 && from_left != 0) {
        if (from_up == from_left) return 0;

        // tile type 2
        state ns = s;
        ns.merge(from_up, from_left);
        ns.from_up = ns.profile[ns.x] = 0;
        ns.normalize();
        ++ns.x;
        ret = solve(ns);
    }
    else if (from_up != 0 && from_left == 0) {
        // tile type 4
        ++s.x;
        ret = solve(s);
        --s.x;

        // tile type 3
        s.from_up = 0; s.profile[s.x] = from_up;
        ++s.x;
        ret = (ret + solve(s)) % MOD;
        --s.x;
        s.from_up = from_up; s.profile[s.x] = 0;
    }
    else if (s.from_up == 0 && from_left != 0) {
        // tile type 1
        ++s.x;
        ret = solve(s);
        --s.x;

        // tile type 5
        s.from_up = from_left; s.profile[s.x] = 0;
        ++s.x;
        ret = (ret + solve(s)) % MOD;
        --s.x;
        s.from_up = 0; s.profile[s.x] = from_left;
    }
    else {
        // leave empty
        ++s.x;
        ret = solve(s);
        --s.x;

        // tile type 6 (new component)
        state ns = s;
        ns.from_up = ns.profile[ns.x] = n;
        ns.normalize();
        ++ns.x;
        ret = (ret + solve(ns)) % MOD;
    }

    return dp[s] = ret;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m;
    for (int x = 0; x < n; ++x)
    for (int y = 0; y < m; ++y) cin >> grid[x][y];

    state s;
    s.x = s.y = 0; s.from_up = 1;
    s.profile.assign(n, 0);

    cout << solve(s);
    return 0;
}
