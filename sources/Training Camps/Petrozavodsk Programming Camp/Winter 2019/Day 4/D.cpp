/*
 * Petrozavodsk Programming Camp, Winter 2019, Day 4: Yandex Cup D. Pick Your Own Nim
 * BOJ 18517 - matroid intersection
 * Date: 2024.3.16
 */

#include<bits/stdc++.h>
using namespace std;
using z2vec = int64_t;

struct z2space {
    vector<z2vec> vs;
    int sz;

    void add(z2vec v) { vs.emplace_back(v); ++sz; }
    void clear() { vs.clear(); sz = 0; }
    void gauss_elim() {
        for (int i = 0; i < sz; ++i) {
            for (int j = i; j < sz; ++j) {
                if (vs[i] < vs[j]) swap(vs[i], vs[j]);
            }
            for (int j = i+1; j < sz; ++j) {
                vs[j] = min(vs[j], vs[i] ^ vs[j]);
            }
        }
    }
    bool indep(z2vec w) {
        for (auto v : vs) w = min(w, v ^ w);
        return w > 0;
    }
};

int num_vecs;
array<z2vec, 5100> vec;
array<int, 5100> color, pos, par;

int sz_ids;
vector<int> ids;
z2space space_ids;
array<z2space, 120> space_wo;
bitset<120> color_ids;

bool colorful_oracle(int ins) {
    return !color_ids[color[ins]];
}

bool colorful_oracle(int ins, int del) {
    return !color_ids[color[ins]] || color[ins] == color[del];
}

bool linear_oracle(int ins) {
    return space_ids.indep(vec[ins]);
}

bool linear_oracle(int ins, int del) {
    return space_wo[pos[del]].indep(vec[ins]);
}

bool augment() {
    space_ids.clear();
    for (int x : ids) space_ids.add(vec[x]);
    for (int i = 0; i < sz_ids; ++i) {
        space_wo[i].clear();
        for (int j = 0; j < sz_ids; ++j) if (i != j) {
            space_wo[i].add(vec[ids[j]]);
        }
    }
    space_ids.gauss_elim();
    for (int i = 0; i < sz_ids; ++i) space_wo[i].gauss_elim();

    color_ids.reset();
    for (int x : ids) color_ids.set(color[x]);

    queue<int> q;
    for (int x = 0; x < num_vecs; ++x) {
        if (colorful_oracle(x)) {
            par[x] = -2;
            q.emplace(x);
        } else par[x] = -1;
    }

    int x_end = -1;
    while (!q.empty()) {
        int x = q.front(); q.pop();

        if (pos[x] == -1) {
            if (linear_oracle(x)) {
                x_end = x; break;
            }
            for (int y : ids) {
                if (par[y] != -1 || !linear_oracle(x, y)) continue;
                par[y] = x;
                q.emplace(y);
            }
        } else {
            for (int y = 0; y < num_vecs; ++y) {
                if (par[y] != -1 || !colorful_oracle(y, x)) continue;
                par[y] = x;
                q.emplace(y);
            }
        }
    }
    if (x_end == -1) return false;

    for (; x_end != -2; x_end = par[x_end]) {
        pos[x_end] = (pos[x_end] == -1)? 0 : -1;
    }
    ids.clear();
    for (int x = 0; x < num_vecs; ++x) if (pos[x] != -1) {
        pos[x] = ids.size();
        ids.emplace_back(x);
    }
    sz_ids = ids.size();
    return true;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    num_vecs = 0;
    int n; cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> vec[num_vecs];
        color[num_vecs] = i;
        pos[num_vecs] = -1;
        ++num_vecs;
    }
    int m; cin >> m;
    for (int i = 0; i < m; ++i) {
        int k; cin >> k;
        while (k--) {
            cin >> vec[num_vecs];
            color[num_vecs] = n+i;
            pos[num_vecs] = -1;
            ++num_vecs;
        }
    }

    sz_ids = 0;
    while (augment());

    if (sz_ids < n+m) { cout << -1; return 0; }
    for (int x = n; x < num_vecs; ++x) if (pos[x] != -1) {
        cout << vec[x] << '\n';
    }
    return 0;
}
