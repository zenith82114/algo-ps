/*
 * 한국정보올림피아드, KOI 2022 1차대회, 고등부 3. 보급
 * BOJ 25382
 * JUNGOL 5124
 *
 * sweep line, segment tree, greedy
 * Date: 2024.1.1
 */

#include<bits/stdc++.h>
using namespace std;

class seg_tree {
    int (*f)(int, int);
    int n;
    vector<int> ar;
public:
    seg_tree(int (*_f)(int, int))
    : f(_f), n(1<<18), ar(n<<1, -_f(0, -n)) {}
    void update(int i, int x) {
        for (ar[i |= n] = x; i > 1; i >>= 1)
            ar[i>>1] = f(ar[i], ar[i^1]);
    }
    int query(int i, int j) {
        int ans = -f(0, -n);
        for (i |= n, j |= n; i <= j; i >>= 1, j >>= 1) {
            if ( i&1) ans = f(ans, ar[i++]);
            if (~j&1) ans = f(ans, ar[j--]);
        }
        return ans;
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n; cin >> n;
    struct _5i { int x, y, a, b, id; };
    vector<_5i> v(n);
    for (int i = 0; i < n; ++i) {
        auto& [x, y, a, b, id] = v[i];
        cin >> x >> y >> a >> b; id = i;
    }
    sort(v.begin(), v.end(), [] (const _5i& s1, const _5i& s2) {
        return s1.x < s2.x;
    });

    seg_tree segt_max([] (int x, int y) { return max(x, y); });
    seg_tree segt_min([] (int x, int y) { return min(x, y); });

    for (int i = 0; i < n; ++i) {
        auto& [x, y, a, b, id] = v[i];
        a = max(a, segt_max.query(1, y-1) + 1);
        segt_max.update(y, a);
    }
    for (int i = n-1; i > -1; --i) {
        auto& [x, y, a, b, id] = v[i];
        b = min(b, segt_min.query(y+1, n) - 1);
        if (a > b) { cout << "NO\n"; return 0; }
        segt_min.update(y, b);
    }

    using ii = pair<int, int>;
    priority_queue<ii, vector<ii>, greater<ii> > pq;
    vector<int> ans(n);

    sort(v.begin(), v.end(), [] (const _5i& s1, const _5i& s2) {
        return s1.a < s2.a;
    });
    auto it = v.begin();
    for (int k = 1; k <= n; ++k) {
        while (it != v.end() && it->a <= k) {
            pq.emplace(it->b, it->id); ++it;
        }
        if (pq.empty() || pq.top().first < k) { cout << "NO\n"; return 0; }
        ans[pq.top().second] = k;
        pq.pop();
    }
    cout << "YES\n";
    for (int k : ans) cout << k << ' ';
    return 0;
}
