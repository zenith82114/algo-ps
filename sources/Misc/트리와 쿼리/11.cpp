/*
 * 트리와 쿼리 11
 * QOJ 18814
 *
 * link-cut tree
 * Date: 2023.3.21
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;
using ii = pair<int, int>;

class link_cut_tree {
    struct node {
        node *l = 0, *r = 0, *p = 0;
    };
    vector<node> nodes;

    bool _is_root(node *x) {
        return !x->p || (x->p->l != x && x->p->r != x);
    }
    void _rotate(node *x) {
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
        if (y) y->p = px;
        if (x->p) {
            if (px == x->p->l) x->p->l = x;
            else if (px == x->p->r) x->p->r = x;
        }
    }
    void _splay(node *x) {
        while (!_is_root(x)) {
            node *px = x->p;
            if (!_is_root(px)) {
                if ((x == px->l) == (px == px->p->l)) _rotate(px);
                else _rotate(x);
            }
            _rotate(x);
        }
    }
    node* _access(node *x) {
        _splay(x);
        x->r = 0;
        node *y = x;
        while (x->p) {
            node *px = x->p;
            y = px;
            _splay(px);
            px->r = x;
            _splay(x);
        }
        return y;
    }
    void _link(node *x, node *y) {
        _access(x);
        _access(y);
        x->l = y;
        y->p = x;
    }
    void _cut(node *x) {
        _access(x);
        x->l->p = 0;
        x->l = 0;
    }
    node *_lca(node *x, node *y) {
        _access(x);
        return _access(y);
    }

public:
    link_cut_tree(int n): nodes(n) {}
    void link(int u, int v) { _link(&nodes[u], &nodes[v]); }
    void cut(int v) { _cut(&nodes[v]); }
    int lca(int u, int v) { return _lca(&nodes[u], &nodes[v]) - &nodes[0]; }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m; cin >> n >> m;
    link_cut_tree lct(n+1);

    while (m--) {
        int q, u, v; cin >> q;
        switch (q) {
            case 1:
            cin >> u >> v; lct.link(u, v); break;
            case 2:
            cin >> v; lct.cut(v); break;
            case 3:
            cin >> u >> v; cout << lct.lca(u, v) << '\n'; break;
        }
    }

    return 0;
}
