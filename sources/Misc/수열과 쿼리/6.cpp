/*
 * 수열과 쿼리 6
 * QOJ 18764
 *
 * Mo's
 * Date: 2022.2.12
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;
using ii = pair<int, int>;
const int MAXN = 1e6 +4;

array<int, MAXN> a, freq, freq_cnt;
int max_freq = 0;

inline void add(int x) {
    int f = freq[x]++;
    --freq_cnt[f]; ++freq_cnt[f+1];
    if (max_freq == f) ++max_freq;
}

inline void remove(int x) {
    int f = freq[x]--;
    --freq_cnt[f]; ++freq_cnt[f-1];
    if (freq_cnt[max_freq] == 0) --max_freq;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n; cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];

    int m; cin >> m;
    struct query { int id, l, r; };
    vector<query> que(m);
    for (int j = 0; j < m; ++j) {
        que[j].id = j;
        cin >> que[j].l >> que[j].r;
    }
    const int blk = (int)sqrt(n+1);
    sort(que.begin(), que.end(), [&blk](const query& p, const query& q){
        return p.r/blk != q.r/blk ? p.r/blk < q.r/blk : p.l < q.l;
    });

    freq.fill(0);
    freq_cnt.fill(0);
    vector<int> ans(m);
    int l = 1, r = 0;

    for (const auto& q : que) {
        while (r < q.r) add(a[++r]);
        while (r > q.r) remove(a[r--]);
        while (l < q.l) remove(a[l++]);
        while (l > q.l) add(a[--l]);
        ans[q.id] = max_freq;
    }

    for (int ansj : ans) cout << ansj << '\n';
    return 0;
}
