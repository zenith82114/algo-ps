/*
 * ICPC, Regionals, Asia Pacific, Korea,
 * Daejeon Nationalwide Internet Competition 2013 D. Dual Priority Queue
 * BOJ 7662
 *
 * interval heap
 * Date: 2024.5.9
 */

#include<bits/stdc++.h>
using namespace std;

class interval_heap {
    struct node { int l, r; };
    vector<node> heap;
    int sz;
    bool odd;

    inline int pa(int x) { return x>>1; }
    inline int lc(int x) { return x<<1; }
    inline int rc(int x) { return x<<1|1; }
public:
    interval_heap(int max_sz): heap(max_sz) {}

    void init() {
        sz = 0;
        odd = false;
    }
    bool empty() { return sz == 0; }
    void insert(int x) {
        if (odd) {
            heap[sz].r = x;
            if (heap[sz].l > heap[sz].r) {
                swap(heap[sz].l, heap[sz].r);
            }
        }
        else {
            heap[++sz].l = x;
            if (sz > 1 && !odd) {
                if (heap[sz].l < heap[pa(sz)].l) {
                    swap(heap[sz].l, heap[pa(sz)].l);
                }
                else if (heap[sz].l > heap[pa(sz)].r) {
                    swap(heap[sz].l, heap[pa(sz)].r);
                }
            }
        }
        int m = odd? sz : pa(sz);
        for (int n = m; n > 1 && heap[pa(n)].l > heap[n].l; n = pa(n)) {
            swap(heap[pa(n)].l, heap[n].l);
        }
        for (int n = m; n > 1 && heap[pa(n)].r < heap[n].r; n = pa(n)) {
            swap(heap[pa(n)].r, heap[n].r);
        }
        odd = !odd;
    }
    void pop_min() {
        if (!sz) return;
        heap[1].l = heap[sz].l;
        if (odd) --sz;
        else heap[sz].l = heap[sz].r;
        for (int n = 1, m = 1; n <= sz; n = m) {
            m = n;
            if (lc(n) <= sz && heap[m].l > heap[lc(n)].l) m = lc(n);
            if (rc(n) <= sz && heap[m].l > heap[rc(n)].l) m = rc(n);
            if (m != n) {
                swap(heap[n].l, heap[m].l);
                if (heap[m].l > heap[m].r) {
                    swap(heap[m].l, heap[m].r);
                }
            }
            else break;
        }
        odd = !odd;
    }
    int get_min() { return heap[1].l; }
    void pop_max() {
        if (!sz) return;
        if (odd) {
            heap[1].r = heap[sz].l;
            --sz;
        }
        else {
            heap[1].r = heap[sz].r;
        }
        for (int n = 1, m = 1; n <= sz; n = m) {
            m = n;
            if (lc(n) <= sz && heap[m].r < heap[lc(n)].r) m = lc(n);
            if (rc(n) <= sz && heap[m].r < heap[rc(n)].r) m = rc(n);
            if (m != n) {
                swap(heap[n].r, heap[m].r);
                if (heap[m].l > heap[m].r) {
                    swap(heap[m].l, heap[m].r);
                }
            }
            else break;
        }
        odd = !odd;
    }
    int get_max() {
        return (sz == 1 && odd)? heap[1].l : heap[1].r;
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    interval_heap ih(1<<20);

    int t; cin >> t;
    while (t--) {
        ih.init();
        int k; cin >> k;
        while (k--) {
            char op; int x; cin >> op >> x;
            if (op == 'I') ih.insert(x);
            else if (x < 0) ih.pop_min();
            else ih.pop_max();
        }
        if (ih.empty()) {
            cout << "EMPTY\n";
        }
        else {
            cout << ih.get_max() << ' ';
            cout << ih.get_min() << '\n';
        }
    }

    return 0;
}
