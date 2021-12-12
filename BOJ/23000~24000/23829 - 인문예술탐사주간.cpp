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
struct SegTree
{
    int n;
    ll t[N * 2 + 1];

    void init(int _n)
    {
        n = _n;
        // Add init values in [n, n+n)
    }

    void build()
    {
        for(int i = n - 1; i > 0; --i) {
            t[i] = merge(t[i << 1], t[i << 1 | 1]);
        }
    }

    void update(int idx, ll v)
    {
        idx += n;
        t[idx] = v;
        idx >>= 1;
        while(idx > 0) {
            t[idx] = merge(t[idx << 1], t[idx << 1 | 1]);
            idx >>= 1;
        }
    }

    ll find(int l, int r)
    {
        l += n;
        r += n + 1;
        ll resl = 0;
        ll resr = 0;
        while(l < r) {
            if(l & 1) resl = merge(resl, t[l++]);
            if(r & 1) resr = merge(t[--r], resr);
            l >>= 1;
            r >>= 1;
        }
        return merge(resl, resr);
    }

    ll merge(ll l, ll r)
    {
        return l + r;
    }
};

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;
    cin >> n >> q;
    vector<int> d(n);
    for(auto& v : d) cin >> v;
    sort(d.begin(), d.end());

    SegTree<100001> sg;
    sg.init(n);
    for(int i = 0; i < n; ++i) {
        sg.t[n + i] = d[i];
    }
    sg.build();

    for(int i = 0; i < q; ++i) {
        int pos;
        cin >> pos;
        int idx = upper_bound(d.begin(), d.end(), pos) - d.begin();
        ll lsum = 0;
        if(idx > 0) lsum = sg.find(0, idx - 1);
        ll rsum = 0;
        if(idx < n) rsum = sg.find(idx, n - 1);

        int lcnt = idx;
        int rcnt = n - lcnt;

        cout << (ll)pos * lcnt - lsum + rsum - (ll)pos * rcnt << "\n";
    }

    return 0;
}
