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
constexpr ll MOD = 1'000'000'007;

template <int mod>
struct ModInt
{
    ll v;
    ModInt(ll _v = 0) : v((_v % mod + mod) % mod) {}
    ModInt(const string& str) {
        v = 0;
        for(char ch : str) {
            v = v * 10 + (ch - '0');
            v %= mod;
        }
    }
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

void solve()
{
    string str;
    cin >> str;
    int n = str.size();

    vector<vector<mint>> dp(n, vector<mint>(n, 0));

    for(int r = 0; r < n; ++r) {
        for(int l = r - 1; l >= 0; --l) {
            if(str[r] == str[l]) continue;

            mint in = 0;
            if(l + 1 == r) in = 1;
            else in = dp[l + 1][r - 1];

            for(int l2 = l; l2 >= 0; --l2) {
                mint out = 0;
                if(l2 == l) out = 1;
                else out = dp[l2][l - 1];
                dp[l2][r] += in * out;
            }
        }
    }

    cout << dp[0][n - 1];
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
