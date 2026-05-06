/*
 * International Olympiad in Informatics, IOI 2014, Day 2 C. Holiday
 * BOJ 10076
 * JUNGOL 3511
 *
 * DnC DP optimization, persistent segment tree
 * Date: 2023.9.9
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;

class persistent_seg_tree {
    struct Node {
        i64 sum;
        int l, r, cnt;
        Node(): sum(0), l(-1), r(-1), cnt(0) {}
    };
    vector<int> values;
    vector<int> roots;
    vector<Node> nodes;
    int N;

    void init_util(int n, int s, int e) {
        if (s == e) return;
        nodes[n].l = nodes.size();
        nodes[n].r = nodes.size() + 1;
        nodes.emplace_back();
        nodes.emplace_back();
        int m = (s + e)>>1;
        init_util(nodes[n].l, s, m);
        init_util(nodes[n].r, m+1, e);
    }
    void insert_util(int pn, int n, int s, int e, int i) {
        if (s == e) {
            nodes[n].sum = nodes[pn].sum + values[i];
            nodes[n].cnt = nodes[pn].cnt + 1;
            return;
        }
        int m = (s + e)>>1;
        if (i <= m) {
            nodes[n].l = nodes.size();
            nodes[n].r = nodes[pn].r;
            nodes.emplace_back();
            insert_util(nodes[pn].l, nodes[n].l, s, m, i);
        } else {
            nodes[n].l = nodes[pn].l;
            nodes[n].r = nodes.size();
            nodes.emplace_back();
            insert_util(nodes[pn].r, nodes[n].r, m+1, e, i);
        }
        nodes[n].sum = nodes[nodes[n].l].sum + nodes[nodes[n].r].sum;
        nodes[n].cnt = nodes[nodes[n].l].cnt + nodes[nodes[n].r].cnt;
    }
public:
    /* avoid MLE */
    void reserve() {
        roots.reserve(  100'001);
        nodes.reserve(2'000'000);
    }
    void init(const vector<int>& arr) {
        roots.clear(); roots.emplace_back(0);
        nodes.clear(); nodes.emplace_back();
        N = arr.size();
        init_util(0, 0, N-1);

        values = arr; sort(values.begin(), values.end());
        for (int x : arr) {
            int pn = roots.back();
            roots.emplace_back(nodes.size());
            nodes.emplace_back();
            int i = lower_bound(values.begin(), values.end(), x) - values.begin();
            insert_util(pn, roots.back(), 0, N-1, i);
        }
    }
    i64 query(int i, int j, int k) {
        int n1 = roots[i-1], n2 = roots[j];
        int s = 0, e = N-1;
        i64 ans = 0;
        while (s < e) {
            int m = (s + e)>>1;
            int rcnt = nodes[nodes[n2].r].cnt - nodes[nodes[n1].r].cnt;
            if (rcnt < k) {
                ans += nodes[nodes[n2].r].sum - nodes[nodes[n1].r].sum;
                k -= rcnt;
                n1 = nodes[n1].l;
                n2 = nodes[n2].l;
                e = m;
            } else {
                n1 = nodes[n1].r;
                n2 = nodes[n2].r;
                s = m+1;
            }
        }
        ans += (i64)k * values[s];
        return ans;
    }
} pst;

int N, S, D;

i64 dnc(int sl, int el, int sr, int er) {
    if (sl > el) return -1;
    i64 ans = -1;
    int ansr = -1;
    int ml = (sl + el)>>1;
    for (int r = sr; r <= er; ++r) {
        int k = max(0, D - S - r + 2*ml);
        k = min(k, r - ml + 1);
        i64 tmp = pst.query(ml, r, k);
        if (ans < tmp) { ans = tmp; ansr = r; }
    }
    ans = max(ans, dnc(sl, ml-1, sr, ansr));
    ans = max(ans, dnc(ml+1, el, ansr, er));
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);

    cin >> N >> S >> D; ++S;
    vector<int> arr(N); for (int& x : arr) cin >> x;
    pst.reserve();
    pst.init(arr);
    i64 ans = dnc(1, S, S, N);

    reverse(arr.begin(), arr.end());
    S = N+1 - S;
    pst.init(arr);
    ans = max(ans, dnc(1, S, S, N));

    cout << ans;
    return 0;
}
