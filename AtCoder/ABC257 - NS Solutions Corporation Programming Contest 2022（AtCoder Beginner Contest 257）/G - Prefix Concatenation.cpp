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

template <ll h1 = 3137, ll m1 = 998244353, ll h2 = 53, ll m2 = 1610612741>
struct HashStr
{
    vector<ll> hv, hpow;
    vector<ll> hv2, hpow2;

    HashStr(const string& str)
    {
        int n = str.size();
        hv.resize(n);
        hpow.resize(n);

        hv[0] = str[0];
        hpow[0] = 1;
        for(int i = 1; i < n; ++i) {
            hv[i] = (hv[i - 1] * h1 + str[i]) % m1;
            hpow[i] = (hpow[i - 1] * h1) % m1;
        }

        hv2.resize(n);
        hpow2.resize(n);

        hv2[0] = str[0];
        hpow2[0] = 1;
        for(int i = 1; i < n; ++i) {
            hv2[i] = (hv2[i - 1] * h2 + str[i]) % m2;
            hpow2[i] = (hpow2[i - 1] * h2) % m2;
        }
    }

    // [l, r]
    ll substr(int l, int r)
    {
        ll res = hv[r];
        if(l > 0) {
            res -= hv[l - 1] * hpow[r - l + 1];
            res = ((res % m1) + m1) % m1;
        }
        ll res2 = hv2[r];
        if(l > 0) {
            res2 -= hv2[l - 1] * hpow2[r - l + 1];
            res2 = ((res2 % m2) + m2) % m2;
        }
        return res << 32 | res2;
    }
};

struct SegTree
{
    using Type = int;

    Type merge(Type l, Type r)
    {
        return min(l, r);
    }

    const Type emptyNode = INF;

    int n;
    vector<Type> t;

    SegTree(int _n)
    {
        n = _n;
        t.resize(n * 2, emptyNode);
    }

    void initv(int idx, Type v)
    {
        t[n + idx] = v;
    }

    void build()
    {
        for(int i = n - 1; i > 0; --i) {
            t[i] = merge(t[i << 1], t[i << 1 | 1]);
        }
    }

    void update(int idx, Type v)
    {
        idx += n;
        t[idx] = v;
        idx >>= 1;
        while(idx > 0) {
            t[idx] = merge(t[idx << 1], t[idx << 1 | 1]);
            idx >>= 1;
        }
    }

    Type query(int l, int r)
    {
        l += n;
        r += n + 1;
        Type resl = emptyNode;
        Type resr = emptyNode;
        while(l < r) {
            if(l & 1) resl = merge(resl, t[l++]);
            if(r & 1) resr = merge(t[--r], resr);
            l >>= 1;
            r >>= 1;
        }
        return merge(resl, resr);
    }
};

void solve()
{
    string s, t;
    cin >> s >> t;
    int n = t.size();

    SegTree sg(n + 1);
    sg.initv(n, 0);
    sg.build();

    HashStr sHs(s), tHs(t);
    for(int i = n - 1; i >= 0; --i) {
        int sufSz = n - i;

        int lo = 0, hi = min((int)s.size() + 1, sufSz + 1);
        while(lo + 1 < hi) {
            int mid = (lo + hi) / 2;
            ll ss = sHs.substr(0, mid - 1);
            ll tt = tHs.substr(i, i + mid - 1);
            if(ss == tt) {
                lo = mid;
            } else {
                hi = mid;
            }
        }

        int v = sg.query(i + 1, i + lo) + 1;
        sg.update(i, v);
    }

    int v = sg.query(0, 0);
    if(v == INF) v = -1;
    cout << v;
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
