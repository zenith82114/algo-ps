/*
 * ICPC, Regionals, Asia Pacific, Korea,
 * Asia Regional - Seoul 2019 K. Washer
 * BOJ 17978
 * JUNGOL 4394
 *
 * 3D geometry, bruteforce
 * Date: 2023.1.11
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;

struct vec3 {
    i64 x, y, z;
    vec3() = default;
    vec3(int x, int y, int z): x(x), y(y), z(z) {}
    vec3 operator-(const vec3& v) const {
        return vec3(x - v.x, y - v.y, z - v.z);
    }
    vec3 cross(const vec3& v) const {
        return vec3(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
    }
    i64 dot(const vec3& v) const {
        return x * v.x + y * v.y + z * v.z;
    }
};

struct vec3_set {
    i64 sx = 0L, sy = 0L, sz = 0L;
    i64 ssx = 0L, ssy = 0L, ssz = 0L;
    int n = 0;
    void add(const vec3& v) {
        n++;
        sx += v.x, sy += v.y, sz += v.z;
        ssx += v.x * v.x, ssy += v.y * v.y, ssz += v.z * v.z;
    }
    void remove(const vec3& v) {
        n--;
        sx -= v.x, sy -= v.y, sz -= v.z;
        ssx -= v.x * v.x, ssy -= v.y * v.y, ssz -= v.z * v.z;
    }
    double sse() {
        if (n == 0) return 0.;
        return ssx + ssy + ssz - (double)(sx * sx + sy * sy + sz * sz)/n;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(6);

    int N, K; cin >> N >> K;
    vector<vec3> vs(N);
    vec3_set s;
    for (auto& v : vs) {
        cin >> v.x >> v.y >> v.z;
        s.add(v);
    }
    double ans = s.sse();
    if (K == 1) {
        cout << ans << '\n';
        return 0;
    }

    if (N > 2) {
        for (int i = 0; i < N; ++i)
        for (int j = i+1; j < N; ++j)
        for (int k = j+1; k < N; ++k) {
            vec3_set s1, s2;
            vec3 n = (vs[j] - vs[i]).cross(vs[k] - vs[i]);
            for (int l = 0; l < N; ++l) if (l != i && l != j && l != k)
                (n.dot(vs[l] - vs[i]) < 0? s1 : s2).add(vs[l]);

            for (int l = 0; l < 8; ++l) {
                (l & 1? s1 : s2).add(vs[i]);
                (l & 2? s1 : s2).add(vs[j]);
                (l & 4? s1 : s2).add(vs[k]);
                ans = min(ans, s1.sse() + s2.sse());
                (l & 1? s1 : s2).remove(vs[i]);
                (l & 2? s1 : s2).remove(vs[j]);
                (l & 4? s1 : s2).remove(vs[k]);
            }
        }
    }
    else ans = 0.;
    cout << ans << '\n';
    return 0;
}
