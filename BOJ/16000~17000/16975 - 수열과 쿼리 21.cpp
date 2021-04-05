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
    ll t[N * 3], lazy[N * 3];
    int stLeaf, n;

    void init(int n, ll* pData)
    {
        stLeaf = 1;
        while(stLeaf < n) stLeaf *= 2;
        for(int i = 0; i < n; ++i) {
            t[stLeaf + i] = pData[i];
        }
    }

    void propagate(int l, int r, int node)
    {
        if(lazy[node] == 0) return;

        if(node < stLeaf) {
            lazy[node * 2] += lazy[node];
            lazy[node * 2 + 1] += lazy[node];
        } else {
            t[node] += lazy[node];
        }
        lazy[node] = 0;
    }

    ll findImpl(int cl, int cr, int l, int r, int node)
    {
        propagate(cl, cr, node);
        if(l <= cl && cr <= r) return t[node];
        else if(cr < l || r < cl) return 0;
        int m = (cl + cr) / 2;
        return findImpl(cl, m, l, r, node * 2) + findImpl(m + 1, cr, l, r, node * 2 + 1);
    }

    void addImpl(int cl, int cr, int l, int r, int node, ll v)
    {
        propagate(cl, cr, node);
        if(l <= cl && cr <= r) {
            lazy[node] += v;
            propagate(cl, cr, node);
            return;
        } else if(cr < l || r < cl) return;
        int m = (cl + cr) / 2;
        addImpl(cl, m, l, r, node * 2, v);
        addImpl(m + 1, cr, l, r, node * 2 + 1, v);
    }

    ll find(int l, int r)
    {
        return findImpl(0, stLeaf - 1, l, r, 1);
    }

    void add(int l, int r, ll v)
    {
        addImpl(0, stLeaf - 1, l, r, 1, v);
    }
};

int n, m;
ll d[100001];
SegTree<100001> sg;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for(int i = 0; i < n; ++i) {
        cin >> d[i];
    }
    sg.init(n, d);
    cin >> m;
    for(int i = 0; i < m; ++i) {
        int a;
        cin >> a;
        if(a == 1) {
            int b, c, d;
            cin >> b >> c >> d;
            b--; c--;
            sg.add(b, c, d);
        } else {
            int b;
            cin >> b;
            b--;
            cout << sg.find(b, b) << "\n";
        }
    }

    return 0;
}
