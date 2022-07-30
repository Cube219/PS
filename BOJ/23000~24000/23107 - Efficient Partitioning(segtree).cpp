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

struct SegTree
{
    using Type = ll;

    Type merge(Type l, Type r)
    {
        return max(l, r);
    }

    const Type emptyNode = -LNF;

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
        t[idx] = max(t[idx], v);
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
    int n;
    cin >> n;
    vector<ll> a(n), b(n), c(n);
    for(auto& v : a) cin >> v;
    for(auto& v : b) cin >> v;
    for(auto& v : c) cin >> v;

    vector<ll> asum(n);
    partial_sum(a.begin(), a.end(), asum.begin());

    vector<ll> vv;
    for(int i = 0; i < n; ++i) {
        vv.push_back(asum[i] + c[i]);
    }
    vv.push_back(-LNF);
    sort(vv.begin(), vv.end());
    vv.erase(unique(vv.begin(), vv.end()), vv.end());

    SegTree sg1(vv.size()), sg2(vv.size());
    ll res;
    for(int i = 0; i < n; ++i) {
        int idx = lower_bound(vv.begin(), vv.end(), asum[i] + c[i]) - vv.begin();

        ll v = asum[i] + b[0] + c[i];
        if(idx > 0) v = max(v, sg1.query(0, idx - 1));
        if(idx < vv.size()) v = max(v, sg2.query(idx, vv.size() - 1) + asum[i] + c[i]);

        if(i < n - 1) {
            int vidx = upper_bound(vv.begin(), vv.end(), v + asum[i] - b[i + 1]) - vv.begin() - 1;
            sg1.update(vidx, v);
            sg2.update(vidx, -asum[i] + b[i + 1]);
        } else {
            res = v;
        }
    }
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
