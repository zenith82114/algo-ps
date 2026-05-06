/*
 * ICPC, Regionals, Europe, Northwestern Europe Regional Contest,
 * Nordic Collegiate Programming Contest, NCPC 2020 I. Infection Estimation
 * Petrozavodsk Programming Camp, Winter 2021, Day 3: Nordic+ Contest 2020 I. Infection Estimation
 * BOJ 21055 - Bayes' theorem
 * Date: 2023.7.12
 */

#include<bits/stdc++.h>
using namespace std;

constexpr int N = 10'000'000;

vector<double> lfact;

double prob(int x, int k, int r) {
    // assume x + k <= N
    double lp = lfact[N-x] - lfact[N-x-k] - lfact[N] + lfact[N-k];
    return r? 1. - exp(lp) : exp(lp);
}

int main() {
    lfact.reserve(N);
    for (int i = 0; i <= N; ++i) lfact.emplace_back(lgamma(i+1));

    vector<int> X;
    for (double x = 100.; x <= 5'000'000; x *= 1.01) {
        X.emplace_back((int)round(x));
    }
    const int M = X.size();
    vector<double> pX(M, 1. / M);

    for (int t = 0; t < 50; ++t) {
        int lo = 1, hi = N;
        int k = 0;
        while (lo < hi) {
            k = (lo + hi)>>1;
            double p = 0.;
            for (int i = 0; i < M; ++i) {
                p += pX[i] * (X[i] + k <= N? prob(X[i], k, 1) : 1);
            }
            if (p > 0.5) hi = k; else lo = k+1;
        }
        cout << "test " << k << endl;

        int r; cin >> r;
        double tot = 0.;
        for (int i = 0; i < M; ++i) {
            pX[i] *= (X[i] + k <= N? prob(X[i], k, r) : r);
            tot += pX[i];
        }
        for (auto& p : pX) p /= tot;
    }

    int me = max_element(pX.begin(), pX.end()) - pX.begin();
    cout << "estimate " << X[me] << endl;
    return 0;
}
