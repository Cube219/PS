#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
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
    ModInt(ll _v = 0) : v((_v% mod + mod) % mod) {}

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
            if(k & 1) res *= p;
            p *= p;
            k >>= 1;
        }
        return res;
    }
};

using mint = ModInt<MOD>;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int tNum;
    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        int n;
        cin >> n;
        vector<int> d(n);
        for(auto& v : d) cin >> v;

        mint res = 0;
        vector<mint> mex1(n + 10, 0); // 0~x
        vector<mint> mex2(n + 10, 0); // 0~x-1, x+1
        for(int i = 0; i < n; ++i) {
            if(d[i] > 1) res += mex1[d[i] - 2];
            if(d[i] > 0) res += mex1[d[i] - 1];
            res += mex1[d[i]];

            res += mex2[d[i] + 1];
            if(d[i] > 0) res += mex2[d[i] - 1];

            if(d[i] == 0 || d[i] == 1) res += 1;



            mint tmp = 0;
            tmp += mex1[d[i]];
            if(d[i] > 0) tmp += mex1[d[i] - 1];

            mex1[d[i]] += tmp;

            if(d[i] > 0) {
                mex2[d[i] - 1] *= 2;
            }
            if(d[i] > 1) {
                mex2[d[i] - 1] += mex1[d[i] - 2];
            }
            mex2[d[i] + 1] *= 2;

            if(d[i] == 0) {
                mex1[0] += 1;
            } else if(d[i] == 1) {
                mex2[0] += 1;
            }
        }

        cout << res << "\n";
    }

    return 0;
}
