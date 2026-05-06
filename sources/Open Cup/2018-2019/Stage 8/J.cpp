/*
 * Open Cup 2018/2019 Stage 8: Grand Prix of Dolgoprudny J. Polynomial
 * BOJ 23648 - bitmask DP, Gray code
 * Date: 2024.6.6
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;

constexpr int MAXD = 20;
constexpr int MAXG = 1<<(MAXD+1);

int main() {
    cin.tie(0)->sync_with_stdio(0);

    vector<int> gray;
    for (int t = 0; t <= MAXD; ++t) {
        int sz = gray.size();
        gray.emplace_back(t);
        for (int i = 0; i < sz; ++i) gray.emplace_back(gray[i]);
    }
    gray.emplace_back(MAXD);

    int d; cin >> d;
    int f = 0;
    for (int i = 0; i <= d; ++i) {
        int x; cin >> x;
        f |= (x<<i);
    }
    i64 n; cin >> n;

    int fe = 0, fo = 0;
    for (int h = f, i = 0; h; h >>= 1, ++i) {
        fe |= (h & (1<<i));
    }
    for (int h = f>>1, i = 0; h; h >>= 1, ++i) {
        fo |= (h & (1<<i));
    }

    vector<i64> dp_old(MAXG), dp_cur(MAXG);
    int g = 0, bc = 0;
    for (int t : gray) {
        g ^= (1<<t);
        bc += (g & (1<<t))? +1 : -1;
        dp_cur[g] = bc;
    }

    int s = 0;
    for (i64 m = n; m; m >>= 1) ++s;

    for (--s; s >= 0; --s) {
        dp_cur.swap(dp_old);

        if ((n>>s)&1) {
            int g = 0, fge = 0, fgo = 0;
            for (int t : gray) {
                g ^= (1<<t);
                fge ^= (t&1? fo : fe) << ((t+1)>>1);
                fgo ^= (t&1? fe : fo) << (t>>1);
                dp_cur[g] = dp_old[fge] + dp_old[fgo];
            }
        } else {
            int g = 0, ge = 0, go = 0;
            for (int t : gray) {
                g ^= (1<<t);
                (t&1? go : ge) ^= (1 << (t>>1));
                dp_cur[g] = dp_old[ge] + dp_old[go];
            }
        }
    }

    cout << dp_cur[1];
    return 0;
}
