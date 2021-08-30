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

using mint = ModInt<998244353>;

struct Node
{
    int a, b;
};

int n;
Node d[5001];
mint dp[5001];
mint res;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for(int i = 0; i < n; ++i) {
        cin >> d[i].a;
    }
    for(int i = 0; i < n; ++i) {
        cin >> d[i].b;
    }
    sort(d, d + n, [](const Node& l, const Node& r) {
        return l.a < r.a;
    });

    dp[0] = 1;
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j <= d[i].a - d[i].b; ++j) {
            res += dp[j];
        }
        for(int j = 5000 - d[i].b; j >= 0; --j) {
            dp[j + d[i].b] += dp[j];
        }
    }

    cout << res;

    return 0;
}
