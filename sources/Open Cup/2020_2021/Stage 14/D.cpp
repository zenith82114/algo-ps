/*
 * Open Cup 2020/2021 Stage 14: Grand Prix of Tokyo
 * D. Do Use FFT
 * QOJ 3085
 *
 * DnC, NTT
 * Date: 2026.7.27
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;
using ii = pair<int, int>;

const int MOD = 998'244'353;
const int BASE_ROOT = 15'311'432;
const int BASE_ROOT_IDX = 23;
const int MAXN = 2.5e5+4;

struct mint {
    int val;
    mint(): val(0) {}
    mint(int v) {
        val = (-MOD <= v && v < MOD)? v : v % MOD;
        if (val < 0) val += MOD;
    }
    mint(const mint& x): val(x.val) {}

    friend istream& operator>>(istream& is, mint& x) {
        int v; is >> v; x = mint(v); return is;
    }
    friend ostream& operator<<(ostream& os, const mint& x) {
        return os << x.val;
    }
    mint operator-() const { return mint(-val); }
    mint pow(int e) const {
        mint y(1), x(*this);
        for (; e; e >>= 1) { if (e&1) { y *= x; } x *= x; }
        return y;
    }
    mint inv() const { return pow(MOD - 2); }

    bool operator==(const mint& x) const { return val == x.val; }
    bool operator!=(const mint& x) const { return val != x.val; }
    bool operator!() const { return !val; }
    mint operator+(const mint& x) const { return mint(*this) += x; }
    mint& operator+=(const mint& x) {
        if ((val += x.val) >= MOD) val -= MOD;
        return *this;
    }
    mint operator-(const mint& x) const { return mint(*this) -= x; }
    mint& operator-=(const mint& x) {
        if ((val -= x.val) < 0) val += MOD;
        return *this;
    }
    mint operator*(const mint& x) const { return mint(*this) *= x; }
    mint& operator*=(const mint& x) {
        val = (1ll * val * x.val) % MOD; return *this;
    }
    mint operator/(const mint& x) const { return mint(*this) /= x; }
    mint& operator/=(const mint& x) {
        return (*this) *= x.inv();
    }
};

array<mint, BASE_ROOT_IDX+1> rou, irou;

void init_consts() {
    rou[BASE_ROOT_IDX] = BASE_ROOT;
    for (int i = BASE_ROOT_IDX; i > 0; --i) rou[i-1] = rou[i] * rou[i];
    for (int i = 1; i <= BASE_ROOT_IDX; ++i) irou[i] = rou[i].inv();
}

using poly = vector<mint>;

void ntt(poly& f, bool inv) {
    int d = f.size();
    assert((d & (d-1)) == 0);

    for (int i = 1, j = 0; i < d; ++i) {
        int t = d/2;
        for (; j & t; t >>= 1) j ^= t;
        j ^= t;
        if (i < j) swap(f[i], f[j]);
    }

    for (int n = 2, rn = 1; n <= d; n *= 2, ++rn) {
        mint w((inv ? irou : rou)[rn]);

        for (int m = 0; m < d; m += n) {
            mint z(1);
            for (int i = 0, j = n/2; j < n; ++i, ++j) {
                mint a(f[m|i]);
                mint b(f[m|j] * z);
                f[m|i] = a + b;
                f[m|j] = a - b;
                z *= w;
            }
        }
    }
    if (inv) {
        mint invd = mint(d).inv();
        for (mint& a : f) a *= invd;
    }
}

poly poly_add(poly f, const poly& g) {
    size_t df = f.size(), dg = g.size();

    for (size_t i = 0; i < min(df, dg); ++i) f[i] += g[i];
    for (size_t i = df; i < dg; ++i) f.push_back(g[i]);
    return f;
}

poly poly_mul(poly f, poly g) {
    size_t df = f.size(), dg = g.size();
    if (!df || !dg) return {};

    size_t sz = 1; while (sz < df+dg-1) sz *= 2;
    f.resize(sz, 0); ntt(f, false);
    g.resize(sz, 0); ntt(g, false);
    for (size_t i = 0; i < sz; ++i) f[i] *= g[i];
    ntt(f, true); f.resize(df+dg-1);
    return f;
}

poly poly_inv(const poly& f, int m) {
    assert(f[0] != 0);

    int df = f.size();
    poly g { f[0].inv() };

    for (int k = 1; k < m; k *= 2) {
        poly h(f.begin(), f.begin() + min(df, 2*k));
        h = poly_mul(h, g);
        for (mint& hi : h) hi *= -1;
        h[0] += 2;
        g = poly_mul(g, h);
        g.resize(2*k);
    }
    g.resize(m);
    return g;
}

array<mint, MAXN> A, B, C;
array<poly, 4*MAXN> Q;

pair<poly, poly> build_G(int l, int r) {
    if (l == r) {
        poly D { 1, -A[l] }, U { C[l] };
        return make_pair(D, U);
    }

    int m = (l + r)/2;
    auto [DL, UL] = build_G(l, m);
    auto [DR, UR] = build_G(m+1, r);

    poly D = poly_mul(DL, DR);
    poly U = poly_add(poly_mul(UL, DR), poly_mul(UR, DL));
    return make_pair(D, U);
}

void build_Q(int idx, int l, int r) {
    if (l == r) {
        Q[idx] = { B[l], 1 };
        return;
    }

    int m = (l + r)/2;
    build_Q(2*idx, l, m);
    build_Q(2*idx+1, m+1, r);
    Q[idx] = poly_mul(Q[2*idx], Q[2*idx+1]);
}

array<mint, MAXN> ans;

void solve(int idx, int l, int r, poly h) {
    if (l == r) {
        ans[l] = h[0]*B[l] + h[1];
        return;
    }

    int m = (l + r)/2;
    int a = m - l + 1;
    int b = r - m;

    poly hl(begin(h), begin(h) + a+1);
    solve(2*idx, l, m, hl);

    poly q = Q[2*idx];
    reverse(begin(q), end(q));
    poly hr = poly_mul(h, q);
    hr.erase(begin(hr), begin(hr) + a);
    hr.resize(b+1);
    solve(2*idx+1, m+1, r, hr);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    init_consts();

    int n; cin >> n;
    for (int i = 1; i <= n; ++i) cin >> A[i];
    for (int i = 1; i <= n; ++i) cin >> B[i];
    for (int i = 1; i <= n; ++i) cin >> C[i];

    auto [D, U] = build_G(1, n);
    poly invD = poly_inv(D, n+1);
    poly G = poly_mul(U, invD);
    G.resize(n+1);

    build_Q(1, 1, n);

    solve(1, 1, n, G);
    for (int i = 1; i <= n; ++i) cout << ans[i] << ' ';
    return 0;
}
