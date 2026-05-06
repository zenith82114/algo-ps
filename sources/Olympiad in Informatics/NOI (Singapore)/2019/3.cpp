/*
 * National Olympiad in Informatics (Singapore), NOI 2019 3. Feast
 * BOJ 19672 - Aliens trick
 * Date: 2025.4.17
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;

int N, K;
i64 s[300'001] {};

pair<i64, i64> eval(i64 lmd) {
    i64 dp = 0, mem = 0;
    int cnt = 0, mcnt = 0;
    for (int i = 1; i <= N; ++i) {
        if (dp < mem + s[i] - lmd) {
            dp = mem + s[i] - lmd;
            cnt = mcnt + 1;
        }
        if (mem < dp - s[i]) {
            mem = dp - s[i];
            mcnt = cnt;
        }
    }
    return { dp, cnt };
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> K;
    for (int i = 1; i <= N; ++i) {
        cin >> s[i]; s[i] += s[i-1];
    }

    i64 lo = -1, hi = 1e16;
    while (lo + 1 < hi) {
        i64 mid = (lo + hi)>>1;
        (eval(mid).second > K? lo : hi) = mid;
    }
    auto [dp, cnt] = eval(hi);
    cout << dp + hi * K;
    return 0;
}
