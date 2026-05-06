/*
 * ICPC, Regionals, Asia Pacific, Korea,
 * Asia Regional - Seoul 2021 K. Stock Price Prediction
 * BOJ 23576
 * JUNGOL 11227
 *
 * KMP, segment tree
 * Date: 2024.1.6
 */

#include<bits/stdc++.h>
using namespace std;

class seg_tree {
    vector<int> ar;
    int n;
public:
    void init(int sz) {
        n = 1; while (n < sz) n <<= 1;
        ar.resize(n<<1);
        fill(ar.begin(), ar.end(), 0);
    }
    void add(int x) { for (x |= n; x; x >>= 1) ++ar[x]; }
    void del(int x) { for (x |= n; x; x >>= 1) --ar[x]; }
    pair<int, int> query(int x) {
        int lt = 0;
        for (int i = n, j = n+x-1; i <= j; i >>= 1, j >>= 1) {
            if ( i&1) lt += ar[i++];
            if (~j&1) lt += ar[j--];
        }
        return make_pair(lt, ar[n|x]);
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int m, n; cin >> m >> n;
    vector<int> x(m), y(n);
    for (int& i : x) cin >> i;
    for (int& i : y) cin >> i;
    auto compress = [] (vector<int>& v) {
        auto w(v); sort(w.begin(), w.end());
        w.erase(unique(w.begin(), w.end()), w.end());
        for (int& x : v) {
            x = distance(w.begin(), lower_bound(w.begin(), w.end(), x));
        }
    };
    compress(x); compress(y);

    seg_tree segt;
    vector<pair<int, int> > memo(m);
    vector<int> ff(m), ans;

    segt.init(m);
    segt.add(x[0]);
    for (int i = 1; i < m; ++i) {
        memo[i] = segt.query(x[i]);
        segt.add(x[i]);
    }
    segt.init(m);
    for (int i = 1, j = 0; i < m; ++i) {
        while (j && memo[j] != segt.query(x[i])) {
            int nj = ff[j-1];
            for (; j > nj; --j) segt.del(x[i-j]);
        }
        if (memo[j] == segt.query(x[i])) {
            ++j; segt.add(x[i]);
        }
        ff[i] = j;
    }

    segt.init(n);
    for (int i = 0, j = 0; i < n; ++i) {
        while (j && memo[j] != segt.query(y[i])) {
            int nj = ff[j-1];
            for (; j > nj; --j) segt.del(y[i-j]);
        }
        if (memo[j] == segt.query(y[i])) {
            ++j; segt.add(y[i]);
        }
        if (j == m) {
            ans.emplace_back(i-m+2);
            int nj = ff[m-1];
            for (; j > nj; --j) segt.del(y[i+1-j]);
        }
    }

    if (ans.empty()) cout << 0;
    else for (int a : ans) cout << a << ' ';
    return 0;
}
