/*
 * North American Invitational Programming Contest, NAIPC 2019 D. It's a Mod, Mod, Mod, Mod World
 * BOJ 16998 - floor sum of arithmetic progression
 * Date: 2024.3.11
 */

#include<iostream>
using namespace std;
using i64 = int64_t;

i64 solve(i64 a, i64 b, i64 c, i64 n) {
    if (!a) return (n+1)*(b/c);
    if (a >= c || b >= c) {
        return n*(n+1)/2*(a/c) + (n+1)*(b/c) + solve(a%c, b%c, c, n);
    }
    i64 m = (a*n + b)/c;
    return m*n - solve(c, c-b-1, a, m-1);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int q; cin >> q;
    while (q--) {
        i64 p, q, n; cin >> p >> q >> n;
        i64 res = solve(p, 0, q, n);
        cout << n*(n+1)/2*p - res*q << '\n';
    }
    return 0;
}
