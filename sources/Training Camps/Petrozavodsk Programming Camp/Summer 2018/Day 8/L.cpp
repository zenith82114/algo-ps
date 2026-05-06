/*
 * Petrozavodsk Programming Camp, Summer 2018, Day 8: Yuhao Du Contest 5, Grand Prix of Zhejiang L. Link Cut Digraph
 * BOJ 19028 - offline incremental SCC
 * Date: 2023.4.8
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;

int N, M;

vector<pair<int, int> > que;
vector<i64> ans;

vector<vector<int> > adj;
vector<int> dirty;

int clk;
int scc_id;
vector<int> entry, link, scc;
stack<int> st;
vector<bool> on_st;

void dfs(int u) {
    entry[u] = link[u] = ++clk;
    st.emplace(u); on_st[u] = true;
    for (const int& v : adj[u]) {
        if (!entry[v]) {
            dfs(v);
            link[u] = min(link[u], link[v]);
        }
        else if (on_st[v])
            link[u] = min(link[u], entry[v]);
    }
    if (entry[u] == link[u]) {
        ++scc_id;
        while (st.top() != u) {
            int v = st.top();
            st.pop(); on_st[v] = false;
            scc[v] = scc_id;
        }
        st.pop(); on_st[u] = false;
        scc[u] = scc_id;
    }
}

vector<int> ar;
i64 cnt = 0L;

int find(int x) {
    if (ar[x] < 0) return x;
    return ar[x] = find(ar[x]);
}

inline i64 nC2(i64 n) { return (n * (n-1)) >> 1; };

void unite(int x, int y) {
    x = find(x), y = find(y);
    if (x == y) return;
    if (ar[x] > ar[y]) swap(x, y);
    cnt -= nC2(-ar[x]) + nC2(-ar[y]);
    ar[x] += ar[y];
    cnt += nC2(-ar[x]);
    ar[y] = x;
}

void dnc(int s, int e, const vector<int>& qid) {
    if (s == M) return;

    if (s == e) {
        for (const int& i : qid) {
            auto [u, v] = que[i];
            unite(u, v);
        }
        ans[s] = cnt;
        return;
    }

    for (const int& u : dirty) adj[u].clear();
    dirty.clear();

    int m = (s + e) >> 1;
    for (const int& i : qid) {
        if (i > m) break;
        auto [u, v] = que[i];
        u = find(u), v = find(v);
        adj[u].emplace_back(v);
        dirty.emplace_back(u);
        dirty.emplace_back(v);
    }

    clk = scc_id = 0;
    for (const int& u : dirty) entry[u] = 0, link[u] = 0, scc[u] = 0;
    for (const int& u : dirty) if (!scc[u]) dfs(u);

    vector<int> qid1, qid2;
    for (const int& i : qid) {
        if (i > m) qid2.emplace_back(i);
        else {
            auto [u, v] = que[i];
            (scc[find(u)] == scc[find(v)]? qid1 : qid2).emplace_back(i);
        }
    }

    dnc(s, m, qid1);
    dnc(m+1, e, qid2);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    cin >> N >> M;

    adj.  resize(N+1);
    entry.resize(N+1);
    link .resize(N+1);
    scc  .resize(N+1);
    on_st.resize(N+1, false);

    ar.resize(N+1, -1);

    que.resize(M);
    ans.resize(M);
    for (auto& [u, v] : que) cin >> u >> v;

    vector<int> qid(M);
    iota(qid.begin(), qid.end(), 0);

    dnc(0, M, qid);
    for (const i64& a : ans) cout << a << '\n';
    return 0;
}
