#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <assert.h>
#include <vector>
using namespace std;

using ll = long long int;

template <int mod>
struct BiCoeff_Lucas
{
    ll fact[mod], invfact[mod];

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

    // O(mod)
    void init()
    {
        int N = mod - 1;
        fact[0] = 1;
        for(int i = 1; i <= N; ++i) fact[i] = fact[i - 1] * i % mod;
        invfact[N] = pw(fact[N], mod - 2);
        for(int i = N - 1; i >= 0; --i) invfact[i] = (ll)invfact[i + 1] * (i + 1) % mod;
    }

    ll ncr(int n, int r)
    {
        if(n < r) return 0;
        ll factn = fact[n];
        ll invrnr = invfact[r] * invfact[n - r] % mod;
        return factn * invrnr % mod;
    }

    // O(logn + logr), Only use when MOD is prime
    ll get(ll n, ll r)
    {
        ll res = 1;
        while(n > 0 || r > 0) {
            ll a = n % mod;
            ll b = r % mod;
            res *= ncr(a, b);
            res %= mod;

            n /= mod;
            r /= mod;
        }
        return res;
    }
};

struct ENode
{
    ll s;
    ll t;
    ll g;
};

ENode eeuc(ll a, ll b)
{
    if(b == 0) return { 1, 0, a };

    ll r = a % b;
    auto res = eeuc(b, r);
    ll x = res.t;
    ll y = res.s - a / b * res.t;
    return { x, y, res.g };
}

// Ax+By=C, D=gcd(A, B)=g
// x0 = s * C/D       y0 = t * C/D
// s = x0 + k * B/D   t = y0 - k * A/D

struct CRT
{
    // x = v (mod m)
    struct Con
    {
        ll v, m;
    };

    Con get(Con c1, Con c2)
    {
        if(c1.m < c2.m) swap(c1, c2);
        ENode en = eeuc(c1.m, c2.m);
        if((c1.v - c2.v) % en.g != 0) return { -1, -1 };

        ll c = (c2.v - c1.v) % c2.m;
        if(c < 0) c += c2.m;

        ll resm = c1.m * c2.m / en.g;
        ll resv = en.s * c / en.g * c1.m + c1.v;
        resv %= resm;
        if(resv < 0) resv += resm;
        return { resv, resm };
    }
};

// idea: https://rkm0959.tistory.com/182
template <int p, int e>
struct BiCo_PrimePower
{
    vector<ll> val;
    ll pe;

    // O(p^e)
    void init()
    {
        pe = 1;
        for(int i = 0; i < e; i++) pe *= p;

        val.resize(pe);
        val[0] = 1;
        val[1] = 1;
        for(int i = 2; i < pe; ++i) {
            val[i] = val[i - 1];
            if(i % p == 0) continue;
            val[i] *= i;
            val[i] %= pe;
        }
    }

    // n! = p^k * r  ->  { k, r (mod p^e)  }
    pair<int, ll> getnfact(ll n)
    {
        if(n < p) {
            ll res = 1;
            for(int i = 2; i <= n; ++i) {
                res *= i;
                res %= pe;
            }
            return { 0, res };
        }

        pair<ll, ll> res;

        ll div = n / p;
        res.first = div;

        auto r = getnfact(div);

        ll div2 = n / pe;
        ll remain2 = n % pe;

        res.second = val[remain2];

        if(div2 % 2 == 1) {
            res.second = (res.second * val[pe - 1]) % pe;
        }

        res.first += r.first;
        res.second = (res.second * r.second) % pe;
        return res;
    }

    ll invmod(ll a)
    {
        ENode res = eeuc(a, pe);
        ll r = res.s % pe;
        if(r < 0) r += pe;
        return r;
    }

    // O(nlogn)
    ll get(ll n, ll r)
    {
        auto nres = getnfact(n);
        auto rres = getnfact(r);
        auto nrres = getnfact(n - r);

        int pnum = nres.first - rres.first - nrres.first;
        ll remain = (nres.second * invmod((rres.second * nrres.second) % pe)) % pe;
        if(pnum >= e) {
            return 0;
        }
        for(int i = 0; i < pnum; ++i) {
            remain *= p;
            remain %= pe;
        }
        return remain;
    }
};

int tNum;
CRT crt;
BiCoeff_Lucas<11> bi1;
BiCoeff_Lucas<13> bi2;
BiCoeff_Lucas<37> bi3;
BiCo_PrimePower<3, 3> bi4;
ll n, k;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    bi1.init();
    bi2.init();
    bi3.init();
    bi4.init();

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        cin >> n >> k;

        ll r1 = bi1.get(n, k);
        ll r2 = bi2.get(n, k);
        ll r3 = bi3.get(n, k);
        ll r4 = bi4.get(n, k);

        CRT::Con c1 = { r1, 11 };
        CRT::Con c2 = { r2, 13 };
        CRT::Con c3 = { r3, 37 };
        CRT::Con c4 = { r4, 27 };

        auto res1 = crt.get(c1, c2);
        auto res2 = crt.get(c3, c4);
        auto res3 = crt.get(res1, res2);

        cout << res3.v << "\n";
    }

    return 0;
}
