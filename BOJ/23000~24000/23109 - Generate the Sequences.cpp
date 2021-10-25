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

using Mint = ModInt<998244353>;

template <int N, int mod>
struct BiCoeff
{
    ll fact[N + 1], invfact[N + 1];

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

    // O(n)
    void init()
    {
        fact[0] = 1;
        for(int i = 1; i <= N; ++i) fact[i] = fact[i - 1] * i % mod;
        invfact[N] = pw(fact[N], mod - 2);
        for(int i = N - 1; i >= 0; --i) invfact[i] = (ll)invfact[i + 1] * (i + 1) % mod;
    }

    // O(1), Only use when MOD is large and prime
    ll get(int n, int r)
    {
        ll factn = fact[n];
        ll invrnr = invfact[r] * invfact[n - r] % mod;
        return factn * invrnr % mod;
    }

    // O(logMOD), Only use when MOD is prime
    ll get2(int n, int r)
    {
        ll factn = fact[n];
        ll factrnr = fact[r] * fact[n - r] % mod;
        return factn * pw(factrnr, mod - 2) % mod;
    }
};

int tNum;
int n, m;
Mint dp[3001][3001];
BiCoeff<10000, 998244353> bi;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    bi.init();

    cin >> n >> m;
    dp[0][0] = 1;
    // i: 전체 시행 횟수, j: 다른 수를 넣은 횟수
    for(int i = 1; i <= n; ++i) {
        for(int j = 0; j <= i; ++j) {
            // 1번 연산
            if(j > 0) {
                dp[i][j] += dp[i - 1][j - 1];
            }

            // 2번 연산
            ll remain = (ll)(m - 2) * j - (i - 1 - j);
            if(remain > 0) {
                dp[i][j] += dp[i - 1][j] * remain;
            }
        }
    }

    Mint res = 1;
    for(int i = 1; i <= n; ++i) {
        for(int j = 0; j <= i; ++j) {
            int remain = n - i;
            res += dp[i][j] * bi.get(i + remain, remain);
        }
    }

    cout << res;

    return 0;
}
