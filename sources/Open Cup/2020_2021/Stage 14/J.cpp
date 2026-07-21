/*
 * Open Cup 2020/2021 Stage 14: Grand Prix of Tokyo
 * J. Japanese Knowledge
 * QOJ 3091
 *
 * DnC, NTT
 * Date: 2026.7.21
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;
using ii = pair<int, int>;

const int MOD = 998'244'353;
const int BASE_ROOT = 15'311'432;
const int BASE_ROOT_IDX = 23;
const int FAC_RANGE = 1e6;
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

array<mint, FAC_RANGE> fac, ifac;
array<mint, BASE_ROOT_IDX+1> rou, irou;

void init_consts() {
    fac[0] = 1;
    for (int i = 1; i < FAC_RANGE; ++i) fac[i] = fac[i-1] * i;
    ifac[FAC_RANGE-1] = fac[FAC_RANGE-1].inv();
    for (int i = FAC_RANGE-2; i >= 0; --i) ifac[i] = ifac[i+1] * (i+1);

    rou[BASE_ROOT_IDX] = BASE_ROOT;
    for (int i = BASE_ROOT_IDX; i > 0; --i) rou[i-1] = rou[i] * rou[i];
    for (int i = 1; i <= BASE_ROOT_IDX; ++i) irou[i] = rou[i].inv();
}

mint binom(int n, int k) {
    assert(0 <= k && k <= n);
    return fac[n] * ifac[k] * ifac[n-k];
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

void poly_add(poly& f, const poly& g) {
    size_t df = f.size(), dg = g.size();

    for (size_t i = 0; i < min(df, dg); ++i) f[i] += g[i];
    for (size_t i = df; i < dg; ++i) f.push_back(g[i]);
}

void poly_mul(poly& f, poly& g) {
    size_t df = f.size(), dg = g.size();
    if (!df || !dg) { f.clear(); return; }

    size_t sz = 1; while (sz < df+dg-1) sz *= 2;
    f.resize(sz, 0); ntt(f, false);
    g.resize(sz, 0); ntt(g, false);
    for (size_t i = 0; i < sz; ++i) f[i] *= g[i];
    ntt(f, true);
    ntt(g, true);
    f.resize(df+dg-1);
}

void concatenate(poly& f, poly& g) {
    if (f.empty()) f.swap(g);
    else f.insert(end(f), begin(g), end(g));
}

int a[MAXN];

poly dnc(int l, int r, int d, poly& f) {
    if (l == r) {
        mint s(0);
        for (int i = 0; i < a[l] - d; ++i) s += f[i];
        return { s };
    }
    int m = (l + r)/2;
    int W = r - m;
    int H = a[m] - d;

    if (H <= 0) {
        poly ans(m-l+1, 0);
        poly g = dnc(m+1, r, d, f);
        concatenate(ans, g);
        return ans;
    }

    poly f1(begin(f) + H, end(f));
    poly g = dnc(m+1, r, a[m], f1);
    poly temp;

    poly RL(f); RL.resize(H);
    temp.resize(H); for (int i = 0; i < H; ++i) temp[H-1-i] = binom(W-1+i, i);
    poly_mul(RL, temp);
    RL.erase(begin(RL), begin(RL) + H-1);

    poly UL(W); for (int i = 0; i < W; ++i) UL[i] = g[i] * ifac[i];
    temp.resize(H+W-1); for (int i = 0; i < H+W-1; ++i) temp[H+W-2-i] = fac[i];
    poly_mul(UL, temp);
    UL.erase(begin(UL), begin(UL) + W-1);
    UL.resize(H);
    for (int i = 0; i < H; ++i) UL[H-1-i] *= ifac[i];

    poly_add(RL, UL);
    poly ans = dnc(l, m, d, RL);

    poly UD(g); UD.resize(W);
    temp.resize(W); for (int i = 0; i < W; ++i) temp[W-1-i] = binom(H-1+i, i);
    poly_mul(UD, temp);
    UD.erase(begin(UD), begin(UD) + W-1);

    poly RD(H); for (int i = 0; i < H; ++i) RD[i] = f[i] * ifac[i];
    temp.resize(W+H-1); for (int i = 0; i < W+H-1; ++i) temp[W+H-2-i] = fac[i];
    poly_mul(RD, temp);
    RD.erase(begin(RD), begin(RD) + H-1);
    RD.resize(W);
    for (int i = 0; i < W; ++i) RD[W-1-i] *= ifac[i];

    poly_add(UD, RD);
    concatenate(ans, UD);
    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    init_consts();

    int n; cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];

    poly f(a[n], 1);
    poly ans = dnc(1, n, 0, f);
    for (int i = 0; i < n; ++i) cout << ans[i] << ' ';
    cout << 1;
    return 0;
}
