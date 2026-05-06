/*
 * Stanford Local ACM Programming Contest, SLPC 2009 G. Rectangles Too!
 * BOJ 7658 - LIS
 * Date: 2023.6.25
 */

#include<bits/stdc++.h>
using namespace std;

struct rect {
    int x1, y1, x2, y2;
    bool operator<(const rect& r) const {
        return make_tuple(x1, y1, x2, y2) < make_tuple(r.x1, r.y1, r.x2, r.y2);
    }
};

vector<map<int, int> > v;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);

    int N; cin >> N;
    while (N) {
        vector<rect> A(N);
        for (auto& [x1, y1, x2, y2] : A) cin >> x1 >> y1 >> x2 >> y2;
        sort(A.begin(), A.end());

        v.resize(1); v[0].clear();
        v[0].emplace(A[0].x2, A[0].y2);
        for (int i = 1; i < N; ++i) {
            const auto& [x1, y1, x2, y2] = A[i];

            int l = 0, r = v.size();
            while (l != r) {
                int m = (l + r)>>1;
                auto& s = v[m];
                auto p = s.lower_bound(x1);
                if (p != s.begin() && prev(p)->second < y1) l = m+1;
                else r = m;
            }
            if (l == (int)v.size()) {
                v.emplace_back();
                v.back().emplace(x2, y2);
            }
            else {
                auto& s = v[l];
                auto p = s.lower_bound(x2);
                if (p != s.begin() && prev(p)->second <= y2) continue;
                while (p != s.end() && p->second >= y2) p = s.erase(p);
                s.emplace(x2, y2);
            }
        }
        cout << v.size() << '\n';
        cin >> N;
    }

    return 0;
}
