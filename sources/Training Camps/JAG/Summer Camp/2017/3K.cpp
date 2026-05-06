/*
 * ICPC Japanese Alumni Group, JAG Summer Camp 2017 Day 3 K. Permutation Period
 * BOJ 16825 - treap
 * Date: 2025.12.31
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;
constexpr int MAXN = 1e5 + 4;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

struct Treap {
    struct Node { int l, r, p, sz; uint prio; } nd[MAXN];

    void init(int n) {
        for (int i = 1; i <= n; ++i) {
            nd[i].l = nd[i].r = 0;
            nd[i].p = 0;
            nd[i].sz = 1;
            nd[i].prio = rng();
        }
    }

    void update(int i) {
        if (!i) return;
        nd[i].sz = 1;
        if (nd[i].l) {
            nd[i].sz += nd[nd[i].l].sz;
            nd[nd[i].l].p = i;
        }
        if (nd[i].r) {
            nd[i].sz += nd[nd[i].r].sz;
            nd[nd[i].r].p = i;
        }
    }

    void split(int root, int k, int &l, int &r) {
        if (!root) { l = r = 0; return; }
        nd[root].p = 0;
        // first k elements go to l
        int lsz = nd[root].l ? nd[nd[root].l].sz : 0;
        if (lsz < k) {
            split(nd[root].r, k - lsz - 1, nd[root].r, r);
            l = root;
        } else {
            split(nd[root].l, k, l, nd[root].l);
            r = root;
        }
        update(root);
    }

    void merge(int &root, int l, int r) {
        if (!l || !r) root = l ? l : r;
        else if (nd[l].prio > nd[r].prio) {
            merge(nd[l].r, nd[l].r, r);
            root = l;
        } else {
            merge(nd[r].l, l, nd[r].l);
            root = r;
        }
        update(root);
    }

    pair<int, int> get_rank(int i) {
        int rank = 1; // 1-based
        if (nd[i].l) rank += nd[nd[i].l].sz;
        int j = i;
        while (nd[j].p) {
            int p = nd[j].p;
            if (nd[p].r == j) {
                rank += 1;
                if (nd[p].l) rank += nd[nd[p].l].sz;
            }
            j = p;
        }
        return {j, rank};
    }

    int make_end(int i) {
        auto [root, k] = get_rank(i);
        if (k == nd[root].sz) return root;
        int l, r;
        split(root, k, l, r);
        merge(root, r, l);
        return root;
    }
} treap;

struct Counter {
    static const int MOD = 1e9 + 7;
    int spf[MAXN];
    int freq[MAXN][20], mfreq[MAXN];
    int inv[MAXN];
    i64 ans;

    void init(int n) {
        memset(spf + 1, 0, n * sizeof(int));
        memset(freq, 0, sizeof freq);
        memset(mfreq, 0, sizeof mfreq);
        ans = 1;

        for (int i = 2; i <= n; ++i) if (!spf[i]) {
            spf[i] = i;
            for (i64 j = (i64)i * i; j <= n; j += i) if (!spf[j]) {
                spf[j] = i;
            }

            i64 tmp = i;
            inv[i] = 1;
            for (int e = MOD - 2; e; e /= 2) {
                if (e&1) inv[i] = tmp * inv[i] % MOD;
                tmp = tmp * tmp % MOD;
            }
        }
    }

    void add(int i) {
        while (i > 1) {
            int p = spf[i], e = 0;
            while (spf[i] == p) i /= spf[i], e++;
            freq[p][e]++;
            if (mfreq[p] < e) {
                for (int j = mfreq[p]; j < e; ++j) ans = (ans * p) % MOD;
                mfreq[p] = e;
            }
        }
    }

    void remove(int i) {
        while (i > 1) {
            int p = spf[i], e = 0;
            while (spf[i] == p) i /= spf[i], e++;
            freq[p][e]--;
            if (mfreq[p] == e && !freq[p][e]) {
                for (; e && !freq[p][e]; --e) ans = (ans * inv[p]) % MOD;
                mfreq[p] = e;
            }
        }
    }
} counter;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, q; cin >> n >> q;
    treap.init(n);
    counter.init(n);

    while (q--) {
        int i, j; cin >> i >> j;
        int root_i = treap.get_rank(i).first;
        int root_j = treap.get_rank(j).first;
        counter.remove(treap.nd[root_i].sz);

        if (root_i != root_j) {
            counter.remove(treap.nd[root_j].sz);
            treap.make_end(i);
            treap.make_end(j);
            root_i = treap.get_rank(i).first;
            root_j = treap.get_rank(j).first;
            int root;
            treap.merge(root, root_i, root_j);
            counter.add(treap.nd[root].sz);
        } else {
            treap.make_end(i);
            int root = treap.get_rank(i).first;
            int rank_j = treap.get_rank(j).second;
            int l, r;
            treap.split(root, rank_j, l, r);
            counter.add(treap.nd[l].sz);
            counter.add(treap.nd[r].sz);
        }

        cout << counter.ans << '\n';
    }

    return 0;
}
