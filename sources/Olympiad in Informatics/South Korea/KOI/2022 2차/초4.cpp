/*
 * 한국정보올림피아드, KOI 2022 2차대회, 초등부 4. 빨강파랑
 * BOJ 25403
 * JUNGOL 5199
 *
 * lazy segment tree, sweep line
 * Date: 2023.6.11
 */

#include<bits/stdc++.h>
using namespace std;
using ii = pair<int, int>;

class lazy_seg_tree {
    int N, lgN;
    int M;
    vector<ii> ar;
    vector<int> lz;

    void apply(int i, int x) {
        ar[i].first += x;
        if (i < N) lz[i] += x;
    }
    void push(int i) {
        apply(i<<1, lz[i]);
        apply(i<<1|1, lz[i]);
        lz[i] = 0;
    }
    void pull(int i) {
        ar[i] = max(ar[i<<1], ar[i<<1|1]);
    }
public:
    lazy_seg_tree(int sz) {
        M = sz;
        for (N = 1, lgN = 0; N < M; N <<= 1, ++lgN);
        ar.resize(N<<1);
        lz.resize(N, 0);

        for (int i = 0; i < M; ++i) ar[i|N].second = -i;
        for (int i = M; i < N; ++i) ar[i|N].second = INT_MIN;
        for (int i = N-1; i; --i) pull(i);
    }
    void add(int i, int j, int x) {
        i |= N, j |= N;
        for (int k = lgN; k; --k) {
            if (    i>>k<<k !=   i) push(i>>k);
            if ((j+1)>>k<<k != j+1) push(j>>k);
        }
        for (int l = i, r = j; l <= r; l >>= 1, r >>= 1) {
            if ( l&1) apply(l++, x);
            if (~r&1) apply(r--, x);
        }
        for (int k = 1; k <= lgN; ++k) {
            if     (i>>k<<k !=   i) pull(i>>k);
            if ((j+1)>>k<<k != j+1) pull(j>>k);
        }
    }
    ii query() {
        const int i = N, j = N|(M-1);
        for (int k = lgN; k; --k) {
            if (    i>>k<<k !=   i) push(i>>k);
            if ((j+1)>>k<<k != j+1) push(j>>k);
        }
        ii ans = { INT_MIN, INT_MIN };
        for (int l = i, r = j; l <= r; l >>= 1, r >>= 1) {
            if ( l&1) ans = max(ans, ar[l++]);
            if (~r&1) ans = max(ans, ar[r--]);
        }
        return ans;
    }
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);

    int N, M, W, H; cin >> N >> M >> W >> H;

    struct event { int x, y, v; };
    vector<event> evt(N + M);
    vector<int> xs, ys;
    for (int i = 0; i < N + M; ++i) {
        auto& [x, y, v] = evt[i];
        cin >> x >> y;
        v = i < N? 1 : -1;
        xs.emplace_back(x - W);
        xs.emplace_back(x + 1);
        ys.emplace_back(y - H);
        ys.emplace_back(y + 1);
    }

    sort(evt.begin(), evt.end(), [] (const event& e1, const event& e2) {
        return e1.y < e2.y;
    });
    sort(xs.begin(), xs.end());
    xs.erase(unique(xs.begin(), xs.end()), xs.end());
    sort(ys.begin(), ys.end());
    ys.erase(unique(ys.begin(), ys.end()), ys.end());

    auto enc = [&] (int x) -> int {
        return lower_bound(xs.begin(), xs.end(), x) - xs.begin();
    };

    lazy_seg_tree segt(xs.size());

    int y_best = 0;
    ii ans = { INT_MIN, INT_MIN };

    auto hp = evt.begin(), lp = evt.begin();
    for (int y_cur : ys) {
        while (hp != evt.end() && hp->y <= y_cur + H) {
            segt.add(enc(hp->x - W), enc(hp->x + 1) - 1, hp->v);
            ++hp;
        }
        while (lp != evt.end() && lp->y < y_cur) {
            segt.add(enc(lp->x - W), enc(lp->x + 1) - 1, -(lp->v));
            ++lp;
        }
        ii ret = segt.query();
        if (ans < ret) { ans = ret; y_best = y_cur; }
    }
    hp = evt.begin(), lp = evt.begin();
    for (int y_cur : ys) {
        while (hp != evt.end() && hp->y <= y_cur + H) {
            segt.add(enc(hp->x - W), enc(hp->x + 1) - 1, -(hp->v));
            ++hp;
        }
        while (lp != evt.end() && lp->y < y_cur) {
            segt.add(enc(lp->x - W), enc(lp->x + 1) - 1, lp->v);
            ++lp;
        }
        ii ret = segt.query();
        if (ans < ret) { ans = ret; y_best = y_cur; }
    }

    cout << ans.first << '\n';
    cout << xs[-ans.second] << ' ' << y_best;

    return 0;
}
