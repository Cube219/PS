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
constexpr ll MOD = 1'000'000'007;

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

// x = v (mod m)
struct Con
{
    ll v, m;
};

Con crt(Con c1, Con c2)
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

void solve()
{
    int n, m;
    cin >> n >> m;
    vector<int> deg(n, 0);
    map<pair<int, int>, int> mp;
    for(int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        if(u > v) swap(u, v);
        deg[u]++;
        if(u != v) {
            deg[v]++;
            mp[{ u, v }]++;
        }
    }

    vector<ll> degCnt(m + 1, 0);
    for(int v : deg) degCnt[v]++;

    NTT<998244353, 3> ntt;
    NTT<167772161, 3> ntt2;
    auto res = ntt.conv(degCnt, degCnt);
    auto res2 = ntt2.conv(degCnt, degCnt);
    for(int i = 0; i < res.size(); ++i) {
        Con resCon = { res[i], 998244353 };
        Con res2Con = { res2[i], 167772161 };
        res[i] = crt(resCon, res2Con).v;

        if(i & 1) {
            res[i] /= 2;
        } else {
            ll v = degCnt[i / 2];
            res[i] -= v * v;
            res[i] /= 2;
            res[i] += v * (v - 1) / 2;
        }
    }
    for(auto& it : mp) {
        auto [u, v] = it.first;
        auto cnt = it.second;

        res[deg[u] + deg[v]]--;
        res[deg[u] + deg[v] - cnt]++;
    }
    for(int i = (int)res.size() - 2; i >= 0; --i) {
        res[i] += res[i + 1];
    }

    int q;
    cin >> q;
    for(int i = 0; i < q; ++i) {
        int v;
        cin >> v;
        if(v + 1 >= res.size()) cout << "0\n";
        else cout << res[v + 1] << "\n";
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
