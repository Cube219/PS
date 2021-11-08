#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;
constexpr ll MOD = 1000000007;

template <int N, int mod>
struct BiCoeff
{
    ll fact[N + 1], invfact[N + 1];

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

    // O(n)
    void init()
    {
        fact[0] = 1;
        for(int i = 1; i <= N; ++i) fact[i] = fact[i - 1] * i % mod;
        invfact[N] = pw(fact[N], mod - 2);
        for(int i = N - 1; i >= 0; --i) invfact[i] = (ll)invfact[i + 1] * (i + 1) % mod;
    }

    ll cat(int n)
    {
        ll u = fact[n * 2];
        ll d = invfact[n + 1] * invfact[n] % mod;
        return u * d % mod;
    }
};

template <int N>
struct SegTree
{
    struct Node
    {
        int mn, cnt;
    };
    Node t[N * 2 + 1];
    int n;

    void init(int _n)
    {
        n = _n;
    }
    void build()
    {
        for(int i = n - 1; i >= 1; --i) {
            t[i] = merge(t[i * 2], t[i * 2 + 1]);
        }
    }

    Node merge(Node l, Node r)
    {
        Node res;
        if(l.mn == r.mn) {
            res.mn = l.mn;
            res.cnt = l.cnt + r.cnt;
        } else if(l.mn < r.mn) res = l;
        else res = r;
        return res;
    }

    Node query(int l, int r)
    {
        l += n;
        r += n + 1;
        Node res = { 987654321, 0 };
        while(l < r) {
            if(l & 1) res = merge(res, t[l++]);
            if(r & 1) res = merge(res, t[--r]);
            l >>= 1;
            r >>= 1;
        }
        return res;
    }
};

int n, d[1000001];
ll res;
BiCoeff<2000001, MOD> bc;
vector<int> idx[1000001];
SegTree<1000001> sg;

ll p(int l, int r)
{
    auto mn = sg.query(l, r);

    ll res = bc.cat(mn.cnt);

    int st = l, ed;
    auto& cidx = idx[mn.mn];
    auto it = lower_bound(cidx.begin(), cidx.end(), l);
    while(it != cidx.end() && *it <= r) {
        ed = *it - 1;
        if(st <= ed) {
            res = (res * p(st, ed)) % MOD;
        }
        st = *it + 1;
        ++it;
    }
    ed = r;
    if(st <= ed) {
        res = (res * p(st, ed)) % MOD;
    }

    return res;
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    bc.init();

    cin >> n;
    for(int i = 0; i < n; ++i) {
        cin >> d[i];
        idx[d[i]].push_back(i);
    }

    sg.init(n);
    for(int i = 0; i < n; ++i) {
        sg.t[n + i] = { d[i], 1 };
    }
    sg.build();

    if(n == 0) {
        res = 1;
    } else {
        res = p(0, n - 1);
    }

    cout << res;

    return 0;
}
