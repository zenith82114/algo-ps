/*
 * ICPC, Regionals, North America,
 * 2013 Southeast USA Regional Programming Contest, Division 1 G.
 * BOJ 9483 - repetitions; Main-Lorentz
 * Date: 2025.7.10
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;

vector<int> z_function(const string& s) {
    int n = s.size();
    vector<int> z(n);
    z[0] = n;
    for (int l = 0, r = 0, i = 1; i < n; ++i) {
        if (i < r) z[i] = min(z[i - l], r - i);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) ++z[i];
        if (r < i + z[i]) l = i, r = i + z[i];
    }
    return z;
}

int lookup_or_zero(const vector<int>& z, int i) {
    return (0 <= i && i < (int)z.size()? z[i] : 0);
}

i64 dnc(const string& s) {
    int n = s.size();
    if (n == 1) return 0;

    int m = n / 2;
    string s1 = s.substr(0, m);
    string s2 = s.substr(m);
    string rs1(s1.rbegin(), s1.rend());
    string rs2(s2.rbegin(), s2.rend());
    i64 ans = dnc(s1) + dnc(s2);

    auto z1 = z_function(rs1);
    auto z2 = z_function(s2 + '.' + s1);
    for (int c = 0; c < m; ++c) {
        int p = m - c;
        int k1 = lookup_or_zero(z1, p);
        int k2 = lookup_or_zero(z2, n - p + 1);
        if (p <= k1 + k2) {
            int min_p1 = max(1, p - k2);
            int max_p1 = min(k1, p - 1);
            ans += max_p1 - min_p1 + 1;
        }
    }

    z1 = z_function(rs1 + '.' + rs2);
    z2 = z_function(s2);
    for (int c = m; c < n; ++c) {
        int p = c - m + 1;
        int k1 = lookup_or_zero(z1, n - p + 1);
        int k2 = lookup_or_zero(z2, p);
        if (p <= k1 + k2) {
            int min_p1 = max(1, p - k2);
            /* unlike for left ones, a1 == p is OK for right repetitions */
            int max_p1 = min(k1, p);
            ans += max_p1 - min_p1 + 1;
        }
    }

    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    string s;
    for (cin >> s; s != "0"; cin >> s) cout << dnc(s) << '\n';
    return 0;
}
