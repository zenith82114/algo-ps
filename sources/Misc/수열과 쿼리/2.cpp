/*
 * 수열과 쿼리 2
 * QOJ 18760
 *
 * splay tree
 * Date: 2026.9.1
 */

#include<bits/stdc++.h>
using namespace std;
using u32 = uint32_t;
using i64 = int64_t;
using ii = pair<int, int>;

const int MAXN=1e5, MAXM=1e5, MAXK=10;

u32 binom[MAXK+1][MAXK+1];

class splay_tree {
    struct node {
        node *l, *r, *p;
        int sz;
        u32 val, sum[MAXK+1];

        node(u32 v): l(0), r(0), p(0), sz(1), val(v) {}

        void update() {
            int lsz = l ? l->sz : 0;
            int rsz = r ? r->sz : 0;
            sz = lsz + rsz + 1;

            int d = lsz + 1;
            u32 dpow[MAXK+1] {1,};
            for (int k = 1; k <= MAXK; ++k) dpow[k] = dpow[k-1] * d;

            for (int k = 0; k <= MAXK; ++k) {
                sum[k] = val * dpow[k];
                if (l) sum[k] += l->sum[k];
                if (r) for (int j = 0; j <= k; ++j) {
                    sum[k] += binom[k][j] * dpow[k-j] * r->sum[j];
                }
            }
        }
    };

    vector<node> nodes;
    node *root;

    void rotate(node *x) {
        node *px = x->p;
        node *y;
        if (x == px->l) { px->l = y = x->r; x->r = px; }
        else            { px->r = y = x->l; x->l = px; }
        x->p = px->p; px->p = x;
        if (y) y->p = px;
        if (x->p) (px == x->p->l ? x->p->l : x->p->r) = x;
        else root = x;
        px->update(); x->update();
    }

    void splay(node *x) {
        while (x->p) {
            node *px = x->p;
            node *gx = px->p;
            if (gx) rotate((x == px->l) == (px == gx->l)? px : x);
            rotate(x);
        }
    }

    void find_kth(int i) {
        node *x = root;
        while (true) {
            while (x->l && i < x->l->sz) x = x->l;
            if (x->l) i -= x->l->sz;
            if (!i) break;
            i--;
            x = x->r;
        }
        splay(x);
    }

public:
    void init(const vector<u32>& data) {
        int n = data.size();
        nodes.reserve(MAXN + MAXM + 2); // prevent reallocation

        nodes.emplace_back(0);
        node *x = root = &nodes[0];
        for (int i = 0; i < n; ++i) {
            nodes.emplace_back(data[i]);
            x->r = &nodes.back();
            x->r->p = x;
            x = x->r;
        }
        nodes.emplace_back(0);
        x->r = &nodes.back();
        x->r->p = x;
        x = x->r;

        while (x) { x->update(); x = x->p; }
    }

    void insert(int p, u32 v) {
        find_kth(p);
        node *x = root;
        root = x->r;
        root->p = 0;

        find_kth(0);
        assert(!root->l);
        nodes.emplace_back(v);
        node *y = &nodes.back();
        y->p = root;
        root->l = y;
        x->r = root;
        root->p = x;
        root = x;

        y->update();
        root->r->update();
        root->update();
    }

    void erase(int p) {
        find_kth(p);
        node *x = root;
        root = x->r;
        root->p = 0;

        find_kth(1);
        root->l = 0;
        x->r = root;
        root->p = x;
        root = x;

        root->r->update();
        root->update();
    }

    void update(int p, u32 v) {
        find_kth(p+1);
        root->val = v;
        root->update();
    }

    u32 query(int l, int r, int k) {
        find_kth(l);
        node *x = root;
        root = x->r;
        root->p = 0;

        find_kth(r-l+1);
        u32 ans = root->l->sum[k];
        x->r = root;
        root->p = x;
        root = x;

        return ans;
    }
} splayt;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    for (int a = 0; a <= MAXK; ++a) {
        binom[a][0] = binom[a][a] = 1;
        for (int b = 1; b < a; ++b) {
            binom[a][b] = binom[a-1][b-1] + binom[a-1][b];
        }
    }

    int n; cin >> n;
    vector<u32> data(n);
    for (u32& x : data) cin >> x;
    splayt.init(data);

    int m; cin >> m;
    while (m--) {
        int op; cin >> op;
        int p; u32 v;
        int l, r, k;

        switch (op) {
            case 1:
                cin >> p >> v;
                splayt.insert(p, v);
                break;
            case 2:
                cin >> p;
                splayt.erase(p);
                break;
            case 3:
                cin >> p >> v;
                splayt.update(p, v);
                break;
            case 4:
                cin >> l >> r >> k;
                cout << splayt.query(l, r, k) << '\n';
                break;
        }
    }
    return 0;
}
