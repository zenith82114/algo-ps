/*
 * National Olympiad in Informatics (Singapore), NOI 2018 5. Safety
 * BOJ 19693 - slope trick
 * Date: 2023.2.22
 */

#include<bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    using i64 = int64_t;

    int N, H; cin >> N >> H;
    i64 s; cin >> s;
    priority_queue<i64> ql; ql.emplace(s);
    priority_queue<i64, vector<i64>, greater<i64>> qr; qr.emplace(s);

    i64 D = 0L;
    i64 ym = 0L;
    for (int i = 1; i < N; ++i) {
        cin >> s;
        D += H;
        i64 l0 = ql.top() - D, r0 = qr.top() + D;

        if (l0 < s && s < r0) {
            ql.emplace(s + D);
            qr.emplace(s - D);
        }
        else if (s <= l0) {
            qr.emplace(l0 - D); ql.pop();
            ql.emplace(s + D);
            ql.emplace(s + D);
            ym += l0 - s;
        }
        else {
            ql.emplace(r0 + D); qr.pop();
            qr.emplace(s - D);
            qr.emplace(s - D);
            ym += s - r0;
        }
    }

    cout << ym;
    return 0;
}
