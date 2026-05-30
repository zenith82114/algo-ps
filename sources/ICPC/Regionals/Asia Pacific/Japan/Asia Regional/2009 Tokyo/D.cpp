/*
 * ICPC, Regionals, Asia Pacific, Japan, 2009 Asia Tokyo Regional Contest D. Separate Points
 * JUNGOL 13687
 *
 * convex hull
 * Date: 2022.1.22
 */

#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

struct vec2 {
    int x, y;
    bool operator<(const vec2& v) const {
        return y != v.y ? y < v.y : x < v.x;
    };
    vec2 operator-(const vec2& v) const {
        return { x-v.x, y-v.y };
    }
};
int64_t cross(const vec2& v, const vec2& w) {
    return v.x*w.y - v.y*w.x;
}
int64_t dot(const vec2& v, const vec2& w) {
    return v.x*w.x + v.y*w.y;
}
int ccw(const vec2& o, const vec2& p, const vec2& q) {
    auto k = cross(p-o, q-o);
    return (k < 0) ? -1 : (k > 0);
}
bool intersects(vec2 a, vec2 b, vec2 c, vec2 d) {
    int ab = ccw(a,b,c) * ccw(a,b,d);
    int cd = ccw(c,d,a) * ccw(c,d,b);
    if (!(ab || cd)) {
        if (b < a) swap(a,b);
        if (d < c) swap(c,d);
        return !(b < c || d < a);
    }
    return ab <= 0 && cd <= 0;
}

void get_convex_hull(vector<vec2>& G, vector<vec2>& H) {
    const int N = G.size();
    int M = 0;
    for (int n = 0; n < N; ++n) {
        if (G[n] < G[M]) M = n;
    }
    swap(G.front(), G[M]);
    vec2 orig = G.front();
    sort(++G.begin(), G.end(), [orig](const vec2& p, const vec2& q) {
        int k = ccw(orig,p,q);
        return k != 0 ? k > 0 : dot(q - p, orig - p) < 0;
    });

    M = 0;
    for (auto &p : G) {
        while (M > 1 && ccw(H[M-2], H[M-1], p) <= 0) {
            H.pop_back();
            M--;
        }
        H.push_back(p);
        M++;
    }
}

bool separable(vector<vec2>& H1, vector<vec2>& H2) {
    int M1 = H1.size(), M2 = H2.size();
    bool b1 = false, b2 = false;
    if (M1 < M2) {
        swap(M1, M2);
        swap(H1, H2);
    }
    if (M2 > 1) {
        for (int i = 0; i < M1; ++i) {
            for (int j = 0; j < M2; ++j) {
                if (intersects(H1[i], H1[(i+1)%M1], H2[j], H2[(j+1)%M2]))
                    return false;
            }
        }
        if (M1 > 2) {
            for (int i = 0; !b1 && i < M1; ++i) {
                for (int j = 0; j < M2; ++j) {
                    if (ccw(H1[i], H1[(i+1)%M1], H2[j]) <= 0) {
                        b1 = true; break;
                    }
                }
            }
        }
        if (M2 > 2) {
            for (int j = 0; !b2 && j < M2; ++j) {
                for (int i = 0; i < M1; ++i) {
                    if (ccw(H2[j], H2[(j+1)%M2], H1[i]) <= 0) {
                        b2 = true; break;
                    }
                }
            }
        }
        if (b1 != b2)
            return false;
    }
    else if (M1 > 1) {
        for (int i = 0; i < M1; ++i) {
            auto k = ccw(H1[i], H1[(i+1)%M1], H2[0]);
            if (k < 0)
                return true;
            if (k == 0 && dot(H1[i]-H2[0], H1[(i+1)%M1]-H2[0]) <= 0)
                return false;
        }
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int N1, N2; cin >> N1 >> N2;
    for (; N1 | N2; cin >> N1 >> N2) {
        vector<vec2> G1(N1), G2(N2);
        for (auto& v1 : G1) cin >> v1.x >> v1.y;
        for (auto& v2 : G2) cin >> v2.x >> v2.y;
        vector<vec2> H1, H2;
        get_convex_hull(G1, H1);
        get_convex_hull(G2, H2);
        cout << (separable(H1, H2) ? "YES\n" : "NO\n");
    }

    return 0;
}
