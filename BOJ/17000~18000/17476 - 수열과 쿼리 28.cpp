#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;

using ll = long long int;
constexpr ll INF = 99991000100000;

template <int N>
class SegTree
{
public:
    struct Node
    {
        ll mx, mn, sum;
        ll addlazy;
    };
    Node t[N * 3];
    int stLeaf, n;

    void init(int n)
    {
        stLeaf = 1;
        while(stLeaf < n) stLeaf *= 2;
        for(int i = 0; i < stLeaf; ++i) {
            t[stLeaf + i] = { 0, INF, 0, 0 };
        }
    }

    void initv(int idx, int v)
    {
        t[stLeaf + idx] = { v, v, v, 0 };
    }

    void build()
    {
        for(int i = stLeaf - 1; i > 0; --i) {
            merge(i);
        }
    }

    void merge(int node)
    {
        if(node >= stLeaf) return;

        Node& cur = t[node];
        Node l = t[node * 2];
        Node r = t[node * 2 + 1];

        cur.mx = max(l.mx, r.mx);
        cur.mn = min(l.mn, r.mn);
        cur.sum = l.sum + r.sum;
    }

    void propagate(int l, int r, int node)
    {
        if(node >= stLeaf) return;

        Node& cur = t[node];
        for(int i = 0; i < 2; ++i) {
            Node& child = t[node * 2 + i];
            int cl = l, cr = r;
            if(i == 0) cr = (l + r) / 2;
            else cl = (l + r) / 2 + 1;
            ll gap = cur.mx - cur.mn;
            if(gap > 0) {
                // add¿¬»ê¸¸ µÊ
                if(cur.addlazy == 0) continue;
                ll dv = cur.addlazy;
                child.mx += dv;
                child.mn += dv;
                child.sum += dv * (cr - cl + 1);
                child.addlazy += cur.addlazy;
            } else {
                child.mx = cur.mx;
                child.mn = cur.mn;
                child.sum = (cr - cl + 1) * child.mx;
            }
        }
        cur.addlazy = 0;
    }

    ll findImpl(int cl, int cr, int l, int r, int node)
    {
        propagate(cl, cr, node);
        if(cr < l || r < cl) return 0;
        if(l <= cl && cr <= r) return t[node].sum;
        int m = (cl + cr) / 2;
        return findImpl(cl, m, l, r, node * 2) + findImpl(m + 1, cr, l, r, node * 2 + 1);
    }

    void addImpl(int cl, int cr, int l, int r, int node, ll v)
    {
        propagate(cl, cr, node);
        if(cr < l || r < cl) return;
        if(l <= cl && cr <= r) {
            t[node].addlazy += v;
            t[node].mn += v;
            t[node].mx += v;
            t[node].sum += (cr - cl + 1) * v;
            propagate(cl, cr, node);
            return;
        }
        int m = (cl + cr) / 2;
        addImpl(cl, m, l, r, node * 2, v);
        addImpl(m + 1, cr, l, r, node * 2 + 1, v);
        merge(node);
    }

    void sqImpl(int cl, int cr, int l, int r, int node)
    {
        propagate(cl, cr, node);
        if(cr < l || r < cl) return;
        ll mnsq = (ll)sqrt(t[node].mn);
        ll mxsq = (ll)sqrt(t[node].mx);
        if(l <= cl && cr <= r && (mxsq == mnsq || t[node].mx - t[node].mn == 1)) {
            if(mnsq == mxsq) {
                t[node].mx = mxsq;
                t[node].mn = mxsq;
                t[node].sum = (cr - cl + 1) * mxsq;
            } else {
                t[node].addlazy -= t[node].mx - mxsq;
                t[node].sum -= (cr - cl + 1) * (t[node].mx - mxsq);
                t[node].mx = mxsq;
                t[node].mn = mnsq;
            }
            propagate(cl, cr, node);
            return;
        }
        int m = (cl + cr) / 2;
        sqImpl(cl, m, l, r, node * 2);
        sqImpl(m + 1, cr, l, r, node * 2 + 1);
        merge(node);
    }

    ll find(int l, int r)
    {
        return findImpl(0, stLeaf - 1, l, r, 1);
    }

    void add(int l, int r, ll v)
    {
        addImpl(0, stLeaf - 1, l, r, 1, v);
    }

    void sq(int l, int r)
    {
        sqImpl(0, stLeaf - 1, l, r, 1);
    }
};

SegTree<100001> sg;
int n, m;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    sg.init(n);
    for(int i = 0; i < n; ++i) {
        int a;
        cin >> a;
        sg.initv(i, a);
    }
    sg.build();
    cin >> m;
    for(int i = 0; i < m; ++i) {
        int a, l, r, x;
        cin >> a >> l >> r;
        l--; r--;
        if(a == 1) {
            cin >> x;
            sg.add(l, r, x);
        } else if(a == 2) {
            sg.sq(l, r);
        } else {
            cout << sg.find(l, r) << "\n";
        }
    }

    return 0;
}
