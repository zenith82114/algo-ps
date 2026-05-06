/*
 * ICPC, Regionals, Europe, Northwestern Europe Regional Contest,
 * Nordic Collegiate Programming Contest, NCPC 2020 L. Language Survey
 * Petrozavodsk Programming Camp, Winter 2021, Day 3: Nordic+ Contest 2020 L. Language Survey
 * BOJ 21058 - Ad hoc
 * Date: 2023.7.16
 */

#include<bits/stdc++.h>
using namespace std;

char q[200][200];
int a[200][200] {};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);

    int n, m; cin >> n >> m;
    bool tr = n > m;
    if (tr) {
        swap(n, m);
        for (int j = 0; j < m; ++j)
        for (int i = 0; i < n; ++i) cin >> q[i][j];
    } else {
        for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j) cin >> q[i][j];
    }

    if (n == 1) {
        int t = q[0][0] == '1'? 0 : 1;
        for (int j = 0; j+1 < m; ++j) if (q[0][j] < q[0][j+1]) ++t;
        if (t == 0) {
            if (m < 3) { cout << "impossible"; return 0; }
            a[0][0] = 1;
            a[0][1] = 2;
            for (int j = 2; j < m; ++j) a[0][j] = 4;
        } else if (t == 1) {
            for (int j = 0; j < m; ++j) a[0][j] = q[0][j] == '1'? 1 : 7;
        } else if (t == 2) {
            int k = 1;
            while (q[0][k-1] == '1' || q[0][k] == '2') ++k;
            for (int j = 0; j < k; ++j) a[0][j] = q[0][j] == '1'? 1 : 3;
            for (int j = k; j < m; ++j) a[0][j] = q[0][j] == '1'? 1 : 5;
        } else { cout << "impossible"; return 0; }
    } else {
        if (n == 2) {
            a[0][0] = a[1][0] = 1;
            for (int j = 1; j < m; ++j) a[0][j] = 2, a[1][j] = 4;
        } else if (n == 3) {
            for (int j = 0; j < m; ++j) a[0][j] = 1, a[1][j] = 2, a[2][j] = 4;
        } else if (n == 4) {
            a[0][0] = a[1][0] = a[2][0] = a[3][0] = 1;
            a[0][1] = a[1][1] = a[2][1] = a[3][1] = 2;
            for (int j = 2; j < m; ++j) {
                a[0][j] = a[3][j] = 2;
                a[1][j] = a[2][j] = 4;
            }
        } else {
            for (int i = 0; i < n; ++i) a[i][0] = 1;
            for (int j = 1; j < m; ++j) a[0][j] = 2;
            int i1 = 1, j1 = 1;
            int i2 = n-1, j2 = m-1;
            int k = 1;
            int t = n/2;
            a[i1][j1] = 2; a[i2][j2] = 4;
            while (t--) {
                while (i1+k > 0 && i1+k < n && !a[i1+k][j1]) i1 += k, a[i1][j1] = 2;
                while (i2-k > 0 && i2-k < n && !a[i2-k][j2]) i2 -= k, a[i2][j2] = 4;
                while (j1+k > 0 && j1+k < m && !a[i1][j1+k]) j1 += k, a[i1][j1] = 2;
                while (j2-k > 0 && j2-k < m && !a[i2][j2-k]) j2 -= k, a[i2][j2] = 4;
                k = -k;
            }
        }

        const int di[] { 1, 0, -1, 0 };
        const int dj[] { 0, 1, 0, -1 };

        for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j) if (q[i][j] == '2') {
            for (int k = 0; k < 4; ++k) {
                int ni = i + di[k];
                int nj = j + dj[k];
                if (ni > -1 && ni < n && nj > -1 && nj < m)
                    a[i][j] |= a[ni][nj];
            }
        }
    }

    if (tr) {
        for (int j = 0; j < m; ++j) {
            for (int i = 0; i < n; ++i) cout << (a[i][j] & 1? 'A' : '.');
            cout << '\n';
        }
        cout << '\n';
        for (int j = 0; j < m; ++j) {
            for (int i = 0; i < n; ++i) cout << (a[i][j] & 2? 'B' : '.');
            cout << '\n';
        }
        cout << '\n';
        for (int j = 0; j < m; ++j) {
            for (int i = 0; i < n; ++i) cout << (a[i][j] & 4? 'C' : '.');
            cout << '\n';
        }
    } else {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) cout << (a[i][j] & 1? 'A' : '.');
            cout << '\n';
        }
        cout << '\n';
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) cout << (a[i][j] & 2? 'B' : '.');
            cout << '\n';
        }
        cout << '\n';
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) cout << (a[i][j] & 4? 'C' : '.');
            cout << '\n';
        }
    }

    return 0;
}
