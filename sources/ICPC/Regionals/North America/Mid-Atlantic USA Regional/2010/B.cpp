/*
 * ICPC, Regionals, North America,
 * 2010 Mid-Atlantic USA Regional Programming Contest B. Balloons
 * BOJ 4716 - greedy
 * Date: 2023.5.1
 */

#include<bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int N, A, B; cin >> N >> A >> B;
    while (N | A | B) {
        vector<int> K(N);
        vector<tuple<int, int, bool> > v;

        int ans = 0;
        for (int i = 0; i < N; ++i) {
            int a, b; cin >> K[i] >> a >> b;
            ans += K[i] * min(a, b);
            v.emplace_back(-abs(a - b), i, a < b);
        }
        sort(v.begin(), v.end());
        for (auto& [w, i, q] : v) {
            int& M = q? A : B;
            int x = min(M, K[i]);
            M -= x; K[i] -= x;
            if (K[i]) {
                (q? B : A) -= K[i];
                ans -= K[i] * w;
            }
        }

        cout << ans << '\n';
        cin >> N >> A >> B;
    }

    return 0;
}
