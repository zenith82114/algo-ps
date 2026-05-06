/*
 * ICPC, World Finals, ACM-ICPC World Finals 2017 D. Money for Nothing
 * BOJ 14636
 * JUNGOL 3617
 *
 * DnC DP optimization
 * Date: 2022.2.18
 */

#include<bits/stdc++.h>
using namespace std;
using ll = long long;

struct Point {
    int x, y;
    Point() {};
    Point(const Point& p) {
        x = p.x, y = p.y;
    }
};
vector<Point> tmp, A, B;

ll dnc(int li, int ri, int lj, int rj) {
    if (li > ri || lj > rj)
        return 0;
    int i = (li + ri)>>1;
    int J = -1, K = rj+1;

    ll F = 0;
    for (int j = lj; j <= rj; ++j) {
        if (B[j].y > A[i].y && B[j].x > A[i].x) {
            ll f = 1ll * (B[j].y - A[i].y) * (B[j].x - A[i].x);
            if (F < f)
                F = f, J = j;
        }
        if (K > j && B[j].x <= A[i].x)
            K = j;
    }
    ll Fl, Fr;
    if (J != -1) {
        Fl = dnc(li, i-1, J, rj);
        Fr = dnc(i+1, ri, lj, J);
    }
    else {
        Fl = dnc(li, i-1, K, rj);
        Fr = dnc(i+1, ri, lj, K-1);
    }
    return max({F, Fl, Fr});
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int N, M; cin >> N >> M;
    tmp.resize(N);
    for (int n = 0; n < N; ++n)
        cin >> tmp[n].x >> tmp[n].y;
    sort(tmp.begin(), tmp.end(), [](const Point& p, const Point& q) {
        return p.x != q.x ? p.x < q.x : p.y < q.y;
    });
    A.emplace_back(tmp.front());
    for (int n = 1; n < N; ++n)
        if (A.back().x < tmp[n].x && A.back().y > tmp[n].y)
            A.emplace_back(tmp[n]);
    N = A.size();

    tmp.resize(M);
    for (int m = 0; m < M; ++m)
        cin >> tmp[m].x >> tmp[m].y;
    sort(tmp.begin(), tmp.end(), [](const Point& p, const Point& q) {
        return p.x != q.x ? p.x > q.x : p.y > q.y;
    });
    B.emplace_back(tmp.front());
    for (int m = 1; m < M; ++m)
        if (B.back().x > tmp[m].x && B.back().y < tmp[m].y)
            B.emplace_back(tmp[m]);
    M = B.size();

    cout << dnc(0, N-1, 0, M-1) << '\n';
    return 0;
}
