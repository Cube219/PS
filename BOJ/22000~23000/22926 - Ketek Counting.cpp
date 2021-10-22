#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
#include <string>
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

string s1, s2;
int n;
mint res;
mint dp[30011], p[30011];
int idx[30011];

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> s1;
    n = s1.size();
    {
        int l = 0, r = n - 1;
        s2.resize(n);
        for(int i = 0; i < n; ++i) {
            if((i & 1) == 0) {
                s2[i] = s1[l];
                idx[l] = i;
                l++;
            } else {
                s2[i] = s1[r];
                idx[r] = i;
                r--;
            }
        }
    }
    for(int i = 0; i < n - 1; ++i) {
        if(i % 2 == 0) p[i] = 1;
        else {
            if(s2[i] == s2[i + 1]) {
                if(s2[i] == '?') p[i] = 26;
                else p[i] = 1;
            } else {
                if(s2[i] == '?' || s2[i + 1] == '?') p[i] = 1;
                else p[i] = 0;
            }
        }
    }

    mint allnum = 1;
    dp[0] = 1;
    if(n & 1) {
        if(s1[n / 2] == '?') dp[1] = 26;
        else dp[1] = 1;
        allnum = dp[1];
    }

    for(int l = n / 2 - 1; l >= 0; --l) {
        int r = n - l - 1;
        int sz = r - l + 1;
        if(s1[l] == '?') allnum *= 26;
        if(s1[r] == '?') allnum *= 26;

        int s2l = idx[l];
        char lch = s2[s2l];

        for(int i = 1; sz - i * 2 >= 0; ++i) {
            int s2r = s2l + i * 2 - 1;
            char rch = s2[s2r];

            mint v;
            if(lch == rch) {
                if(lch == '?') v = 26;
                else v = 1;
            } else {
                if(lch == '?' || rch == '?') v = 1;
                else v = 0;
            }

            mint pal = p[idx[l] + i - 1] * v;
            p[idx[l] + i - 1] = pal;
            dp[sz] += dp[sz - i * 2] * pal;

            if(s2l > 0 && s2r < n - 1) {
                char lch2 = s2[s2l - 1];
                char rch2 = s2[s2r + 1];
                if(lch2 == rch2) {
                    if(lch2 == '?') v = 26;
                    else v = 1;
                } else {
                    if(lch2 == '?' || rch2 == '?') v = 1;
                    else v = 0;
                }
                p[idx[l] + i - 1] *= v;
            }
        }
        dp[sz] += allnum;
    }

    cout << dp[n];

    return 0;
}
