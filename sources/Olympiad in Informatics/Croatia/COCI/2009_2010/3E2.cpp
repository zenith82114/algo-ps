/*
 * Croatian Open Competition in Informatics, COCI 2009/2010, Contest #3 E. PATULJCI
 * BOJ 2912
 * JUNGOL 4187
 *
 * randomization
 * Date: 2023.4.3
 */

#include<bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int color[300'001];
    vector<int> color_idx[10'001];

    int N, C; cin >> N >> C;
    for (int i = 1; i <= N; ++i) {
        cin >> color[i];
        color_idx[color[i]].emplace_back(i);
    }

    default_random_engine en(chrono::system_clock::now().time_since_epoch().count());

    int M; cin >> M;
    while (M--) {
        int a, b; cin >> a >> b;
        if (a == b) {
            cout << "yes " << color[a] << '\n';
            continue;
        }

        uniform_int_distribution<int> dist(a, b);
        bool flag = false;
        int trial = 64;
        int i = 0;
        while (!flag && trial--) {
            i = dist(en);
            auto& ci = color_idx[color[i]];
            int cnt
                = upper_bound(ci.begin(), ci.end(), b)
                - lower_bound(ci.begin(), ci.end(), a);
            flag = (2 * cnt > b - a + 1);
        }
        if (flag) cout << "yes " << color[i] << '\n';
        else cout << "no\n";
    }

    return 0;
}
