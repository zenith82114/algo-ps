/*
 * ICPC, Regionals, Europe, Northwestern Europe Regional Contest,
 * NWERC 2008 B. Proving Equivalences
 * BOJ 3682 - SCC reduction
 * Date: 2023.11.21
 */

#include<bits/stdc++.h>
using namespace std;

#define SIZE 20001

vector<int> adj[SIZE];
int clk;
int entry[SIZE], link[SIZE];
stack<int> st;
bool on_st[SIZE] {};
int scc[SIZE];
int scc_id;
int in_deg[SIZE] {}, out_deg[SIZE] {};

void dfs(int x) {
    clk++;
    entry[x] = clk;
    link[x] = clk;
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
        scc_id++;
        while (st.top() != x) {
            int y = st.top();
            st.pop(); on_st[y] = false;
            scc[y] = scc_id;
        }
        st.pop(); on_st[x] = false;
        scc[x] = scc_id;
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);

    int tc; cin >> tc;
    while (tc--) {
        int n, m; cin >> n >> m;
        for (int x = 1; x <= n; ++x) adj[x].clear();
        while (m--) {
            int x, y; cin >> x >> y;
            adj[x].emplace_back(y);
        }

        clk = 0; scc_id = 0;
        memset(entry+1, 0, n * sizeof(int));
        for (int x = 1; x <= n; ++x) if (!entry[x]) dfs(x);

        if (scc_id == 1) { cout << "0\n"; continue; }

        memset(in_deg+1, 0, scc_id * sizeof(int));
        memset(out_deg+1, 0, scc_id * sizeof(int));
        for (int x = 1; x <= n; ++x) for (int y : adj[x]) {
            if (scc[x] != scc[y]) {
                ++out_deg[scc[x]];
                ++in_deg[scc[y]];
            }
        }

        int s = 0, t = 0;
        for (int x = 1; x <= scc_id; ++x) {
            if (!in_deg[x]) ++s;
            if (!out_deg[x]) ++t;
        }
        cout << max(s, t) << '\n';
    }

    return 0;
}
