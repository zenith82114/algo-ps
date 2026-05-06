/*
 * ICPC, Regionals, Africa and Arab,
 * 2012 Arab Collegiate Programming Contest B. No Name
 * BOJ 9548 - treap
 * Date: 2025.4.3
 */

#include<bits/stdc++.h>
using namespace std;

class Treap {
    struct node {
        node *l, *r;
        int y, sz;
        char x;
        node() = delete;
        node(char x): l(nullptr), r(nullptr), y(rand()), sz(1), x(x) {}
        ~node() {
            if (l) delete l;
            if (r) delete r;
        }
    };
    void update(node *t) {
        if (!t) return;
        t->sz = 1;
        if (t->l) t->sz += t->l->sz;
        if (t->r) t->sz += t->r->sz;
    }
    void heapify(node *t) {
        if (!t) return;
        node *mx = t;
        if (t->l && t->l->y > mx->y) mx = t->l;
        if (t->r && t->r->y > mx->y) mx = t->r;
        if (mx != t) {
            swap(t->y, mx->y);
            heapify(mx);
        }
    }
    node* build(const string& s, int i, int j) {
        if (i > j) return nullptr;
        int m = (i + j) >> 1;
        node *t = new node(s[m]);
        t->l = build(s, i, m - 1);
        t->r = build(s, m + 1, j);
        heapify(t);
        update(t);
        return t;
    }
    void split(node *t, node *&u, node *&v, int n) {
        if (!t) {
            u = v = nullptr;
            return;
        }
        int k = t->l? t->l->sz : 0;
        if (n <= k)
            split(t->l, u, t->l, n), v = t;
        else
            split(t->r, t->r, v, n - k - 1), u = t;
        update(t);
    }
    void merge(node *&t, node *u, node *v) {
        if (!u || !v)
            t = u? u : v;
        else if (u->y > v->y)
            merge(u->r, u->r, v), t = u;
        else
            merge(v->l, u, v->l), t = v;
        update(t);
    }
    void print_util(node *t) {
        if (!t) return;
        print_util(t->l);
        cout << t->x;
        print_util(t->r);
    }
    node* root;
public:
    Treap(const string& s) {
        root = build(s, 0, (int)s.size() - 1);
    }
    ~Treap() { delete root; }
    void insert(const string& s, int i) {
        node *u;
        split(root, u, root, i);
        node *v = build(s, 0, (int)s.size() - 1);
        merge(u, u, v);
        merge(root, u, root);
    }
    void print(int i, int j) {
        node *u, *v;
        split(root, root, v, j + 1);
        split(root, u, root, i);
        print_util(root);
        cout << '\n';
        merge(root, root, v);
        merge(root, u, root);
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int tc; cin >> tc;
    while (tc--) {
        string s; cin >> s;
        Treap tr(s);

        bool go = true;
        while (go) {
            char op; cin >> op;
            if (op == 'I') {
                int i; cin >> s >> i;
                tr.insert(s, i);
            }
            else if (op == 'P') {
                int i, j; cin >> i >> j;
                tr.print(i, j);
            }
            else { // 'E'
                cin >> s; // "ND"
                go = false;
            }
        }
    }

    return 0;
}
