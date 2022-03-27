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
constexpr int INF = 0x1f3f3f3f;
constexpr ll LNF = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 1'000'000'007;

struct SegTree
{
    struct Node
    {
        int v, mn, mx, l2r, r2l;
    };
    int n;
    vector<Node> t;

    SegTree(int _n)
    {
        n = _n;
        t.resize(n * 2, emptyNode);
    }

    void initv(int idx, int v)
    {
        t[n + idx] = { -INF, v, v, -INF, -INF };
    }

    void build()
    {
        for(int i = n - 1; i > 0; --i) {
            t[i] = merge(t[i << 1], t[i << 1 | 1]);
        }
    }

    void update(int idx, int v)
    {
        idx += n;
        t[idx] = { -INF, v, v, -INF, -INF };
        idx >>= 1;
        while(idx > 0) {
            t[idx] = merge(t[idx << 1], t[idx << 1 | 1]);
            idx >>= 1;
        }
    }

    Node find(int l, int r)
    {
        l += n;
        r += n + 1;
        Node resl = emptyNode;
        Node resr = emptyNode;
        while(l < r) {
            if(l & 1) resl = merge(resl, t[l++]);
            if(r & 1) resr = merge(t[--r], resr);
            l >>= 1;
            r >>= 1;
        }
        return merge(resl, resr);
    }

    Node merge(Node l, Node r)
    {
        if(l.mx == INF) return r;
        if(r.mx == INF) return l;

        Node res = emptyNode;
        res.v = max(l.v, r.v);
        res.v = max(res.v, l.l2r - r.mn);
        res.v = max(res.v, r.r2l - l.mn);
        res.mn = min(l.mn, r.mn);
        res.mx = max(l.mx, r.mx);
        res.l2r = max(l.l2r, r.l2r);
        res.l2r = max(res.l2r, r.mx - l.mn);
        res.r2l = max(l.r2l, r.r2l);
        res.r2l = max(res.r2l, l.mx - r.mn);

        return res;
    }

    const Node emptyNode = { -INF, INF, -INF, -INF, -INF };
};


void solve()
{
    int n, q;
    cin >> n >> q;
    SegTree sg(n);
    for(int i = 0; i < n; ++i) {
        ll a;
        cin >> a;
        sg.initv(i, a);
    }
    sg.build();

    for(int qq = 0; qq < q; ++qq) {
        int type;
        cin >> type;
        if(type == 1) {
            int x, y;
            cin >> x >> y;
            x--;
            sg.update(x, y);
        } else {
            int l, r;
            cin >> l >> r;
            l--; r--;

            auto res = sg.find(l, r);
            cout << res.v << "\n";
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
