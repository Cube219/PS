#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;
constexpr ll INF = 9999999999999999;

template <int N>
class SegTree
{
public:
    ll t[N * 3];
    int stLeaf, n;

    void init(int n)
    {
        stLeaf = 1;
        while(stLeaf < n) stLeaf *= 2;
    }

    ll findImpl(int cl, int cr, int l, int r, int node)
    {
        if(l <= cl && cr <= r) return t[node];
        else if(cr < l || r < cl) return 0;
        int m = (cl + cr) / 2;
        return findImpl(cl, m, l, r, node * 2) + findImpl(m + 1, cr, l, r, node * 2 + 1);
    }

    ll find(int l, int r)
    {
        return findImpl(0, stLeaf - 1, l, r, 1);
    }

    void add(int idx, ll v)
    {
        int node = stLeaf + idx;
        t[node] += v;
        node /= 2;
        while(node > 0) {
            t[node] = t[node * 2] + t[node * 2 + 1];
            node /= 2;
        }
    }
};


int n, k;
int h[100001], a[100001], b[100001];
SegTree<100001> d1, d2, u1, u2;

ll tfunc(ll x, int st)
{
    int l = st;
    int r = st + k - 1;

    ll res = 0;
    res += x * d1.find(0, x);
    res -= d2.find(0, x);
    res += u1.find(x, 100000);
    res -= x * u2.find(x, 100000);

    return res;
}

ll tsearch(ll minv, ll maxv, int st)
{
    ll l = minv, r = maxv;
    while(l + 2 < r) {
        ll p = (l * 2 + r) / 3;
        ll q = (l + r * 2) / 3;

        ll pv = tfunc(p, st);
        ll qv = tfunc(q, st);
        if(pv <= qv) r = q;
        else l = p;
    }

    ll res = tfunc(l, st);
    for(ll i = l + 1; i <= r; ++i) {
        res = min(res, tfunc(i, st));
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

    cin >> n >> k;
    for(int i = 0; i < n; ++i) {
        cin >> h[i];
    }
    for(int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    for(int i = 0; i < n; ++i) {
        cin >> b[i];
    }

    d1.init(100001);
    d2.init(100001);
    u1.init(100001);
    u2.init(100001);

    for(int i = 0; i < k; ++i) {
        d1.add(h[i], a[i]);
        d2.add(h[i], h[i] * a[i]);
        u1.add(h[i], h[i] * b[i]);
        u2.add(h[i], b[i]);
    }
    ll res = tsearch(0, 100000, 0);
    for(int i = 0; i < n - k; ++i) {
        d1.add(h[i], -a[i]);
        d2.add(h[i], -h[i] * a[i]);
        u1.add(h[i], -h[i] * b[i]);
        u2.add(h[i], -b[i]);

        d1.add(h[i + k], a[i + k]);
        d2.add(h[i + k], h[i + k] * a[i + k]);
        u1.add(h[i + k], h[i + k] * b[i + k]);
        u2.add(h[i + k], b[i + k]);

        res = min(res, tsearch(0, 100000, i + 1));
    }

    cout << res;

    return 0;
}
