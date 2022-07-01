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
        ll v;
        int l, r, sz, lmx, rmx;
    };
    using Type = Node;

    Type merge(Type l, Type r)
    {
        if(l.v == -1) return r;
        if(r.v == -1) return l;

        Type res;
        res.v = l.v + r.v;
        res.l = l.l;
        res.r = r.r;
        res.sz = l.sz + r.sz;
        res.lmx = l.lmx;
        res.rmx = r.rmx;

        if(l.r != r.l) {
            res.v += (ll)l.rmx * r.lmx;
            if(l.lmx == l.sz) res.lmx += r.lmx;
            if(r.rmx == r.sz) res.rmx += l.rmx;
        }

        return res;
    }

    const Type emptyNode = { -1, };

    vector<Type> t;
    vector<char> lazy;
    int stLeaf, n;

    SegTree(int n)
    {
        stLeaf = 1;
        while(stLeaf < n) stLeaf *= 2;

        t.resize(stLeaf * 2, emptyNode);
        lazy.resize(stLeaf * 2, 0);
    }

    void initv(int idx, int v)
    {
        t[stLeaf + idx] = { 1, v, v, 1, 1, 1 };
    }

    void build()
    {
        for(int i = stLeaf - 1; i > 0; --i) {
            t[i] = merge(t[i * 2], t[i * 2 + 1]);
        }
    }

    void push(int l, int r, int node)
    {
        if(!lazy[node]) return;

        if(node < stLeaf) {
            lazy[node * 2] = !lazy[node * 2];
            lazy[node * 2 + 1] = !lazy[node * 2 + 1];
        }

        t[node].l = 1 - t[node].l;
        t[node].r = 1 - t[node].r;

        lazy[node] = false;
    }

    Type queryImpl(int cl, int cr, int l, int r, int node)
    {
        push(cl, cr, node);
        if(cr < l || r < cl) return emptyNode;
        if(l <= cl && cr <= r) return t[node];
        int m = (cl + cr) / 2;
        return merge(queryImpl(cl, m, l, r, node * 2), queryImpl(m + 1, cr, l, r, node * 2 + 1));
    }

    void udtImpl(int cl, int cr, int l, int r, int node)
    {
        push(cl, cr, node);
        if(cr < l || r < cl) return;
        if(l <= cl && cr <= r) {
            lazy[node] = true;
            push(cl, cr, node);
            return;
        }
        int m = (cl + cr) / 2;
        udtImpl(cl, m, l, r, node * 2);
        udtImpl(m + 1, cr, l, r, node * 2 + 1);
        t[node] = merge(t[node * 2], t[node * 2 + 1]);
    }

    Type query(int l, int r)
    {
        return queryImpl(0, stLeaf - 1, l, r, 1);
    }

    void update(int l, int r)
    {
        udtImpl(0, stLeaf - 1, l, r, 1);
    }
};

void solve()
{
    int n, q;
    cin >> n >> q;
    SegTree sg(n);
    for(int i = 0; i < n; ++i) {
        int v;
        cin >> v;
        sg.initv(i, v);
    }
    sg.build();

    for(int i = 0; i < q; ++i) {
        int t, l, r;
        cin >> t >> l >> r;
        l--; r--;
        if(t == 1) {
            sg.update(l, r);
        } else {
            auto res = sg.query(l, r);
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
