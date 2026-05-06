/*
 * ICPC, Regionals, Europe,
 * Benelux Algorithm Programming Contest, BAPC 2005 E. North-Western Winds
 * BOJ 5419 - sweep line, segment tree
 * Date: 2021.12.23
 */

#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

class seg_tree {
    int N;
    vector<int> A;
    int lc(int n) { return n << 1; }
    int rc(int n) { return n << 1 | 1; }
    int remove_util(int k, int n, int l, int r) {
        A[n]--;
        if (l != r) {
            int m = (l + r) / 2;
            return k > m
                ? remove_util(k, rc(n), m + 1, r)
                : remove_util(k, lc(n), l, m) + A[rc(n)];
        }
        else return A[n];
    }
public:
    seg_tree(int _N) {
        N = _N;
        int sz = 1;
        while (sz < N) sz <<= 1;
        A.resize(sz<<1, 0);
    }
    void insert(int k) {
        int n = 1, l = 0, r = N - 1;
        A[1]++;
        while (l < r) {
            int m = (l + r) / 2;
            if (k > m) {
                l = m + 1;
                n = rc(n);
            }
            else {
                r = m;
                n = lc(n);
            }
            A[n]++;
        }
    }
    int remove(int k) {
        return remove_util(k, 1, 0, N - 1);
    }
};

struct Point { int x, y; };
vector<Point> points;

// coordinate compression
vector<int> y_idx;
int y_to_idx(int y) {
    auto p = lower_bound(y_idx.begin(), y_idx.end(), y);
    return distance(y_idx.begin(), p);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int TC; cin >> TC;
    for (int tc = 0; tc < TC; tc++) {
        int64_t cnt = 0ll;
        int N; cin >> N;
        points.resize(N);
        y_idx.resize(N);
        for (int i = 0; i < N; i++) {
            auto& p = points[i];
            cin >> p.x >> p.y;
            y_idx[i] = p.y;
        }

        sort(points.begin(), points.end(),
            [](const Point& p1, const Point& p2){
                return p1.x != p2.x ? p1.x > p2.x : p1.y < p2.y;
            }
        );
        sort(y_idx.begin(), y_idx.end());

        seg_tree segt(N);
        for (const auto& [x, y] : points)
            segt.insert(y_to_idx(y));
        for (const auto& [x, y] : points)
            cnt += segt.remove(y_to_idx(y));

        cout << cnt << '\n';
    }

    return 0;
}
