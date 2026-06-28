/*
 * Russian Olympiad in Informatics, Russia Team High School Programming Contest 2020
 * G. Cooking
 * QOJ 4299
 *
 * graph theory, min cost flow
 * Date: 2026.6.28
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;
using ii = pair<int, int>;
const int INF = 1e9;

int n, V;
int a[11], b[11], a_sum = 0;
vector<int> a_odd;

int cap[22][22] {}, wgt[22][22] {};
bitset<22> inq;
array<int, 22> dist, pred;

int ans = INF;

bool spfa() {
    queue<int> q; q.push(0);
    inq.reset();
    dist.fill(INF); dist[0] = 0;

    while (!q.empty()) {
        int x = q.front(); q.pop(); inq.reset(x);

        for (int y = 0; y < V; ++y) {
            if (cap[x][y] > 0 && dist[y] > dist[x] + wgt[x][y]) {
                dist[y] = dist[x] + wgt[x][y];
                pred[y] = x;
                if (!inq[y]) { q.push(y); inq.set(y); }
            }
        }
    }
    return dist[V-1] < INF;
}

void go(size_t ptr) {
    if (ptr < a_odd.size()) {
        int i = a_odd[ptr];
        b[i] = a[i]/2; go(ptr+1);
        b[i] = (a[i]+1)/2; go(ptr+1);
        return;
    }

    for (int i = 1; i <= n; ++i) {
        cap[0][i] = b[i];
        cap[i][0] = 0;
        cap[n + i][V-1] = a[i] - b[i];
        cap[V-1][n + i] = 0;
        for (int j = 1; j <= n; ++j) {
            cap[i][n + j] = INF;
            cap[n + j][i] = 0;
        }
    }

    int flow = 0, cost = 0;

    while (spfa()) {
        int df = INF;
        for (int y = V-1; y != 0; y = pred[y]) df = min(df, cap[pred[y]][y]);
        flow += df;

        for (int y = V-1; y != 0; y = pred[y]) {
            cost += df * wgt[pred[y]][y];
            cap[pred[y]][y] -= df;
            cap[y][pred[y]] += df;
        }
    }
    if (flow == a_sum/2) ans = min(ans, cost);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;
    V = 2*n + 2;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        a_sum += a[i];
        if (a[i] & 1) a_odd.push_back(i);
        else b[i] = a[i]/2;
    }
    if (a_sum & 1) { cout << -1; return 0; }

    for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= n; ++j) {
        cin >> wgt[i][n + j];
        wgt[n + j][i] = -wgt[i][n + j];
    }

    go(0);
    cout << ans;
    return 0;
}
