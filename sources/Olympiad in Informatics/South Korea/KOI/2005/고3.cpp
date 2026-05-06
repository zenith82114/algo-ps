/*
 * 한국정보올림피아드, KOI 2005, 고등부 3. 소방차
 * BOJ 2586
 * JUNGOL 2017
 *
 * greedy
 * Date: 2023.9.11
 */

#include<bits/stdc++.h>
using namespace std;

vector<int> level[200'000];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);

    int N, M; cin >> N >> M;
    vector<pair<int, int> > v;
    for (int i = 0; i < N; ++i) {
        int x; cin >> x; v.emplace_back(x, 1);
    }
    for (int i = 0; i < M; ++i) {
        int x; cin >> x; v.emplace_back(x, 0);
    }
    sort(v.begin(), v.end());
    int y = M;
    int ymin = M, ymax = M;
    for (const auto& [x, t] : v) {
        if (t) {
            ymax = max(ymax, y);
            level[y++].emplace_back(x);
        } else {
            level[--y].emplace_back(x);
            ymin = min(ymin, y);
        }
    }

    int64_t ans = 0;
    for (int y = ymin; y <= ymax; ++y) {
        const auto& lv = level[y];
        int k = lv.size();
        if (k < 2) continue;
        else if (k & 1) {
            int64_t tmp = 0;
            for (int i = 1; i < k; i += 2) tmp += lv[i+1] - lv[i];
            int64_t opt = tmp;
            for (int i = 1; i < k; i += 2) {
                tmp += 2*lv[i] - lv[i-1] - lv[i+1];
                opt = min(opt, tmp);
            }
            ans += opt;
        } else {
            for (int i = 0; i < k; i += 2) ans += lv[i+1] - lv[i];
        }
    }

    cout << ans;
    return 0;
}
