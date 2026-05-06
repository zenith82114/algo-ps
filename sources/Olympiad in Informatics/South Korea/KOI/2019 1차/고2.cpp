/*
 * 한국정보올림피아드, KOI 2019 1차대회, 고등부 2. 점프
 * BOJ 17613
 * JUNGOL 3338
 *
 * DnC
 * Date: 2023.7.12
 */

#include<bits/stdc++.h>
using namespace std;

int v[32];

int dnc(int x, int y) {
    if (!x && !y) return 0;

    int i = 0;
    for (; i+1 < 31 && v[i+1] <= x; ++i);
    if (y < v[i+1])
        return dnc(x - v[i], y - v[i]) + i;

    int j = i;
    for (; j+1 < 31 && v[j+1] <= y; ++j);

    if (i+1 < j)
        return max(1 + ((j-1)*j)/2, dnc(v[j], y));
    else
        return max(dnc(x, v[j] - 1), dnc(v[j], y));
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);

    for (int i = 0; i < 31; ++i) v[i] = (1<<i) -1;

    int T; cin >> T;
    while (T--) {
        int x, y; cin >> x >> y;
        cout << dnc(x, y) << '\n';
    }

    return 0;
}
