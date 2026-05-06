/*
 * 한국정보올림피아드, KOI 2010, 중등부 3/고등부 2. 체인점
 * BOJ 2472
 * JUNGOL 2302/2304
 *
 * Dijkstra's, segment tree
 * Date: 2023.5.31
 */

#include<bits/stdc++.h>
using namespace std;

class seg_tree {
    int N;
    vector<int> ar;
public:
    seg_tree(int sz) {
        N = 1; while (N < sz) N <<= 1;
        ar.resize(N<<1, INT32_MAX);
    }
    void update(int i, int x) {
        i |= N;
        if (ar[i] <= x) return;
        for (ar[i] = x; i > 1; i >>= 1) ar[i>>1] = min(ar[i], ar[i^1]);
    }
    int query(int i) {
        int j = i | N; i = N;
        int ans = INT32_MAX;
        for (; i <= j; i >>= 1, j >>= 1) {
            if ( i&1) ans = min(ans, ar[i++]);
            if (~j&1) ans = min(ans, ar[j--]);
        }
        return ans;
    }
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    using ii = pair<int, int>;

    int N; cin >> N;
    vector<vector<ii> > adj(N+1);

    int A, B, C; cin >> A >> B >> C;
    int M; cin >> M;
    while (M--) {
        int x, y, w; cin >> x >> y >> w;
        adj[x].emplace_back(y, w);
        adj[y].emplace_back(x, w);
    }

    struct iiii { int id, a, b, c; };
    vector<iiii> arr(N+1);
    for (int i = 0; i <= N; ++i) {
        auto& [id, a, b, c] = arr[i];
        id = i; a = b = c = INT32_MAX;
    }
    priority_queue<ii> pq;

    arr[A].a = 0; pq.emplace(0, A);
    while (!pq.empty()) {
        auto [d, x] = pq.top(); d = -d; pq.pop();
        if (arr[x].a < d) continue;
        for (const auto& [y, w] : adj[x]) if (arr[y].a > w + arr[x].a) {
            arr[y].a = w + arr[x].a;
            pq.emplace(-arr[y].a, y);
        }
    }
    arr[B].b = 0; pq.emplace(0, B);
    while (!pq.empty()) {
        auto [d, x] = pq.top(); d = -d; pq.pop();
        if (arr[x].b < d) continue;
        for (const auto& [y, w] : adj[x]) if (arr[y].b > w + arr[x].b) {
            arr[y].b = w + arr[x].b;
            pq.emplace(-arr[y].b, y);
        }
    }
    arr[C].c = 0; pq.emplace(0, C);
    while (!pq.empty()) {
        auto [d, x] = pq.top(); d = -d; pq.pop();
        if (arr[x].c < d) continue;
        for (const auto& [y, w] : adj[x]) if (arr[y].c > w + arr[x].c) {
            arr[y].c = w + arr[x].c;
            pq.emplace(-arr[y].c, y);
        }
    }

    sort(arr.begin(), arr.end(), [] (const iiii& e1, const iiii& e2) {
        return e1.a < e2.a;
    });

    vector<int> cmpr;
    for (const auto& e : arr) cmpr.emplace_back(e.b);
    sort(cmpr.begin(), cmpr.end());
    auto enc = [&cmpr] (int b) {
        return int(lower_bound(cmpr.begin(), cmpr.end(), b) - cmpr.begin());
    };

    seg_tree segt(N+1);
    vector<bool> ans(N+1);
    vector<int> memo(N+1);

    for (int l = 0, r = 0; l < N; l = r) {
        while (r < N && arr[l].a == arr[r].a) ++r;
        for (int k = l; k < r; ++k) {
            const auto& [id, a, b, c] = arr[k];
            int& i = memo[k] = enc(b);
            ans[id] = !i || segt.query(i-1) >= c;
        }
        for (int k = l; k < r; ++k)
            segt.update(memo[k], arr[k].c);
    }

    int T; cin >> T;
    while (T--) {
        int q; cin >> q; cout << (ans[q]? "YES\n" : "NO\n");
    }
    return 0;
}
