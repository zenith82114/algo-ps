/*
 * Croatian Highschool Competitions in Informatics, 2009, Croatian Olympiad in Informatics 2009 B. OTOCI
 * BOJ 21973 - link-cut tree
 * Date: 2024.1.13
 */

#include<bits/stdc++.h>
using namespace std;
using ii = pair<int, int>;

class LinkCutTree {
    struct Node {
        Node *l, *r, *p;
        int val, sum;
        bool rev;
        Node(int i, int c):
            l(0), r(0), p(0), val(c), sum(c), rev(false) {}
    };
    vector<Node> nodes;

    bool _is_root(Node *x) {
        return !x->p || (x->p->l != x && x->p->r != x);
    }
    void _update(Node *x) {
        x->sum = x->val;
        if (x->l) x->sum += x->l->sum;
        if (x->r) x->sum += x->r->sum;
    }
    void _lazy(Node *x) {
        if (!x->rev) return;
        swap(x->l, x->r);
        x->rev = false;
        if (x->l) x->l->rev = !x->l->rev;
        if (x->r) x->r->rev = !x->r->rev;
    }
    void _rotate(Node *x) {
        Node *px = x->p;
        _lazy(px); _lazy(x);
        if (x == px->l) {
            px->l = x->r;
            if (x->r) x->r->p = px;
            x->r = px;
        }
        else {
            px->r = x->l;
            if (x->l) x->l->p = px;
            x->l = px;
        }
        x->p = px->p;
        px->p = x;
        if (x->p) {
            if (px == x->p->l) x->p->l = x;
            else if (px == x->p->r) x->p->r = x;
        }
        _update(px); _update(x);
    }
    void _splay(Node *x) {
        while (!_is_root(x)) {
            Node *px = x->p;
            if (!_is_root(px))
                _rotate((x == px->l) == (px == px->p->l)? px : x);
            _rotate(x);
        }
    }
    Node *_access(Node *x) {
        _splay(x); _lazy(x);
        x->r = 0;
        _update(x);

        Node *y = x;
        while (x->p) {
            y = x->p;
            _splay(y); _lazy(y);
            y->r = x;
            _update(y);
            _splay(x);
        }
        return y;
    }
    void _link(Node *x, Node *y) {
        _access(x);
        _access(y);
        x->l = y;
        y->p = x;
        _update(x);
    }
    Node *_lca(Node *x, Node *y) {
        _access(x);
        return _access(y);
    }
    Node *_get_root(Node *x) {
        _access(x);
        while (x->l) x = x->l;
        _splay(x);
        return x;
    }
    void _make_root(Node *x) {
        _access(x);
        x->rev = !x->rev;
    }
    int _path_sum(Node *x, Node *y) {
        Node *z = _lca(y, x);
        int ret = z->val;
        _access(x); _splay(z);
        if (z->r) ret += z->r->sum;
        _access(y); _splay(z);
        if (z->r) ret += z->r->sum;
        return ret;
    }
public:
    LinkCutTree(int sz) { nodes.reserve(sz); }
    int add_node(int c) {
        int id = nodes.size();
        nodes.emplace_back(id, c);
        return id;
    }
    bool connected(int u, int v) { return _get_root(&nodes[u]) == _get_root(&nodes[v]); }
    void connect(int u, int v) {
        _make_root(&nodes[u]);
        _link(&nodes[u], &nodes[v]);
    }
    void update(int u, int c) {
        _splay(&nodes[u]);
        nodes[u].val = c;
        _update(&nodes[u]);
    }
    int path_sum(int u, int v) { return _path_sum(&nodes[u], &nodes[v]); }
};

int main() {
    ios_base::sync_with_stdio(false);

    int N; cin >> N;
    LinkCutTree lct(N+1); lct.add_node(0);
    for (int i = 0; i < N; ++i) {
        int c; cin >> c; lct.add_node(c);
    }

    int Q; cin >> Q;
    while (Q--) {
        string s; int a, b; cin >> s >> a >> b;
        if (s[0] == 'b') {
            if (lct.connected(a, b)) cout << "no" << endl;
            else {
                cout << "yes" << endl;
                lct.connect(a, b);
            }
        }
        else if (s[0] == 'p') lct.update(a, b);
        else {
            if (lct.connected(a, b)) cout << lct.path_sum(a, b) << endl;
            else cout << "impossible" << endl;
        }
    }

    return 0;
}
