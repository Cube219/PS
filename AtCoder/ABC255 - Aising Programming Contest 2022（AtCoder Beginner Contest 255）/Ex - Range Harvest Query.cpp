#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <map>
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

struct SegmentList
{
    using Type = ll;

    struct Segment
    {
        ll l, r;
        Type v;
    };

    map<ll, Segment> list;

    SegmentList(ll st, ll ed)
    {
        list.insert({ st, {st, ed, 0} });
    }

    mint query(ll l, ll r, ll v)
    {
        auto stIt = prev(list.upper_bound(l));
        if(stIt->second.l < l) {
            Segment seg = stIt->second;
            list.erase(stIt);

            Segment lSeg = seg;
            lSeg.r = l - 1;
            list.insert({ lSeg.l, lSeg });
            Segment rSeg = seg;
            rSeg.l = l;
            list.insert({ rSeg.l, rSeg }).first;
        }
        auto edIt = prev(list.upper_bound(r));
        if(r < edIt->second.r) {
            Segment seg = edIt->second;
            list.erase(edIt);

            Segment lSeg = seg;
            lSeg.r = r;
            list.insert({ lSeg.l, lSeg }).first;
            Segment rSeg = seg;
            rSeg.l = r + 1;
            list.insert({ rSeg.l, rSeg });
        }
        stIt = list.lower_bound(l);
        edIt = list.upper_bound(r);

        mint res = 0;
        for(auto it = stIt; it != edIt;) {
            // Do something
            Segment seg = it->second;
            ll dt = v - seg.v;

            mint suml = seg.l - 1;
            suml = suml * (suml + 1) / 2;
            mint sumr = seg.r;
            sumr = sumr * (sumr + 1) / 2;
            res += (sumr - suml) * dt;

            it = list.erase(it);
        }

        Segment seg;
        seg.l = l; seg.r = r;
        seg.v = v; // Insert new value
        list.insert({ seg.l, seg });

        return res;
    }
};

void solve()
{
    ll n, q;
    cin >> n >> q;
    SegmentList list(1, n);

    for(int i = 0; i < q; ++i) {
        ll t, l, r;
        cin >> t >> l >> r;

        cout << list.query(l, r, t) << "\n";
    }
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
