/*
 * Waterloo's local Programming Contests, 26 January, 2002 B. Discrete Logging
 * BOJ 4357 - discrete logarithm; baby-step giant-step
 * Date: 2022.10.3
 */

#include<bits/stdc++.h>
using namespace std;

inline int mul_mod(int a, int b, int p) {
    return (1ll * a * b) % p;
}

inline int exp_mod(int a, int e, int p) {
    int b = 1;
    while (e) {
        if (e&1) b = mul_mod(a, b, p);
        a = mul_mod(a, a, p);
        e >>= 1;
    }
    return b;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    unordered_map<int, int> tbl;

    cin >> std::ws;
    while (cin.peek() != EOF) {
        int p, a, y; cin >> p >> a >> y;
        int q = (int)sqrt(p) + 1;

        int a_j = 1;
        tbl.clear();
        for (int j = 0; j < q; ++j) {
            if (tbl.find(a_j) == tbl.end())
                tbl.emplace(a_j, j);
            a_j = mul_mod(a_j, a, p);
        }

        int a_mq = exp_mod(a_j, p-2, p);
        int ya_miq = y;
        int x = -1;
        for (int i = 0; i < q; ++i) {
            if (tbl.find(ya_miq) != tbl.end()) {
                x = i * q + tbl[ya_miq];
                break;
            }
            ya_miq = mul_mod(ya_miq, a_mq, p);
        }

        if (x != -1) cout << x << '\n';
        else cout << "no solution\n";

        cin >> std::ws;
    }

    return 0;
}
