/*
 * 한국정보올림피아드, KOI 2018, 고등부 3. 조화로운 행렬
 * BOJ 15977
 * JUNGOL 3236
 *
 * O(N log N) LIS
 * Date: 2023.5.12
 */

#include<bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);

    int M, N; cin >> M >> N;
    if (M == 2) {
        vector<pair<int, int> > A(N);
        for (auto& [x, y] : A) cin >> x;
        for (auto& [x, y] : A) cin >> y;
        sort(A.begin(), A.end());

        vector<int> v;
        for (const auto& [x, y] : A) {
            auto p = lower_bound(v.begin(), v.end(), y);
            if (p != v.end()) *p = y;
            else v.emplace_back(y);
        }

        cout << v.size();
    } else {
        struct iii { int x, y, z; };
        vector<iii> A(N);
        for (iii& a : A) cin >> a.x;
        for (iii& a : A) cin >> a.y;
        for (iii& a : A) cin >> a.z;
        sort(A.begin(), A.end(), [] (const iii& a, const iii& b) {
            return a.x < b.x;
        });

        vector<map<int, int> > v(1);
        v[0].emplace(A[0].y, A[0].z);
        for (int i = 1; i < N; ++i) {
            const auto& [x, y, z] = A[i];

            int l = 0, r = v.size();
            while (l != r) {
                int m = (l + r)>>1;
                auto& s = v[m];
                auto p = s.lower_bound(y);
                if (p != s.begin() && prev(p)->second < z) l = m+1; else r = m;
            }
            if (l == (int)v.size()) v.emplace_back(), v.back().emplace(y, z);
            else {
                auto& s = v[l];
                auto p = s.lower_bound(y);
                while (p != s.end() && p->second > z) p = s.erase(p);
                s.emplace(y, z);
            }
        }

        cout << v.size();
    }

    return 0;
}
