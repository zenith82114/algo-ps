/*
 * UCPC 2016 A. 배열
 * BOJ 13159
 *
 * splay tree
 * Date: 2022.3.14
 */

#include<bits/stdc++.h>
using namespace std;
using ll = long long;

class splay_tree {
    struct node {
        node *l, *r, *p;
        ll sum;
        int val, sz, val_min, val_max;
        bool rev;
        node(int v) :
            val(v), rev(false), l(nullptr), r(nullptr), p(nullptr) {}
        void update() {
            sz = 1;
            val_min = val_max = sum = val;
            if (l) {
                sz += l->sz;
                val_min = min(val_min, l->val_min);
                val_max = max(val_max, l->val_max);
                sum += l->sum;
            }
            if (r) {
                sz += r->sz;
                val_min = min(val_min, r->val_min);
                val_max = max(val_max, r->val_max);
                sum += r->sum;
            }
        }
        void lazy() {
            if (!rev) return;
            if (l) l->rev = !l->rev;
            if (r) r->rev = !r->rev;
            swap(l, r);
            rev = false;
        }
    } *root;
    int N;
    void rotate(node *x) {
        node *px = x->p;
        node *y;
        if (x == px->l) {
            px->l = y = x->r;
            x->r = px;
        }
        else {
            px->r = y = x->l;
            x->l = px;
        }
        x->p = px->p;
        px->p = x;
        if (y)
            y->p = px;
        if (x->p)
            (px == x->p->l ? x->p->l : x->p->r) = x;
        else root = x;
        px->update();
        x->update();
    }
    void splay(node *x) {
        node *px, *gx;
        while (x->p) {
            px = x->p;
            gx = px->p;
            if (gx) {
                if ((x == px->l) == (px == gx->l))
                    rotate(px);
                else rotate(x);
            }
            rotate(x);
        }
    }
    node *find_index(int i) {
        node *x = root; x->lazy();
        while (true) {
            while (x->l && i < x->l->sz) {
                x = x->l; x->lazy();
            }
            if (x->l)
                i -= x->l->sz;
            if (!i) break;
            i--;
            x = x->r; x->lazy();
        }
        splay(x);
        return x;
    }
    node *find_value(node *x, int v) {
        node *y = nullptr;
        x->lazy();
        if (v == x->val) {
            splay(x);
            return x;
        }
        if (x->l && v >= x->l->val_min && v <= x->l->val_max)
            y = find_value(x->l, v);
        if (!y && x->r && v >= x->r->val_min && v <= x->r->val_max)
            y = find_value(x->r, v);
        return y;
    }
    node *find_interval(int i, int j) {
        find_index(i-1);
        node *x = root;
        root = x->r;
        root->p = nullptr;
        find_index(j-i+1);
        x->r = root;
        root->p = x;
        root = x;
        return root->r->l;
    }
    void in_order_util(node *x) {
        if (!x) return;
        x->lazy();
        in_order_util(x->l);
        if (x->val > 0 && x->val <= N)
            cout << x->val << ' ';
        in_order_util(x->r);
    }
public:
    void init(int _N) {
        N = _N;
        root = new node(0);
        node *x = root;
        for (int i=1; i<=N+1; ++i) {
            x->r = new node(i);
            x->r->p = x;
            x = x->r;
        }
        while (x) {
            x->update();
            x = x->p;
        }
    }
    void query_index(int i) {
        cout << find_index(i)->val << '\n';
    }
    void query_value(int v) {
        cout << find_value(root, v)->l->sz << '\n';
    }
    void query_interval(int i, int j) {
        node *x = find_interval(i, j);
        cout << x->val_min << ' ' << x->val_max << ' ' << x->sum << '\n';
    }
    void flip_interval(int i, int j) {
        node *x = find_interval(i, j);
        x->rev = !x->rev;
    }
    void shift_interval(int i, int j, int k) {
        k %= (j-i+1);
        if (k < 0)
            k += (j-i+1);
        if (k > 0) {
            flip_interval(i, j);
            flip_interval(i, i+k-1);
            flip_interval(i+k, j);
        }
    }
    void in_order() {
        in_order_util(root);
        cout << '\n';
    }
} splayt;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int N, Q; cin >> N >> Q;
    int l, r, x;
    splayt.init(N);
    while (Q--) {
        int q; cin >> q;
        switch (q) {
            case 1:
                cin >> l >> r;
                splayt.query_interval(l, r);
                splayt.flip_interval(l, r);
            break;
            case 2:
                cin >> l >> r >> x;
                splayt.query_interval(l, r);
                splayt.shift_interval(l, r, x);
            break;
            case 3:
                cin >> x;
                splayt.query_index(x);
            break;
            case 4:
                cin >> x;
                splayt.query_value(x);
        }
    }
    splayt.in_order();
    return 0;
}
