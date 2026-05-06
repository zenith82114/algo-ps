/*
 * University of Ulm Local Contest 2004 H. Binary Search Heap Construction
 * BOJ 6541 - tree rotation
 * Date: 2024.12.15
 */

#include<bits/stdc++.h>
using namespace std;

pair<string, int> items[50000];

struct node {
    node *l, *r, *p;
    int idx;
    node(int i):
    l(nullptr), r(nullptr), p(nullptr), idx(i) {}
    ~node() { if (l) delete l; if (r) delete r; }
};

node* heapify(node* t) {
    node* u = t;
    if (t->l && items[u->idx].second < items[t->l->idx].second) u = t->l;
    if (t->r && items[u->idx].second < items[t->r->idx].second) u = t->r;
    if (u != t) {
        // rotate u: t == u->p
        node* v;
        if (u == t->l) {
            t->l = v = u->r;
            u->r = t;
        }
        else {
            t->r = v = u->l;
            u->l = t;
        }
        u->p = t->p;
        t->p = u;
        if (v) v->p = t;
        if (u->p) (t == u->p->l? u->p->l : u->p->r) = u;
        heapify(t);
    }
    return u;
}

node* build(int s, int e) {
    if (s > e) return nullptr;
    int m = (s + e) / 2;
    node* t = new node(m);
    t->l = build(s, m - 1);
    t->r = build(m + 1, e);
    if (t->l) t->l->p = t;
    if (t->r) t->r->p = t;
    return heapify(t);
}

void dfs(node* t) {
    if (!t) return;
    const auto& [label, prio] = items[t->idx];
    cout << '(';
    dfs(t->l);
    cout << label << '/' << prio;
    dfs(t->r);
    cout << ')';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n;
    string buf;
    for (cin >> n; n; cin >> n) {
        for (int i = 0; i < n; ++i) {
            cin >> buf;
            auto d = buf.find('/');
            auto& [label, prio] = items[i];
            label = buf.substr(0, d);
            prio = stoi(buf.substr(d + 1));
        }
        sort(items, items + n);
        auto root = build(0, n - 1);
        dfs(root);
        cout << '\n';
        delete root;
    }

    return 0;
}
