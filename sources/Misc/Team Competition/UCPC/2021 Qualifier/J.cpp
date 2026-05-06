/*
 * UCPC 2021 Qualifier J. ABBC 만들기
 * JUNGOL 8509
 *
 * DSU on tree (Sack)
 * Date: 2026.5.3
 *
 * For the original version (UCPC 만들기),
 * just modify the `char_to_vec` function.
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;
const int MAXN = 2e5 + 4;

struct vec2 {
    int x, y;
    vec2() = default;
    vec2(int x, int y): x(x), y(y) {}
    bool operator<(const vec2& other) const {
        return make_pair(x, y) < make_pair(other.x, other.y);
    }
    bool operator==(const vec2& other) const {
        return x == other.x && y == other.y;
    }
    bool operator!=(const vec2& other) const {
        return x != other.x || y != other.y;
    }
    vec2 operator+(const vec2& other) const {
        return vec2(x + other.x, y + other.y);
    }
    vec2 operator-(const vec2& other) const {
        return vec2(x - other.x, y - other.y);
    }
};

string str;
vector<int> tree[MAXN];
int par[MAXN], sz[MAXN];
vec2 psum[MAXN];

vec2 char_to_vec(char c) {
    return c == 'A' ? vec2(1, 2)
        : c == 'B' ? vec2(0, -1)
        : vec2(-1, 0);
}

void prep(int px, int x) {
    par[x] = px;
    sz[x] = 1;
    psum[x] = psum[px] + char_to_vec(str[x]);

    for (int y : tree[x]) if (y != px) {
        prep(x, y); sz[x] += sz[y];
    }
}

map<vec2, int> mp;
i64 ans = 0;

void update_ans(int x, const vec2& t) {
    if (auto f = mp.find(t - psum[x]); f != end(mp)) ans += f->second;
    for (int y : tree[x]) if (y != par[x]) update_ans(y, t);
}

void add_mp(int x, int delta) {
    mp[psum[x]] += delta;
    if (mp[psum[x]] == 0) mp.erase(psum[x]);
    for (int y : tree[x]) if (y != par[x]) add_mp(y, delta);
}

void solve(int x, bool heavy = false) {
    int hy = 0; // sz[0] = 0
    for (int y : tree[x]) if (y != par[x] && sz[hy] < sz[y]) hy = y;

    for (int y : tree[x]) if (y != par[x] && y != hy) solve(y, false);
    if (hy) solve(hy, true);

    vec2 t = psum[x] + psum[x] - char_to_vec(str[x]);
    if (auto f = mp.find(t - psum[x]); f != end(mp)) ans += f->second;

    mp[psum[x]] += 1;
    for (int y : tree[x]) if (y != par[x] && y != hy) update_ans(y, t), add_mp(y, +1);
    if (!heavy) add_mp(x, -1);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n; cin >> n;
    cin >> str; str.insert(begin(str), 0);
    for (int i = 1; i < n; ++i) {
        int x, y; cin >> x >> y;
        tree[x].push_back(y);
        tree[y].push_back(x);
    }

    prep(0, 1);
    solve(1);
    cout << ans;
    return 0;
}
