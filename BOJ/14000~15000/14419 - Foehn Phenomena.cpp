#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

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

    void initv(int idx, ll v)
    {
        t[stLeaf + idx] = v;
    }

    void build()
    {
        for(int i = stLeaf - 1; i > 0; --i) {
            t[i] = t[i * 2] + t[i * 2 + 1];
        }
    }

    ll findImpl(int cl, int cr, int l, int r, int node)
    {
        if(cr < l || r < cl) return 0;
        if(l <= cl && cr <= r) return t[node];
        int m = (cl + cr) / 2;
        return findImpl(cl, m, l, r, node * 2) + findImpl(m + 1, cr, l, r, node * 2 + 1);
    }

    ll find(int l, int r)
    {
        return findImpl(0, stLeaf - 1, l, r, 1);
    }

    void update(int idx, ll v)
    {
        int node = stLeaf + idx;
        t[node] = v;
        node /= 2;
        while(node > 0) {
            t[node] = t[node * 2] + t[node * 2 + 1];
            node /= 2;
        }
    }
};


int n, q, s, t;
ll a[200001], da[200001];
SegTree<200001> pos, neg;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> q >> s >> t;
    n++;
    pos.init(n);
    neg.init(n);
    for(int i = 0; i < n; ++i) {
        cin >> a[i];
        if(i > 0) {
            ll v = a[i] - a[i - 1];
            if(v >= 0) pos.initv(i, v);
            else neg.initv(i, -v);

            da[i] = a[i] - a[i - 1];
        }
    }
    pos.build();
    neg.build();

    for(int i = 0; i < q; ++i) {
        ll l, r, x;
        cin >> l >> r >> x;
        if(l > 0) {
            if(da[l] >= 0) pos.update(l, 0);
            else neg.update(l, 0);

            da[l] += x;
            if(da[l] >= 0) pos.update(l, da[l]);
            else neg.update(l, -da[l]);
        }
        if(r < n - 1) {
            if(da[r + 1] >= 0) pos.update(r + 1, 0);
            else neg.update(r + 1, 0);

            da[r + 1] -= x;
            if(da[r + 1] >= 0) pos.update(r + 1, da[r + 1]);
            else neg.update(r + 1, -da[r + 1]);
        }

        ll posv = pos.find(0, n - 1);
        ll negv = neg.find(0, n - 1);

        ll res = posv * s - negv * t;
        cout << -res << "\n";
    }

    return 0;
}
