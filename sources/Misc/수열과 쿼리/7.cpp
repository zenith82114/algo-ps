/*
 * 수열과 쿼리 7
 * QOJ 18765
 *
 * Mo's, sqrt decomposition
 * Date: 2023.9.23
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;
using ii = pair<int, int>;
const int MAXN = 1e5 +4, MAXK = 1e6 +4, MAXM = 1e5 +4;

class counter {
    int N, B;
    vector<int> cnt, bin_cnt;
public:
    counter(int sz) {
        B = (int)sqrt(sz);
        N = (sz + B-1) / B * B;
        cnt.resize(N);
        bin_cnt.resize(N/B);
    }
    void add(int x) {
        cnt[x]++;
        bin_cnt[x/B]++;
    }
    void remove(int x) {
        cnt[x]--;
        bin_cnt[x/B]--;
    }
    int find_max() {
        for (int i = N/B -1; i > -1; --i) if (bin_cnt[i]) {
            for (int j = B-1; j > -1; --j)
                if (cnt[i*B + j]) return i*B + j;
        }
        return -1;
    }
};

int a[MAXN] {};
list<int> lss[MAXK];
struct query { int id, l, r; } que[MAXM];
int ans[MAXM];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, k; cin >> n >> k;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        a[i] = (a[i] + a[i-1]) % k;
    }

    int m; cin >> m;
    for (int j = 0; j < m; ++j) {
        auto& q = que[j];
        q.id = j;
        cin >> q.l >> q.r;
        q.l--;
    }
    const int blk = (int)sqrt(n);
    sort(que, que + m, [&blk](const query &p, const query &q) {
        if (p.l/blk != q.l/blk) return p.l < q.l;
        return ((p.l/blk) & 1)? (p.r > q.r) : (p.r < q.r);
    });

    counter cntr(n+1);
    int l = 0, r = -1;

    for (int i = 0; i < m; ++i) {
        const auto& q = que[i];

        while (l > q.l) {
            auto& ls = lss[a[--l]];
            if (!ls.empty()) cntr.remove(ls.back() - ls.front());
            ls.emplace_front(l);
            cntr.add(ls.back() - ls.front());
        }
        while (r < q.r) {
            auto& ls = lss[a[++r]];
            if (!ls.empty()) cntr.remove(ls.back() - ls.front());
            ls.emplace_back(r);
            cntr.add(ls.back() - ls.front());
        }
        while (l < q.l) {
            auto& ls = lss[a[l++]];
            cntr.remove(ls.back() - ls.front());
            ls.pop_front();
            if (!ls.empty()) cntr.add(ls.back() - ls.front());
        }
        while (r > q.r) {
            auto& ls = lss[a[r--]];
            cntr.remove(ls.back() - ls.front());
            ls.pop_back();
            if (!ls.empty()) cntr.add(ls.back() - ls.front());
        }
        ans[q.id] = cntr.find_max();
    }

    for (int i = 0; i < m; ++i) cout << ans[i] << '\n';
    return 0;
}
