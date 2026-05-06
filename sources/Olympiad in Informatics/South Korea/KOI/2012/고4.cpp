/*
 * 한국정보올림피아드, KOI 2012, 고등부 4. 막대기
 * BOJ 2519
 * JUNGOL 2589
 *
 * 2-SAT
 * Date: 2026.4.30
 */

#include<iostream>
#include<vector>
#include<stack>
#include<bitset>
using namespace std;
const int MAXN = 1000;

vector<int> gph[6*MAXN];
int clk;
int entry[6*MAXN] {};
int link[6*MAXN];
stack<int> st;
bitset<6*MAXN> on_st;
int scc[6*MAXN] {}, scc_id;

void dfs(int x) {
    entry[x] = ++clk;
    link[x] = clk;
    st.emplace(x); on_st.set(x);
    for (int y : gph[x]) {
        if (!entry[y]) {
            dfs(y);
            link[x] = min(link[x], link[y]);
        }
        else if (on_st[y]) {
            link[x] = min(link[x], entry[y]);
        }
    }
    if (entry[x] == link[x]) {
        scc_id++;
        while (st.top() != x) {
            int y = st.top();
            st.pop(); on_st.reset(y);
            scc[y] = scc_id;
        }
        st.pop(); on_st.reset(x);
        scc[x] = scc_id;
    }
}

struct vec2 {
    int x, y;
    vec2 operator-(const vec2& v) const {
        return { x - v.x, y - v.y };
    }
};
struct segment { vec2 v1, v2; };
segment seg[3*MAXN];

int cross(const vec2& v, const vec2& w) {
    return v.x*w.y - v.y*w.x;
}
int ccw(const vec2& o, const vec2& p, const vec2& q) {
    auto k = cross(p - o, q - o);
    return k < 0 ? -1 : k > 0;
}
bool intersects(const segment& a, const segment& b) {
    auto &a1 = a.v1, &a2 = a.v2;
    auto &b1 = b.v1, &b2 = b.v2;
    auto ca = ccw(a1, a2, b1) * ccw(a1, a2, b2);
    auto cb = ccw(b1, b2, a1) * ccw(b1, b2, a2);
    return ca < 0 && cb < 0;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n; cin >> n;
    auto neg = [&n] (int i) { return 6*n - 1 - i; };

    for (int m = 0; m < 3*n; m += 3) {
        gph[neg(m)]    .push_back(m + 1);
        gph[neg(m)]    .push_back(m + 2);
        gph[neg(m + 1)].push_back(m + 2);
        gph[neg(m + 1)].push_back(m);
        gph[neg(m + 2)].push_back(m);
        gph[neg(m + 2)].push_back(m + 1);
    }
    for (int i = 0; i < 3*n; ++i) {
        cin >> seg[i].v1.x >> seg[i].v1.y;
        cin >> seg[i].v2.x >> seg[i].v2.y;
    }

    for (int i = 0;     i < 3*n; ++i)
    for (int j = i + 1; j < 3*n; ++j) {
        if (intersects(seg[i], seg[j])) {
            gph[i].push_back(neg(j));
            gph[j].push_back(neg(i));
        }
    }

    clk = 0; scc_id = 0;
    for (int i = 0; i < 6*n; ++i) if (!entry[i]) dfs(i);

    vector<int> ans;
    for (int i = 0; i < 3*n; ++i) {
        if (scc[neg(i)] == scc[i]) {
            cout << -1;
            return 0;
        }
        if (scc[neg(i)] < scc[i]) ans.push_back(i + 1);
    }
    cout << ans.size() << '\n';
    for (int i : ans) cout << i << ' ';

    return 0;
}
