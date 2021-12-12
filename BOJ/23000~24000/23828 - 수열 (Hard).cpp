#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

template <int mod>
struct ModInt
{
    ll v;
    ModInt(ll _v = 0) : v((_v % mod + mod) % mod) {}

    ModInt(const string& str)
    {
        ll cur = 0;
        for(char ch : str) {
            cur *= 10;
            cur += ch - '-';
            cur %= mod;
        }
        v = cur;
    }

    ModInt& operator+=(const ModInt& rhs)
    {
        v += rhs.v;
        if(v >= mod) v -= mod;
        return *this;
    }

    ModInt& operator-=(const ModInt& rhs)
    {
        v -= rhs.v;
        if(v < 0) v += mod;
        return *this;
    }

    ModInt& operator*=(const ModInt& rhs)
    {
        v *= rhs.v;
        v %= mod;
        return *this;
    }

    ModInt& operator/=(const ModInt& rhs)
    {
        ll n = mod - 2;
        ModInt rev = 1, b = rhs;
        while(n > 0) {
            if(n & 1) {
                rev *= b;
            }
            b *= b;
            n >>= 1;
        }
        return *this *= rev;
    }

    ModInt operator+(const ModInt& rhs) const
    {
        ModInt lhs(*this);
        return lhs += rhs;
    }

    ModInt operator-() const
    {
        return ModInt() -= *this;
    }

    ModInt operator-(const ModInt& rhs) const
    {
        ModInt lhs(*this);
        return lhs -= rhs;
    }

    ModInt operator*(const ModInt& rhs) const
    {
        ModInt lhs(*this);
        return lhs *= rhs;
    }

    ModInt operator/(const ModInt& rhs) const
    {
        ModInt lhs(*this);
        return lhs /= rhs;
    }

    friend std::ostream& operator<<(std::ostream& os, const ModInt& n)
    {
        return os << n.v;
    }

    friend std::istream& operator>>(std::istream& is, ModInt& n)
    {
        ll x;
        is >> x;
        n = ModInt(x);
        return is;
    }

    bool operator==(const ModInt& rhs) const
    {
        return v == rhs.v;
    }

    bool operator!=(const ModInt& rhs) const
    {
        return v != rhs.v;
    }

    ModInt pow(ll k) const
    {
        ModInt res = 1;
        ModInt p = v;
        while(k > 0) {
            if(k & 1) {
                res *= p;
            }
            p *= p;
            k >>= 1;
        }
        return res;
    }
};

using mint = ModInt<1000000007>;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;
    vector<int> dd(n);
    for(auto& v : dd) cin >> v;

    sort(dd.begin(), dd.end());
    vector<pair<int, int>> d;
    for(int i = 0; i < n; ++i) {
        if(d.size() == 0 || d.back().first != dd[i]) d.push_back({ dd[i], 0 });
        d.back().second++;
    }

    n = d.size();

    vector<vector<mint>> dp(m, vector<mint>(n, 0));
    for(int i = 0; i < n; ++i) {
        dp[0][i] = d[i].first * d[i].second;
        if(i > 0) dp[0][i] += dp[0][i - 1];
    }
    for(int i = 1; i < m; ++i) {
        for(int j = 0; j < n; ++j) {
            mint v = 0;
            if(j > 0) {
                v = dp[i - 1][j - 1];
            }
            dp[i][j] = v * d[j].first * d[j].second;
            if(j > 0) dp[i][j] += dp[i][j - 1];
        }
    }

    cout << dp[m - 1][n - 1];

    return 0;
}
