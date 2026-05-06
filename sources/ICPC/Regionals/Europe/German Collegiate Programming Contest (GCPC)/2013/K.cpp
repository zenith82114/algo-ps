/*
 * ICPC, Regionals, Europe, Northwestern Europe Regional Contest,
 * German Collegiate Programming Contest, GCPC 2013 K. Triangles
 * BOJ 9212 - geometry
 * Date: 2024.2.21
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;
constexpr double eps = 1e-6;

struct vec3 {
    i64 x, y, z;
    vec3() = default;
    vec3(i64 x, i64 y, i64 z): x(x), y(y), z(z) {}
    vec3 operator-(const vec3& v) const {
        return vec3(x - v.x, y - v.y, z - v.z);
    }
    vec3 cross(const vec3& v) const {
        return vec3(y*v.z - z*v.y, z*v.x - x*v.z, x*v.y - y*v.x);
    }
    i64 dot(const vec3& v) const {
        return x*v.x + y*v.y + z*v.z;
    }
};
using triangle = array<vec3, 3>;

bool inside(triangle& t, tuple<double, double, double>& p) {
    vec3 u = t[0]-t[2], v = t[1]-t[2];
    auto& [px, py, pz] = p;
    double wx = px-t[2].x, wy = py-t[2].y, wz = pz-t[2].z;
    i64 uu = u.dot(u), uv = u.dot(v), vv = v.dot(v);
    double uw = u.x*wx + u.y*wy + u.z*wz;
    double vw = v.x*wx + v.y*wy + v.z*wz;
    i64 det = uu*vv - uv*uv;
    double a = (vv*uw - uv*vw)/det;
    double b = (uu*vw - uv*uw)/det;
    return a > eps && b > eps && 1-a-b > eps;
}

bool tangled(triangle& t, triangle& s) {
    vector<tuple<double, double, double> > intersect;
    vec3 n = (t[1]-t[0]).cross(t[2]-t[0]);
    for (const auto& si : s) if (n.dot(si-t[0]) == 0) {
        intersect.emplace_back(si.x, si.y, si.z);
    }
    if (intersect.size() > 1) return false;

    for (int i = 0; i < 3; ++i) {
        const auto& s0 = s[i];
        const auto& s1 = s[(i+1)%3];
        if (n.dot(s1-s0) == 0) continue;
        double k = (double)(n.dot(t[0]-s0))/n.dot(s1-s0);
        if (eps < k && k < 1-eps) {
            intersect.emplace_back(
                (1-k)*s0.x + k*s1.x,
                (1-k)*s0.y + k*s1.y,
                (1-k)*s0.z + k*s1.z);
        }
    }
    if (intersect.size() != 2) return false;
    return inside(t, intersect[0]) != inside(t, intersect[1]);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    triangle t, s;
    int tc; cin >> tc; while (tc--) {
        for (auto& [x, y, z] : t) cin >> x >> y >> z;
        for (auto& [x, y, z] : s) cin >> x >> y >> z;
        cout << (tangled(t, s)? "YES\n" : "NO\n");
    }
    return 0;
}
