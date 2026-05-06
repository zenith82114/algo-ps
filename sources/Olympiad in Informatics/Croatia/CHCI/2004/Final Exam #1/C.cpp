/*
 * Croatian Highschool Competitions in Informatics, 2004, Final Exam #1 C. mapa
 * BOJ 3225 - segment tree, sweep line
 * Date: 2025.4.13
 */

#include<bits/stdc++.h>
using namespace std;

class seg_tree {
    int TN;
    vector<int> ar;
public:
    void init(int sz) {
        for (TN = 1; TN < sz; TN *= 2);
        ar.resize(TN * 2);
    }
    void clear() {
        fill(ar.begin(), ar.end(), 0);
    }
    void add(int i, int j, int x) {
        for (i |= TN, j |= TN; i <= j; i >>= 1, j >>= 1) {
            if ( i&1) ar[i++] += x;
            if (~j&1) ar[j--] += x;
        }
    }
    bool query(int i) {
        int ans = 0;
        for (i |= TN; i; i >>= 1) ans += ar[i];
        return ans > 0;
    }
} segt;

vector<pair<int, int> > a;

bool decide(int m) {
    vector<tuple<int, int, int> > ev;
    vector<int> ys;

    for (const auto& [x, y] : a) {
        ev.emplace_back(x,     +1, y);
        ev.emplace_back(x + m, -1, y);
        ys.emplace_back(y - m + 1);
        ys.emplace_back(y);
        ys.emplace_back(y + m - 1);
    }
    sort(ev.begin(), ev.end());
    sort(ys.begin(), ys.end());

    segt.clear();
    for (const auto& [x, t, y] : ev) {
        int p = lower_bound(ys.begin(), ys.end(), y) - ys.begin();
        if (t > 0 && segt.query(p)) return false;
        int i = lower_bound(ys.begin(), ys.end(), y - m + 1) - ys.begin();
        int j = lower_bound(ys.begin(), ys.end(), y + m - 1) - ys.begin();
        segt.add(i, j, t);
        if (t < 0 && segt.query(p)) return false;
    }
    return true;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n; cin >> n;
    a.resize(n);
    for (auto& [x, y] : a) cin >> x >> y, y *= 3;
    segt.init(3 * n);

    int lo = 1, hi = 3'000'001;
    while (lo + 1 < hi) {
        int m = (lo + hi) / 2;
        (decide(m)? lo : hi) = m;
    }
    cout << (lo / 3.);
    return 0;
}
