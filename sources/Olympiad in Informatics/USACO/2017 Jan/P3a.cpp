/*
 * USA Computing Olympiad, USACO 2017 January Contest, Platinum 3. Subsequence Reversal
 * BOJ 14448
 * JUNGOL 4000
 *
 * simulated annealing
 * Date: 2023.6.20
 *
 * [NOTE]
 * The chance of being accepted is pretty low,
 * so one is advised to consult it only as reference.
 */

#include<bits/stdc++.h>
using namespace std;

mt19937 rng((unsigned)chrono::steady_clock::now().time_since_epoch().count());

int rand_int(int a, int b) {
    if (a == b) return a;
    return uniform_int_distribution(a, b)(rng);
}
double rand_dbl(double a = 0., double b = 1.) {
    return uniform_real_distribution(a, b)(rng);
}

int eval(vector<int>& arr, const bitset<50>& state) {
    const int n = arr.size();
    int i = 0, j = n-1;
    while (i < j) {
        while (i < j && !state[i]) i++;
        while (i < j && !state[j]) j--;
        if (i < j) swap(arr[i++], arr[j--]);
    }
    vector<int> dp;
    for (int& x : arr) {
        auto p = upper_bound(dp.begin(), dp.end(), x);
        if (p == dp.end()) dp.emplace_back(x);
        else *p = x;
    }
    i = 0, j = n-1;
    while (i < j) {
        while (i < j && !state[i]) i++;
        while (i < j && !state[j]) j--;
        if (i < j) swap(arr[i++], arr[j--]);
    }
    return dp.size();
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);

    int N; cin >> N;
    if (N < 3) { cout << N; return 0; }
    vector<int> arr(N); for (int& x : arr) cin >> x;

    constexpr int    SHOTS = 10;
    constexpr int    TIMEOUT = 100'000;
    constexpr double INIT_TEMP = 10.;
    constexpr double COOL_RATE = 0.9999;

    int ans = 1;

    for (int shot = 0; shot < SHOTS; ++shot) {
        bitset<50> state;
        for (int i = 0; i < N; ++i)
            if (rand_dbl() < .5) state.set(i);
        int score = eval(arr, state);
        int max_score = score;
        double temp = INIT_TEMP;

        for (int clk = 0; clk < TIMEOUT; ++clk) {
            auto nstate = state;
            nstate.flip(rand_int(0, N-1));
            int nscore = eval(arr, nstate);
            if (rand_dbl() < exp((nscore - score) / temp)) {
                state = nstate;
                score = nscore;
            }
            max_score = max(max_score, score);
            temp *= COOL_RATE;
        }
        ans = max(ans, max_score);
    }
    cout << ans;
    return 0;
}
