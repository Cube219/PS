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
constexpr ll MOD = 1'000'000'007;

template <int mod>
struct ModInt
{
    ll v;
    ModInt(ll _v = 0) : v((_v% mod + mod) % mod) {}
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
            if(n & 1) rev *= b;
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
    ModInt operator-() const { return ModInt() -= *this; }
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
    friend std::ostream& operator<<(std::ostream& os, const ModInt& n) { return os << n.v; }
    friend std::istream& operator>>(std::istream& is, ModInt& n)
    {
        ll x;
        is >> x;
        n = ModInt(x);
        return is;
    }
    bool operator==(const ModInt& rhs) const { return v == rhs.v; }
    bool operator!=(const ModInt& rhs) const { return v != rhs.v; }
    ModInt pow(ll k) const
    {
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

void solve()
{
    vector<mint> c(500001);
    c[0] = 1;
    for(int i = 0; i < 500000 - 1; ++i) {
        mint up = 2 * (2 * i + 1);
        mint down = i + 2;
        c[i + 1] = c[i] * up / down;
    }

    string str;
    cin >> str;

    mint res = 1;

    vector<int> st;
    st.push_back(0);
    for(char ch : str) {
        if(ch == '?') {
            st.push_back(0);
        } else if(ch == ':') {
            int cur = st.back();
            st.pop_back();
            res *= c[cur];
            st.back()++;
        }
    }
    res *= c[st.back()];

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
