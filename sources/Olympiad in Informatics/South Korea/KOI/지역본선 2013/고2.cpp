/*
 * 한국정보올림피아드, 지역본선 2013, 고등부 2. 탐사
 * BOJ 7577
 * JUNGOL 2614
 *
 * system of difference constraints
 * Date: 2023.8.9
 */

#include<bits/stdc++.h>
using namespace std;

int dist[50][50];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);

    int K, N; cin >> K >> N;
    memset(dist, 0x3f, sizeof dist);
    for (int x = 0; x < K; ++x) {
        dist[x][x+1] = 1;
        dist[x+1][x] = 0;
    }
    while (N--) {
        int x, y, w; cin >> x >> y >> w;
        dist[x-1][y] = min(dist[x-1][y], w);
        dist[y][x-1] = min(dist[y][x-1], -w);
    }

    for (int z = 0; z <= K; ++z)
    for (int x = 0; x <= K; ++x)
    for (int y = 0; y <= K; ++y)
        dist[x][y] = min(dist[x][y], dist[x][z] + dist[z][y]);

    for (int x = 0; x <= K; ++x) if (dist[x][x] < 0) {
        cout << "NONE"; return 0;
    }
    for (int x = 1; x <= K; ++x)
        cout << (dist[0][x-1] < dist[0][x]? '#' : '-');

    return 0;
}
