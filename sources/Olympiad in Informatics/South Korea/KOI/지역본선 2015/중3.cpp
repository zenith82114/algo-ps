/*
 * 한국정보올림피아드, 지역본선 2015, 중등부 3. 369 게임
 * BOJ 10802
 * JUNGOL 2861
 *
 * DP
 * Date: 2023.6.20
 */

#include<bits/stdc++.h>
using namespace std;

struct mint {
    static const int MOD = 20150523;
    int val;
    mint(): val(0) {}
    mint(int v): val(v) {}

    friend ostream& operator<<(ostream& os, const mint& x) {
        return os << x.val;
    }
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
    friend mint operator*(int c, const mint& x) {
        return mint((1LL * c * x.val) % MOD);
    }
};

mint dp[100004][4];
mint pow_10[100004];

mint solve(const string& a) {
    const int n = a.size();
    bool has369 = false;
    int mod3 = 0;
    mint ans(0);

    for (int i = 0; i < n; ++i) {
        int x = a[i] - '0';
        for (int j = 0; j < x; ++j) {
            if (has369 || j == 3 || j == 6 || j == 9)
                ans += pow_10[n-1 - i];
            else
                ans += dp[n-1 - i][(12 - mod3 - j)%3] + dp[n-1 - i][3];
        }
        has369 = has369 || x == 3 || x == 6 || x == 9;
        mod3 = (mod3 + x)%3;
    }
    if (has369 || !mod3) ans += 1;
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);

    dp[0][0] = 1;
    dp[0][1] = 0;
    dp[0][2] = 0;
    dp[0][3] = 0;
    pow_10[0] = 1;
    for (int i = 0; i < 100003; ++i) {
        dp[i+1][0] =   dp[i][0] + 3*dp[i][1] + 3*dp[i][2];
        dp[i+1][1] = 3*dp[i][0] +   dp[i][1] + 3*dp[i][2];
        dp[i+1][2] = 3*dp[i][0] + 3*dp[i][1] +   dp[i][2];
        dp[i+1][3] = 3*dp[i][0] + 3*dp[i][1] + 3*dp[i][2] + 10*dp[i][3];
        pow_10[i+1] = 10*pow_10[i];
    }

    string a, b; cin >> a >> b;
    mint ans = solve(b) - solve(a);

    int sum = 0;
    for (char c : a) {
        if (c == '3' || c == '6' || c == '9') {
            cout << ans + 1; return 0;
        }
        sum += c - '0';
    }
    if (sum % 3 == 0) ans += 1;
    cout << ans;
    return 0;
}
