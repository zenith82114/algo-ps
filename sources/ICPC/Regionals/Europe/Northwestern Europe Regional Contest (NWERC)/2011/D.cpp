/*
 * ICPC, Regionals, Europe, Northwestern Europe Regional Contest,
 * NWERC 2011 D. Piece it together
 * BOJ 3654 - 2-SAT
 * Date: 2024.3.12
 *
 * WARNING: MASSIVE stack usage when input is large.
 * Increase stack limit or switch to non-recursive Kosaraju's.
 */

#include<bits/stdc++.h>
using namespace std;

char f[500][500];
array<vector<int>, 1'000'000> adj, adj_rev;
array<int, 1'000'000> entry, link, scc;
int clk, scc_id;
stack<int> st;
array<bool, 1'000'000> on_st;

void tarjan(int u) {
    clk++;
    entry[u] = clk;
    link[u] = clk;
    st.emplace(u); on_st[u] = true;
    for (const int& v : adj[u]) {
        if (!entry[v]) {
            tarjan(v);
            link[u] = min(link[u], link[v]);
        }
        else if (on_st[v])
            link[u] = min(link[u], entry[v]);
    }
    if (entry[u] == link[u]) {
        scc_id++;
        while (st.top() != u) {
            int v = st.top();
            st.pop(); on_st[v] = false;
            scc[v] = scc_id;
        }
        st.pop(); on_st[u] = false;
        scc[u] = scc_id;
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int tc; cin >> tc;
    while (tc--) {
        int n, m; cin >> n >> m;
        int white = 0, black = 0;
        for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j) {
            cin >> f[i][j];
            if (f[i][j] == 'W') ++white;
            if (f[i][j] == 'B') ++black;
        }

        if (white != 2*black) { cout << "NO\n"; continue; }

        const int V = 4*n*m;
        for (int x = 0; x < V; ++x) adj[x].clear();

        auto DOWN = [n, m](int i, int j) {
            return (i*m + j)<<2;
        };
        auto RIGHT = [n, m](int i, int j) {
            return (i*m + j)<<2|2;
        };
        // NOT(x): x^1
        auto add_or = [](int x, int y) {
            adj[1^x].emplace_back(y);
            if (x^y) adj[1^y].emplace_back(x);
        };

        for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j) {
            if (f[i][j] == 'B') {
                if (i > 0) {
                    add_or(DOWN(i-1, j), DOWN(i, j));
                    add_or(1^DOWN(i-1, j), 1^DOWN(i, j));
                }
                if (j > 0) {
                    add_or(RIGHT(i, j-1), RIGHT(i, j));
                    add_or(1^RIGHT(i, j-1), 1^RIGHT(i, j));
                }
            }

            else if (f[i][j] == 'W') {
                vector<int> v { DOWN(i, j), RIGHT(i, j) };
                if (i > 0) v.emplace_back(DOWN(i-1, j));
                if (j > 0) v.emplace_back(RIGHT(i, j-1));

                for (size_t a =   0; a < v.size(); ++a)
                for (size_t b = a+1; b < v.size(); ++b) {
                    add_or(1^v[a], 1^v[b]);
                }
            }
        }

        for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j) {
            if (f[i][j] == '.') {
                add_or(1^DOWN(i, j), 1^DOWN(i, j));
                add_or(1^RIGHT(i, j), 1^RIGHT(i, j));
            }
            else if (f[i][j] == 'B') {
                if (i == 0) add_or(DOWN(i, j), DOWN(i, j));
                if (j == 0) add_or(RIGHT(i, j), RIGHT(i, j));
                if (i+1 == n || f[i+1][j] != 'W')
                    add_or(1^DOWN(i, j), 1^DOWN(i, j));
                if (j+1 == m || f[i][j+1] != 'W')
                    add_or(1^RIGHT(i, j), 1^RIGHT(i, j));
            }
            else {
                if (i+1 == n || f[i+1][j] != 'B')
                    add_or(1^DOWN(i, j), 1^DOWN(i, j));
                if (j+1 == m || f[i][j+1] != 'B')
                    add_or(1^RIGHT(i, j), 1^RIGHT(i, j));
            }
        }

        clk = scc_id = 0;
        fill_n(entry.begin(), V, 0);
        fill_n(scc.begin(), V, 0);
        for (int x = 0; x < V; ++x) if (!entry[x]) tarjan(x);

        bool ans = true;
        for (int x = 0; x < V; x += 2) ans = ans && (scc[x] != scc[1^x]);
        cout << (ans? "YES\n" : "NO\n");
    }

    return 0;
}
