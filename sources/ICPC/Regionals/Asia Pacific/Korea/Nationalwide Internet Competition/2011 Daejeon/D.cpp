/*
 * ICPC, Regionals, Asia Pacific, Korea,
 * Daejeon Nationalwide Internet Competition 2011 D. DSLR
 * BOJ 9019
 *
 * bidirectional BFS
 * Date: 2023.4.21
 */

#include<bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    constexpr char FROM_A = 1, FROM_B = 0, NONE = -1;
    constexpr char OP[6] = "DDSLR";
    char op_pred[10000], visitor[10000];
    int pred[10000], neighbors[5];

    int TC; cin >> TC;
    while (TC--) {
        int A, B; cin >> A >> B;
        queue<int> q; q.push(A); q.push(B);
        memset(visitor, NONE, sizeof visitor);
        visitor[A] = FROM_A;
        visitor[B] = FROM_B;

        bool done = false;
        while (!done) {
            int n = q.front(); q.pop();
            char v = visitor[n];
            if (v == FROM_A) {
                neighbors[1] = n < 5000? n<<1 : (n - 5000)<<1;
                neighbors[2] = n? n-1 : 9999;
                neighbors[3] = (n % 1000) * 10 + n / 1000;
                neighbors[4] = (n % 10) * 1000 + n / 10;
            }
            else {
                neighbors[0] = n>>1;
                neighbors[1] = (n>>1) + 5000;
                neighbors[2] = n < 9999? n+1 : 0;
                neighbors[3] = (n % 10) * 1000 + n / 10;
                neighbors[4] = (n % 1000) * 10 + n / 1000;
            }
            for (int i = (int)v; i < 5; ++i) {
                if (i < 2 && (n & 1) && v == FROM_B) continue;
                int nn = neighbors[i];
                if (visitor[nn] == v) continue;
                else if (visitor[nn] == NONE) {
                    visitor[nn] = v;
                    pred[nn] = n;
                    op_pred[nn] = OP[i];
                    q.push(nn);
                }
                else {
                    int a = n, b = nn;
                    if (v == FROM_B) swap(a, b);
                    string s;
                    for (; a != A; a = pred[a]) s.push_back(op_pred[a]);
                    for (auto rit = s.rbegin(); rit != s.rend(); ++rit) cout << *rit;
                    cout << OP[i];
                    for (; b != B; b = pred[b]) cout << op_pred[b];
                    cout << '\n';
                    done = true;
                    break;
                }
            }
        }
    }

    return 0;
}
