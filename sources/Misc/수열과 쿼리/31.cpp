/*
 * 수열과 쿼리 31
 * QOJ 18789
 *
 * splay tree
 * Date: 2023.5.22
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;
using ii = pair<int, int>;

class splay_tree {
    struct node {
        node *l, *r, *p;
        int sz, lmx, rmx, mx;
        bool val, rev;

        node(bool v): l(0), r(0), p(0), sz(1), lmx(v), rmx(v), mx(v), val(v), rev(false) {}

        void update() {
            if (l && r) {
                l->lazy(); r->lazy();
                sz = l->sz + r->sz + 1;
                lmx = l->lmx + (val && l->lmx == l->sz? 1 + r->lmx : 0);
                rmx = r->rmx + (val && r->rmx == r->sz? 1 + l->rmx : 0);
                mx = max(l->mx, r->mx);
                if (val) mx = max(mx, l->rmx + 1 + r->lmx);
            }
            else if (l) {
                l->lazy();
                sz = l->sz + 1;
                lmx = l->lmx + (val && l->lmx == l->sz? 1 : 0);
                rmx = val? l->rmx + 1 : 0;
                mx = max(l->mx, rmx);
            }
            else if (r) {
                r->lazy();
                sz = r->sz + 1;
                lmx = val? r->lmx + 1 : 0;
                rmx = r->rmx + (val && r->rmx == r->sz? 1 : 0);
                mx = max(r->mx, lmx);
            }
            else {
                sz = 1;
                lmx = rmx = mx = val? 1 : 0;
            }
        }

        void lazy() {
            if (!rev) return;
            swap(l, r);
            swap(lmx, rmx);
            rev = false;
            if (l) l->rev = !l->rev;
            if (r) r->rev = !r->rev;
        }
    };

    vector<node> nodes;
    node *root;

    void rotate(node *x) {
        node *px = x->p; px->lazy(); x->lazy();
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
        x->lazy();
        while (x->p) {
            node *px = x->p;
            node *gx = px->p;
            if (gx) rotate((x == px->l) == (px == gx->l)? px : x);
            rotate(x);
        }
    }

    void find_index(int i) {
        node *x = root; x->lazy();
        while (true) {
            while (x->l && i < x->l->sz) { x = x->l; x->lazy(); }
            if (x->l) i -= x->l->sz;
            if (!i) break;
            i--;
            x = x->r; x->lazy();
        }
        splay(x);
    }

    node *find_interval(int i, int j) {
        find_index(i-1);
        node *x = root;
        root = x->r;
        root->p = 0;
        find_index(j-i+1);
        x->r = root;
        root->p = x;
        root = x;
        return root->r->l;
    }

public:
    void init(const vector<bool>& data) {
        int N = data.size();
        nodes.reserve(N+2);
        nodes.emplace_back(false);
        node *x = root = &nodes[0];
        for (int i = 0; i < N; ++i) {
            nodes.emplace_back(data[i]);
            x->r = &nodes.back();
            x->r->p = x;
            x = x->r;
        }
        nodes.emplace_back(false);
        x->r = &nodes.back();
        x->r->p = x;
        x = x->r;
        while (x) { x->update(); x = x->p; }
    }

    void flip(int i, int j) {
        node *x = find_interval(i, j);
        x->rev = !x->rev;
    }

    int query(int i, int j) {
        return find_interval(i, j)->mx;
    }
} splayt;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n; cin >> n;
    vector<bool> data(n);
    for (int i = 0; i < n; ++i) { int x; cin >> x; data[i] = x; }
    splayt.init(data);

    int m; cin >> m;
    while (m--) {
        int op, i, j; cin >> op >> i >> j;
        if (op & 1) splayt.flip(i, j);
        else cout << splayt.query(i, j) << '\n';
    }
    return 0;
}
