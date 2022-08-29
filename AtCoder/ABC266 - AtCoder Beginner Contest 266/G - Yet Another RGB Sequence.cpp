#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <numeric>
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
    ModInt(ll _v = 0) : v((_v % mod + mod) % mod) {}
    ModInt& operator+=(const ModInt& rhs) {
        v += rhs.v;
        if(v >= mod) v -= mod;
        return *this;
    }
    ModInt& operator-=(const ModInt& rhs) {
        v -= rhs.v;
        if(v < 0) v += mod;
        return *this;
    }
    ModInt& operator*=(const ModInt& rhs) {
        v *= rhs.v;
        v %= mod;
        return *this;
    }
    ModInt& operator/=(const ModInt& rhs) {
        ll n = mod - 2;
        ModInt rev = 1, b = rhs;
        while(n > 0) {
            if(n & 1) rev *= b;
            b *= b;
            n >>= 1;
        }
        return *this *= rev;
    }
    ModInt operator+(const ModInt& rhs) const {
        ModInt lhs(*this);
        return lhs += rhs;
    }
    ModInt operator-() const { return ModInt() -= *this; }
    ModInt operator-(const ModInt& rhs) const {
        ModInt lhs(*this);
        return lhs -= rhs;
    }
    ModInt operator*(const ModInt& rhs) const {
        ModInt lhs(*this);
        return lhs *= rhs;
    }
    ModInt operator/(const ModInt& rhs) const {
        ModInt lhs(*this);
        return lhs /= rhs;
    }
    friend std::ostream& operator<<(std::ostream& os, const ModInt& n) { return os << n.v; }
    friend std::istream& operator>>(std::istream& is, ModInt& n) {
        ll x;
        is >> x;
        n = ModInt(x);
        return is;
    }
    bool operator==(const ModInt& rhs) const { return v == rhs.v; }
    bool operator!=(const ModInt& rhs) const { return v != rhs.v; }
    ModInt pow(ll k) const {
        ModInt res = 1, p = v;
        while(k > 0) {
            if(k & 1) res *= p;
            p *= p;
            k >>= 1;
        }
        return res;
    }
};
using mint = ModInt<MOD>;

template <int mod>
struct BiCoeff
{
    vector<ll> fact, invfact;

    ll pw(ll a, ll b)
    {
        ll res = 1;
        while(b > 0) {
            if(b & 1) {
                res = res * a % mod;
            }
            a = a * a % mod;
            b >>= 1;
        }
        return res;
    }

    void init(int n)
    {
        fact.resize(n + 1);
        invfact.resize(n + 1);

        fact[0] = 1;
        for(int i = 1; i <= n; ++i) fact[i] = fact[i - 1] * i % mod;
        invfact[n] = pw(fact[n], mod - 2);
        for(int i = n - 1; i >= 0; --i) invfact[i] = invfact[i + 1] * (i + 1) % mod;
    }

    ll get(int n, int r)
    {
        if(n < 0 || r < 0) return 0;
        return fact[n] * (invfact[r] * invfact[n - r] % mod) % mod;
        // return fact[n] * pw(fact[r] * fact[n - r] % mod, mod - 2) % mod;
    }
};

void solve()
{
    int r, g, b, k;
    cin >> r >> g >> b >> k;

    BiCoeff<MOD> bi;
    bi.init(6000000);

    mint res = bi.get(b + r, r);
    res *= bi.get(r, k);
    int cnt = r + b - (r- k);
    res *= bi.get(cnt + (g-k), g-k);

    cout << res;
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
    for(int tt = 1; tt <= tNum; tt++) {
        solve();
    }

    return 0;
}
