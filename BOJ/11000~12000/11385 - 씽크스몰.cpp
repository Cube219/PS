#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

// https://github.com/kth-competitive-programming/kactl/blob/main/content/numerical/NumberTheoreticTransform.h
template <int MOD, int ROOT>
struct NTT
{
    ll modpow(ll a, ll b)
    {
        ll res = 1;
        ll p = a;
        while(b > 0) {
            if(b & 1) {
                res = (res * p) % MOD;
            }
            p = (p * p) % MOD;
            b >>= 1;
        }
        return res;
    }

    void ntt(vector<ll>& a)
    {
        int n = a.size(), L = 0;
        while(n > 1) {
            n >>= 1;
            L++;
        }
        n = a.size();
        static vector<ll> rt(2, 1);
        for(static int k = 2, s = 2; k < n; k *= 2, s++) {
            rt.resize(n);
            ll z[] = { 1, modpow(ROOT, MOD >> s) };
            for(int i = k; i < 2 * k; ++i) {
                rt[i] = rt[i / 2] * z[i & 1] % MOD;
            }
        }
        vector<int> rev(n);
        for(int i = 0; i < n; ++i) {
            rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
        }
        for(int i = 0; i < n; ++i) {
            if(i < rev[i]) swap(a[i], a[rev[i]]);
        }
        for(int k = 1; k < n; k *= 2) {
            for(int i = 0; i < n; i += 2 * k) {
                for(int j = 0; j < k; ++j) {
                    ll z = rt[j + k] * a[i + j + k] % MOD, &ai = a[i + j];
                    a[i + j + k] = ai - z + (z > ai ? MOD : 0);
                    ai += (ai + z >= MOD ? z - MOD : z);
                }
            }
        }
    }

    vector<ll> conv(const vector<ll>& a, const vector<ll>& b)
    {
        if(a.empty() || b.empty()) return {};
        int s = a.size() + b.size() - 1;
        int B = 0, n = 1;
        while(n <= s) {
            n <<= 1;
            B++;
        }
        ll inv = modpow(n, MOD - 2);
        vector<ll> L(a), R(b), out(n);
        L.resize(n), R.resize(n);
        ntt(L), ntt(R);
        for(int i = 0; i < n; ++i) {
            out[-i & (n - 1)] = (ll)L[i] * R[i] % MOD * inv % MOD;
        }
        ntt(out);
        return { out.begin(), out.begin() + s };
    }
};

// NTT<998244353, 62> ntt;
// NTT<998244353, 3> ntt;
// NTT<167772161, 3> ntt;
// For p < 2^30 there is also e.g. 5 << 25, 7 << 26, 479 << 21
// and 483 << 21 (same root). The last two are > 10^9.

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
        ll resv = (en.s * c) % c2.m / en.g * c1.m + c1.v;
        resv %= resm;
        if(resv < 0) resv += resm;
        return { resv, resm };
    }
};

int n, m;
vector<ll> a, b;
NTT<998244353, 3> ntt1;
NTT<1004535809, 62> ntt2;
CRT crt;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;
    n++; m++;
    a.resize(n); b.resize(m);
    for(int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    for(int i = 0; i < m; ++i) {
        cin >> b[i];
    }

    auto res1 = ntt1.conv(a, b);
    auto res2 = ntt2.conv(a, b);

    ll res = 0;
    for(int i = 0; i < res1.size(); ++i) {
        CRT::Con c1 = { res1[i], 998244353 };
        CRT::Con c2 = { res2[i], 1004535809 };
        auto c3 = crt.get(c1, c2);
        res ^= c3.v;
    }

    cout << res;

    return 0;
}
