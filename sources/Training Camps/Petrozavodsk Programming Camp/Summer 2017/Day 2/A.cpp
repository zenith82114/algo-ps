/*
 * Petrozavodsk Programming Camp, Summer 2017, Day 2: UniBuc Contest A. Balance
 * Open Cup 2017/2018 Stage 1: Grand Prix of Romania A. Balance
 * BOJ 19043 - LP duality, Hungarian
 * Date: 2024.2.18
 */

#include<bits/stdc++.h>
using namespace std;

array<array<int, 50>, 50> A;
array<int, 50> lx, ly, mx, my, ty, slk, slkx;
array<bool, 50> S, T;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n; cin >> n;
    int m = 0;
    lx.fill(0), ly.fill(0);
    mx.fill(-1), my.fill(-1);
    for (int i = 0; i < n; ++i)
    for (int j = 0; j < n; ++j) {
        cin >> A[i][j];
        lx[i] = max(lx[i], A[i][j]);
    }

    while (m < n) {
        ty.fill(-1);
        S.fill(false), T.fill(false);
        int x = -1;
        for (int i = 0; i < n; ++i) {
            if (mx[i] < 0) { x = i; break; }
        }
        S[x] = true;
        for (int j = 0; j < n; ++j) {
            slk[j] = lx[x] + ly[j] - A[x][j];
            slkx[j] = x;
        }

        while (true) {
            int y = -1;
            for (int j = 0; j < n; ++j) {
                if (!slk[j] && !T[j]) { y = j; break; }
            }
            if (y < 0) {
                int delta = INT_MAX;
                for (int j = 0; j < n; ++j) if (!T[j]) {
                    delta = min(delta, slk[j]);
                }
                for (int i = 0; i < n; ++i) {
                    if (S[i]) lx[i] -= delta;
                    if (T[i]) ly[i] += delta;
                }
                for (int j = 0; j < n; ++j) if (!T[j]) {
                    slk[j] -= delta;
                    if (!slk[j]) y = j;
                }
            }
            ty[y] = slkx[y];

            if (my[y] < 0) {
                while (y != -1) {
                    x = ty[y];
                    my[y] = x;
                    int yy = mx[x];
                    mx[x] = y;
                    y = yy;
                }
                ++m;
                break;
            }
            else {
                int z = my[y];
                S[z] = true, T[y] = true;
                for (int y = 0; y < n; ++y) {
                    int s = lx[z] + ly[y] - A[z][y];
                    if (s < slk[y]) {
                        slk[y] = s;
                        slkx[y] = z;
                    }
                }
            }
        }
    }

    int ans = 0;
    for (int i = 0; i < n; ++i) ans += lx[i] + ly[i];
    cout << (n * ans) << '\n';
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) cout << lx[i] + ly[j] << ' ';
        cout << '\n';
    }
    return 0;
}
