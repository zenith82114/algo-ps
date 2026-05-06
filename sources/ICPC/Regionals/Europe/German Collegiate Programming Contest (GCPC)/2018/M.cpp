/*
 * ICPC, Regionals, Europe, Northwestern Europe Regional Contest,
 * German Collegiate Programming Contest, GCPC 2018 M. Mountaineers
 * BOJ 16074 - parallel binary search
 * Date: 2023.1.8
 */

#include<bits/stdc++.h>
using namespace std;

#define MAX_HEIGHT 1'000'000

class disjoint_sets {
    vector<int> ar;
    int find(int x) {
        if (ar[x] < 1) return x;
        return ar[x] = find(ar[x]);
    }
public:
    disjoint_sets() { ar.resize(512 * 512, -1); }
    void reset() { fill(ar.begin(), ar.end(), -1); }
    void unite(int x1, int y1, int x2, int y2) {
        int p1 = find((x1<<9) | y1);
        int p2 = find((x2<<9) | y2);
        if (p1 != p2) {
            if (ar[p1] < ar[p2]) swap(p1, p2);
            if (ar[p1] == ar[p2]) ar[p2]--;
            ar[p1] = p2;
        }
    }
    bool united(int x1, int y1, int x2, int y2) {
        return find((x1<<9) | y1) == find((x2<<9) | y2);
    }
};

int H[512][512];
vector<pair<int, int>> pls[MAX_HEIGHT +1];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int M, N, Q; cin >> M >> N >> Q;
    for (int x = 1; x <= M; ++x)
    for (int y = 1; y <= N; ++y) {
        cin >> H[x][y];
        pls[H[x][y]].emplace_back(x, y);
    }

    struct Query { int x1, y1, x2, y2; };
    vector<Query> que(Q);
    vector<int> lo(Q, 1), hi(Q, MAX_HEIGHT);
    for (int i = 0; i < Q; ++i) {
        auto& q = que[i];
        cin >> q.x1 >> q.y1 >> q.x2 >> q.y2;
        if (q.x1 == q.x2 && q.y1 == q.y2)
            lo[i] = hi[i] = H[q.x1][q.y1];
    }

    vector<vector<int>> qls(MAX_HEIGHT +1);
    disjoint_sets dsu;

    const int dx[4] = {1, -1, 0, 0};
    const int dy[4] = {0, 0, 1, -1};

    for (int iter = 1; iter < MAX_HEIGHT; iter <<= 1) {
        for (auto& ql : qls) ql.clear();

        for (int i = 0; i < Q; ++i) if (lo[i] != hi[i])
            qls[(lo[i] + hi[i])/2].emplace_back(i);

        dsu.reset();
        for (int mid = 1; mid <= MAX_HEIGHT; ++mid) {
            for (const auto& [x, y] : pls[mid]) {
                for (int k = 0; k < 4; ++k) {
                    int nx = x + dx[k];
                    int ny = y + dy[k];
                    if (nx == 0 || nx > M || ny == 0 || ny > N) continue;
                    if (H[nx][ny] <= mid) dsu.unite(x, y, nx, ny);
                }
            }
            for (const int& i : qls[mid]) {
                const auto& q = que[i];
                if (dsu.united(q.x1, q.y1, q.x2, q.y2))
                    hi[i] = mid;
                else
                    lo[i] = mid+1;
            }
        }
    }

    for (const int& l : lo) cout << l << '\n';
    return 0;
}
