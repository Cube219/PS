#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <numeric>
#include <vector>
#include <cmath>
using namespace std;

using ll = long long int;
constexpr int INF = 0x3f3f3f3f;
constexpr ll LNF = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 1'000'000'007;

namespace geo
{
    template <typename T>
    struct PointBase
    {
        using P = PointBase;

        T x, y;
        int color;
        PointBase(T _x = 0, T _y = 0) : x(_x), y(_y) {}

        P operator+(P p) const { return { x + p.x, y + p.y }; }
        P operator-(P p) const { return { x - p.x, y - p.y }; }
        P operator*(T d) const { return { x * d, y * d }; }
        P operator/(T d) const { return { x / d, y / d }; }

        bool operator<(const P& rhs) const { return tie(x, y) < tie(rhs.x, rhs.y); }
        bool operator==(const P& rhs) const { return tie(x, y) == tie(rhs.x, rhs.y); }

        T dis2() const { return x * x + y * y; }
        double dis() const { return sqrt((double)dis2()); }
        T dot(P p) const { return x * p.x + y * p.y; }
        T cross(P p) const { return x * p.y - y * p.x; }
        P perp() const { return { -y, x }; } // +90 deg
    };

    template <typename P>
    auto dot(P a, P b) { return a.x * b.x + a.y + b.y; }

    template <typename P>
    auto cross(P a, P b) { return a.x * b.y - a.y * b.x; }

    using Point = PointBase<ll>;

    template <typename P>
    vector<P> convexHull(vector<P>& poly, bool erase = false)
    {
        // line 위 포함 => cross 등호 빼고, 일자인 경우 예외처리
        if(poly.size() <= 1) {
            auto newPoly = poly;
            if(erase) poly.clear();
            return newPoly;
        }

        vector<int> eraseIdx;

        sort(poly.begin(), poly.end());
        vector<P> up;
        for(int i = 0; i < poly.size(); ++i) {
            int sz = up.size();
            auto& p = poly[i];
            while(sz >= 2 && cross(up[sz - 1] - up[sz - 2], p - up[sz - 2]) <= 0) {
                up.pop_back();
                eraseIdx.pop_back();
                sz--;
            }
            up.push_back(p);
            eraseIdx.push_back(i);
        }

        vector<P> lo;
        for(int i = poly.size() - 1; i >= 0; --i) {
            int sz = lo.size();
            auto& p = poly[i];
            while(sz >= 2 && cross(lo[sz - 1] - lo[sz - 2], p - lo[sz - 2]) <= 0) {
                lo.pop_back();
                eraseIdx.pop_back();
                sz--;
            }
            lo.push_back(p);
            eraseIdx.push_back(i);
        }

        if(erase) {
            sort(eraseIdx.begin(), eraseIdx.end());
            eraseIdx.push_back(poly.size());
            vector<P> newPoly;
            int ei = 0;
            for(int i = 0; i < poly.size(); ++i) {
                while(eraseIdx[ei] < i) ei++;
                if(eraseIdx[ei] == i) ei++;
                else newPoly.push_back(poly[i]);
            }

            poly = newPoly;
        }

        up.insert(up.end(), lo.begin() + 1, lo.end() - 1);
        return up;
    }
}

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

void solve()
{
    int n;
    cin >> n;
    vector<geo::Point> d(n);
    bool allRed = true, allBlue = true;
    for(auto& v : d) {
        cin >> v.x >> v.y >> v.color;
        if(v.color == 1) allBlue = false;
        if(v.color == 2) allRed = false;
    }

    auto cvx = geo::convexHull(d, true);
    mint inNum = 1;
    for(auto [x, y, c] : d) {
        if(c == 0) inNum *= 2;
    }

    // 00 / 11 / 0011 / 1100 / 001100 / 110011
    vector<mint> dp(6, 0), ndp(6, 0);
    if(cvx[0].color != 2) {
        dp[0] = 1;
    }
    if(cvx[0].color != 1) {
        dp[1] = 1;
    }
    for(int i = 1; i < cvx.size(); ++i) {
        for(int j = 0; j < 6; ++j) ndp[j] = 0;
        int c = cvx[i].color;
        if(c != 2) {
            // use 0
            ndp[0] += dp[0];
            ndp[3] += dp[3] + dp[1];
            ndp[4] += dp[4] + dp[2];
        }
        if(c != 1) {
            // use 1
            ndp[1] += dp[1];
            ndp[2] += dp[2] + dp[0];
            ndp[5] += dp[5] + dp[3];
        }

        swap(dp, ndp);
    }

    mint res = (dp[0] + dp[1] + dp[2] + dp[3] + dp[4] + dp[5]) * inNum;
    if(allRed) res -= 1;
    if(allBlue) res -= 1;

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
