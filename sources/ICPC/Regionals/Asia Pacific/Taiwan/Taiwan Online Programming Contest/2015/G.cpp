/*
 * ICPC, Regionals, Asia Pacific, Taiwan,
 * Taiwan Online Programming Contest, TOPC 2015 G. Egg
 * BOJ 11012 - sweep line, segment tree
 * Date: 2022.1.5
 */

#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

enum ItemType { LEFT_SIDE, POINT, RIGHT_SIDE };
struct Item {
    ItemType type;
    int x;
    int yb, yt;
    bool operator<(const Item &i) {
        return x != i.x ? x < i.x : type < i.type;
    }
};
vector<Item> items;

class seg_tree {
    int N;
    vector<int> A;

    int lc(int n) { return n << 1; }
    int rc(int n) { return n << 1 | 1; }
    void add_range_util(int n, int l, int r, int i, int j, int k) {
        int m;
        if (i == l && j == r) {
            A[n] += k;
            return;
        }
        m = (l + r) / 2;
        if (j <= m)
            add_range_util(lc(n), l, m, i, j, k);
        else if (i > m)
            add_range_util(rc(n), m+1, r, i, j, k);
        else {
            add_range_util(lc(n), l, m, i, m, k);
            add_range_util(rc(n), m+1, r, m+1, j, k);
        }
    }
public:
    seg_tree(int _N) {
        N = _N;
        int sz = 1;
        while (sz < N) sz <<= 1;
        A.resize(sz<<1, 0);
    }
    void clear() { A.clear(); }
    void add_range(int i, int j, int k) {
        add_range_util(1, 0, N-1, i, j, k);
    }
    int query(int i) {
        int n = 1, l = 0, r = N-1;
        int q = A[1];
        while (l != r) {
            int m = (l + r) / 2;
            if (i > m) {
                n = rc(n);
                l = m+1;
            }
            else {
                n = lc(n);
                r = m;
            }
            q += A[n];
        }
        return q;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    seg_tree segt(100001);

    int TC; cin >> TC;
    while (TC--) {
        int N, M; cin >> N >> M;
        items.resize(N + 2*M);

        int xl, xr, yb, yt;
        for (int i = 0; i < N; ++i) {
            cin >> xl >> yb;
            items[i] = { POINT, xl, yb, };
        }
        for (int i = 0; i < M; i++) {
            cin >> xl >> xr >> yb >> yt;
            items[N + 2*i]     = { LEFT_SIDE, xl, yb, yt };
            items[N + 2*i + 1] = { RIGHT_SIDE, xr, yb, yt };
        }
        sort(items.begin(), items.end());

        segt.clear();
        int cnt = 0;
        for (const auto& item : items) {
            switch (item.type) {
            case POINT:
                cnt += segt.query(item.yb);
                break;
            case LEFT_SIDE:
                segt.add_range(item.yb, item.yt, 1);
                break;
            case RIGHT_SIDE:
                segt.add_range(item.yb, item.yt, -1);
                break;
            }
        }
        cout << cnt << '\n';
    }

    return 0;
}
