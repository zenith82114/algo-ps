/*
 * ICPC, Regionals, North America, Pacific Northwest Regional,
 * 2021 ICPC Pacific Northwest Region, Division 1 J. Fail Them All!
 * BOJ 24599 - greedy, Floyd-Warshall
 * Date: 2023.8.1
 */

#include<bits/stdc++.h>
using namespace std;

bool path[200][200] {};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);

    int N, K; cin >> N >> K;
    const int V = K<<1;
    while (N--) {
        string s; cin >> s;
        for (int i = 0; i < K; ++i) if (s[i] != 'X') {
            int xi = s[i] == 'F'? i+K : i;
            for (int j = 0; j < K; ++j) if (i != j && s[j] != 'X') {
                int xj = s[j] == 'F'? j : j+K;
                path[xi][xj] = true;
            }
        }
    }

    for (int k = 0; k < V; ++k)
    for (int i = 0; i < V; ++i)
    for (int j = 0; j < V; ++j)
        path[i][j] = path[i][j] || (path[i][k] && path[k][j]);

    for (int i = 0; i < K; ++i) if (path[i][i+K] && path[i+K][i]) {
        cout << -1; return 0;
    }

    for (int t = 0; t < K; ++t) {
        if (!path[t][t+K] && path[t+K][t]) cout << 'T'; else
        if (!path[t+K][t] && path[t][t+K]) cout << 'F';
        else {
            cout << 'F';
            path[t][t+K] = true;
            for (int i = 0; i < V; ++i)
            for (int j = 0; j < V; ++j)
                path[i][j] = path[i][j] || (path[i][t] && path[t+K][j]);
        }
    }

    return 0;
}
