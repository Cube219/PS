#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <algorithm>
#include <cstdio>
#include <iostream>
#include <numeric>
#include <utility>
#include <vector>
using namespace std;

using ll = long long int;
constexpr int INF = 0x3f3f3f3f;
constexpr ll LNF = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 998244353;

template <int mod>
struct ModInt
{
    ll v;
    ModInt(ll _v = 0)
        : v((_v % mod + mod) % mod)
    {
    }
    ModInt &operator+=(const ModInt &rhs)
    {
        v += rhs.v;
        if (v >= mod)
            v -= mod;
        return *this;
    }
    ModInt &operator-=(const ModInt &rhs)
    {
        v -= rhs.v;
        if (v < 0)
            v += mod;
        return *this;
    }
    ModInt &operator*=(const ModInt &rhs)
    {
        v *= rhs.v;
        v %= mod;
        return *this;
    }
    ModInt &operator/=(const ModInt &rhs)
    {
        ll n = mod - 2;
        ModInt rev = 1, b = rhs;
        while (n > 0)
        {
            if (n & 1)
                rev *= b;
            b *= b;
            n >>= 1;
        }
        return *this *= rev;
    }
    ModInt operator+(const ModInt &rhs) const
    {
        ModInt lhs(*this);
        return lhs += rhs;
    }
    ModInt operator-() const
    {
        return ModInt() -= *this;
    }
    ModInt operator-(const ModInt &rhs) const
    {
        ModInt lhs(*this);
        return lhs -= rhs;
    }
    ModInt operator*(const ModInt &rhs) const
    {
        ModInt lhs(*this);
        return lhs *= rhs;
    }
    ModInt operator/(const ModInt &rhs) const
    {
        ModInt lhs(*this);
        return lhs /= rhs;
    }
    friend std::ostream &operator<<(std::ostream &os, const ModInt &n)
    {
        return os << n.v;
    }
    friend std::istream &operator>>(std::istream &is, ModInt &n)
    {
        ll x;
        is >> x;
        n = ModInt(x);
        return is;
    }
    bool operator==(const ModInt &rhs) const
    {
        return v == rhs.v;
    }
    bool operator!=(const ModInt &rhs) const
    {
        return v != rhs.v;
    }
    ModInt pow(ll k) const
    {
        ModInt res = 1, p = v;
        while (k > 0)
        {
            if (k & 1)
                res *= p;
            p *= p;
            k >>= 1;
        }
        return res;
    }
};
using mint = ModInt<MOD>;

void solve()
{
    int n;
    cin >> n;
    vector<mint> a(n);
    for (auto &v : a)
        cin >> v;

    vector<mint> l(n), r(n);
    l[0] = 1;
    r[n - 1] = 1;
    mint sum = a[0];
    for (int i = 1; i < n; ++i)
    {
        sum += a[i];
        mint p = a[i] / sum;
        l[i] = p * l[i - 1];
    }
    sum = a[n - 1];
    for (int i = n - 2; i >= 0; --i)
    {
        sum += a[i];
        mint p = a[i] / sum;
        r[i] = p * r[i + 1];
    }

    mint res = 0;
    for (int i = 0; i < n; ++i)
    {
        mint lp = i > 0 ? l[i - 1] : 1;
        mint rp = i + 1 < n ? r[i + 1] : 1;
        res += a[i] / sum * lp * rp;
    }

    cout << mint(1) - res;
}

int main()
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int tNum = 1;
    // cin >> tNum;
    for (int tt = 1; tt <= tNum; tt++)
    {
        solve();
    }

    return 0;
}
