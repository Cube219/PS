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
    struct Node
    {
        int mn, mx, v;
    };
    using T = Node;

    T merge(T l, T r)
    {
        T res;
        res.mn = min(l.mn, r.mn);
        res.mx = max(l.mx, r.mx);
        res.v = max(l.v, r.v);
        res.v = max(res.v, r.mx - l.mn);
        return res;
    }

    constexpr static T empty = { INF, -INF, 0 };

    int n;
    vector<T> t;
    SegTree(int _n) : n(_n), t(_n * 2, empty) {}

    void initv(int idx, int v)
    {
        t[n + idx] = { v, v, 0 };
    }

    void build()
    {
        for(int i = n - 1; i > 0; --i) t[i] = merge(t[i << 1], t[i << 1 | 1]);
    }

    void update(int pos, int v)
    {
        pos += n;
        t[pos] = { v, v, 0 };
        for(pos >>= 1; pos > 0; pos >>= 1) t[pos] = merge(t[pos << 1], t[pos << 1 | 1]);
    }

    T query(int l, int r)
    {
        T lres = empty, rres = empty;
        for(l += n, r += n + 1; l < r; l >>= 1, r >>= 1) {
            if(l & 1) lres = merge(lres, t[l++]);
            if(r & 1) rres = merge(t[--r], rres);
        }
        return merge(lres, rres);
    }
};


void solve()
{
    int n;
    cin >> n;
    SegTree sg(n);
    for(int i = 0; i < n; ++i) {
        int v;
        cin >> v;
        sg.initv(i, v);
    }
    sg.build();

    int q;
    cin >> q;
    for(int i = 0; i < q; ++i) {
        int t, a, b;
        cin >> t >> a >> b;
        if(t == 1) {
            sg.update(a - 1, b);
        } else {
            cout << sg.query(a - 1, b - 1).v << "\n";
        }
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
