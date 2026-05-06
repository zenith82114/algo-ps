/*
 * ICPC, Regionals, Asia West Continent, Iran, Tehran Site 2014 G. Dragons
 * BOJ 10605 - greedy, disjoint sets
 * Date: 2023.9.3
 */

#include<bits/stdc++.h>
using namespace std;
using ii = pair<int, int>;

class disjoint_sets {
    int ar[301];
public:
    void init(int sz) {
        memset(ar, -1, sz * sizeof(int));
    }
    int find(int x) {
        if (ar[x] < 0) return x;
        return ar[x] = find(ar[x]);
    }
    void unite(int x, int y) {
        x = find(x), y = find(y);
        if (x == y) return;
        ar[y] = x;
    }
} dsu;

vector<ii> dra[301];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);

    int N, M, K;
    for (cin >> N >> M >> K; N; cin >> N >> M >> K) {

        dsu.init(N+1);
        while (M--) {
            int x, y; cin >> x >> y;
            dsu.unite(x, y);
        }

        for (int x = 1; x <= N; ++x) dra[x].clear();
        for (int k = 0; k < K; ++k) {
            int c, s, n; cin >> c >> s >> n;
            dra[dsu.find(c)].emplace_back(s, n);
        }

        int ans = 0;

        for (int x = 1; x <= N; ++x) {
            auto& v = dra[x];
            sort(v.begin(), v.end(), [] (const ii& a, const ii& b) {
                return a.second > b.second;
            });
            auto it = v.begin();
            int ppl = INT32_MAX, sum = 0;
            while (it != v.end()) {
                int dsum = 0;
                ppl = it->second;
                while (it != v.end() && it->second == ppl) {
                    dsum += it->first;
                    ++it;
                }
                sum += dsum;
                if (ppl < sum) {
                    ans += max(ppl + 1, sum - dsum);
                    break;
                }
            }
            if (sum <= ppl) ans += sum;
        }

        cout << ans << '\n';
    }

    return 0;
}
