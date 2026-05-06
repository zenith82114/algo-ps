/*
 * Polish Olympiad in Informatics, POI 2010/2011, Stage 1 B. Lollipop
 * BOJ 8203 - ad-hoc
 * Date: 2023.2.28
 */

#include<bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    constexpr char ONE = 'W';
    constexpr char TWO = 'T';

    int N, M; cin >> N >> M;
    string A; cin >> A;

    int i = 1;
    for (; i <= N && A[i-1] == TWO; ++i);

    if (i > N) {
        while (M--) {
            int K; cin >> K;
            if (~K & 1 && K <= 2*N)
                cout << 1 << ' ' << K/2;
            else
                cout << "NIE";
            cout << '\n';
        }
    }
    else {
        vector<int> R(2*N +1, -1); R[0] = i-1;
        int S = 0;
        int So = 0, Se = 0;
        for (int j = i; j <= N; ++j) {
            S += A[j-1] == ONE? 1 : 2;
            R[S] = j;
            (S & 1? So : Se) = S;
        }

        while (M--) {
            int K; cin >> K;

            if (K <= S) {
                if (R[K] != -1)
                    cout << i << ' ' << R[K];
                else
                    cout << i+1 << ' ' << R[K+1];
            }
            else {
                if (~K & 1 && !Se) {
                    if (K <= 2*(i-1))
                        cout << 1 << ' ' << K/2;
                    else
                        cout << "NIE";
                }
                else {
                    int& Sp = K & 1? So : Se;
                    if (K <= 2*(i-1) + Sp)
                        cout << i - (K - Sp)/2 << ' ' << R[Sp];
                    else
                        cout << "NIE";
                }
            }
            cout << '\n';
        }
    }

    return 0;
}
