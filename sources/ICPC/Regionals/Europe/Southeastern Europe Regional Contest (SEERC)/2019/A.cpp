/*
 * ICPC, Regionals, Europe, Southeastern Europe Regional Contest, SEERC 2019
 * A. Max or Min
 * QOJ 2371
 *
 * ad-hoc; segment tree
 * Date: 2026.7.17
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;
using ii = pair<int, int>;
const int MAXN = 2e5 +4, MAXM = 2e5 +4;

class seg_tree {
    vector<ii> tr;
    int N;
    int clk;

public:
    void init(int n) {
        N = 1; while (N < n) N *= 2;

        tr.resize(2*N, ii(-1, -1));
        for (int i = 0; i < N; ++i) tr[i|N] = ii(0, i);

        clk = 0;
    }

    void update(int i, int j, int v) {
        ii s = ii(++clk, v);

        for (i |= N, j |= N; i <= j; i >>= 1, j >>= 1) {
            if ( i&1) tr[i++] = s;
            if (~j&1) tr[j--] = s;
        }
    }

    int query(int i) {
        ii s(-1, -1);
        for (i |= N; i > 0; i >>= 1) s = max(s, tr[i]);
        return s.second;
    }
} segt;

int n, m;
vector<int> loc[MAXM];
int a[MAXN];
int len[MAXN];
int sumz = 0;

void decrement_before(int i) {
    int p = segt.query(i);

    if (p + len[p] == i+1) {
        sumz += (len[p] - 1)/2 - len[p]/2;
        --len[p];
    } else {
        sumz += (i - p)/2 + (p + len[p] - 1 - i)/2 - len[p]/2;
        segt.update(i+1, p + len[p] - 1, i+1);
        len[i+1] = p + len[p] - 1 - i;
        len[p] = i - p;
    }

    a[i] = 0;
    len[i] = 0;
    segt.update(i, i, i);
}

void decrement_after(int i) {
    a[i] = -1;
    len[i] = 1;
    segt.update(i, i, i);

    if (i+1 < n && a[i+1] == 1) {
        sumz += (len[i+1] + 1)/2 - len[i+1]/2;
        segt.update(i+1, i + len[i+1], i);
        len[i] = len[i+1] + 1;
        len[i+1] = 0;
    }

    if (i > 0 && a[i-1] == 1) {
        int p = segt.query(i-1);

        sumz += (len[p] + len[i])/2 - len[p]/2 - len[i]/2;
        segt.update(i, i + len[i] - 1, p);
        len[p] += len[i];
        len[i] = 0;
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        int x; cin >> x;
        loc[x].push_back(i);
        a[i] = 1;
        len[i] = 1;
    }

    segt.init(n);

    for (int x = 1; x <= m; ++x) {
        if (loc[x].empty()) {
            cout << -1 << ' ';
            continue;
        }

        for (int i : loc[x]) decrement_before(i);

        int ans = n - (int)loc[x].size() + sumz;
        if (a[0] * a[n-1] == -1) {
            int p = segt.query(n-1);
            ans += (len[0] + len[p])/2 - len[0]/2 - len[p]/2;
        }
        cout << ans << ' ';

        for (int i : loc[x]) decrement_after(i);
    }

    return 0;
}
