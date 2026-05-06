/*
 * POI Training Camp, ONTAK 2009 5-1. Godzilla
 * BOJ 8496 - offline incremental SCC
 * Date: 2023.6.1
 */

#include<bits/stdc++.h>
using namespace std;

int N, M;

vector<pair<int, int> > que;
vector<int> ans;

vector<vector<int> > adj;
vector<int> dirty;

int clk, scc_id;
vector<int> entry, link, scc;
stack<int> st;
vector<bool> on_st;

void dfs(int x) {
    entry[x] = link[x] = ++clk;
    st.emplace(x); on_st[x] = true;
    for (int y : adj[x]) {
        if (!entry[y]) {
            dfs(y);
            link[x] = min(link[x], link[y]);
        }
        else if (on_st[y])
            link[x] = min(link[x], entry[y]);
    }
    if (entry[x] == link[x]) {
        ++scc_id;
        while (st.top() != x) {
            int y = st.top();
            st.pop(); on_st[y] = false;
            scc[y] = scc_id;
        }
        st.pop(); on_st[x] = false;
        scc[x] = scc_id;
    }
}

vector<int> ar, in_deg;
int cnt;

int head(int x) {
    if (ar[x] < 0) return x;
    return ar[x] = head(ar[x]);
}

void unite(int x, int y) {
    x = head(x), y = head(y);
    if (x == y) return;
    if (ar[x] > ar[y]) swap(x, y);
    ar[x] += ar[y];
    in_deg[x] += in_deg[y];
    ar[y] = x;
}

void dnc(int s, int e, const vector<int>& qid) {
    if (s == M) return;

    if (s == e) {
        auto [a, b] = que[s];
        bool flag = !in_deg[head(b)];
        ++in_deg[head(b)];
        for (int i : qid) {
            auto [x, y] = que[i];
            --in_deg[head(y)];
            unite(x, y);
        }
        if (flag && in_deg[head(b)] > 0) ans[s] = --cnt;
        else ans[s] = cnt;
        return;
    }

    for (int x : dirty) adj[x].clear();
    dirty.clear();

    int m = (s + e) >> 1;
    for (int i : qid) {
        if (i > m) break;
        auto [x, y] = que[i];
        x = head(x), y = head(y);
        adj[x].emplace_back(y);
        dirty.emplace_back(x);
        dirty.emplace_back(y);
    }

    clk = scc_id = 0;
    for (int x : dirty) entry[x] = 0, link[x] = 0, scc[x] = 0;
    for (int x : dirty) if (!scc[x]) dfs(x);

    vector<int> qid1, qid2;
    for (int i : qid) {
        if (i > m) qid2.emplace_back(i);
        else {
            auto [x, y] = que[i];
            (scc[head(x)] == scc[head(y)]? qid1 : qid2).emplace_back(i);
        }
    }

    dnc(s, m, qid1);
    dnc(m+1, e, qid2);
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);

    cin >> N >> M;

    adj  .resize(N+1);
    entry.resize(N+1);
    link .resize(N+1);
    scc  .resize(N+1);
    on_st.resize(N+1, false);

    ar    .resize(N+1, -1);
    in_deg.resize(N+1);

    que.resize(M);
    ans.resize(M);
    for (auto& [x, y] : que) cin >> x >> y;

    int K; cin >> K;
    vector<pair<int, int> > tmp;
    vector<bool> chk(M, false);
    for (int k = 0; k < K; ++k) {
        int m; cin >> m; --m;
        chk[m] = true;
        tmp.emplace_back(que[m]);
    }
    for (int m = 0; m < M; ++m) if (!chk[m]) tmp.emplace_back(que[m]);
    reverse(tmp.begin(), tmp.end());
    que.swap(tmp);

    vector<int> qid(M);
    iota(qid.begin(), qid.end(), 0);

    cnt = N;
    dnc(0, M, qid);
    reverse(ans.begin(), ans.end());
    ans.emplace_back(N);
    for (int k = 1; k <= K; ++k) cout << ans[k] << '\n';
    return 0;
}
