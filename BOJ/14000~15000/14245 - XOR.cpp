#define _CRT_SECURE_NO_WARNINGS 1

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
    int t[N * 3], lazy[N * 3];
    int stLeaf, n;

    void init(int n, int* pData)
    {
        stLeaf = 1;
        while(stLeaf < n) stLeaf *= 2;
        for(int i = 0; i < n; ++i) {
            t[stLeaf + i] = pData[i];
        }
        for(int i = stLeaf - 1; i > 0; --i) {
            t[i] = t[i * 2] + t[i * 2 + 1];
        }
    }

    void propagate(int l, int r, int node)
    {
        if(lazy[node] == 0) return;

        if(node < stLeaf) {
            lazy[node * 2] ^= lazy[node];
            lazy[node * 2 + 1] ^= lazy[node];
        } else {
            t[node] ^= lazy[node];
        }
        lazy[node] = 0;
    }

    int findImpl(int cl, int cr, int l, int r, int node)
    {
        propagate(cl, cr, node);
        if(l <= cl && cr <= r) return t[node];
        else if(cr < l || r < cl) return 0;
        int m = (cl + cr) / 2;
        return findImpl(cl, m, l, r, node * 2) + findImpl(m + 1, cr, l, r, node * 2 + 1);
    }

    void addImpl(int cl, int cr, int l, int r, int node, int v)
    {
        propagate(cl, cr, node);
        if(l <= cl && cr <= r) {
            lazy[node] = lazy[node] ^ v;
            propagate(cl, cr, node);
            return;
        } else if(cr < l || r < cl) return;
        int m = (cl + cr) / 2;
        addImpl(cl, m, l, r, node * 2, v);
        addImpl(m + 1, cr, l, r, node * 2 + 1, v);
    }

    int find(int l, int r)
    {
        return findImpl(0, stLeaf - 1, l, r, 1);
    }

    void add(int l, int r, int v)
    {
        addImpl(0, stLeaf - 1, l, r, 1, v);
    }
};

SegTree<500001> seg;
int n, d[500001];
int m;

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
    seg.init(n, d);
    cin >> m;
    for(int i = 0; i < m; ++i) {
        int t;
        cin >> t;
        if(t == 1) {
            int a, b, c;
            cin >> a >> b >> c;
            seg.add(a, b, c);
        } else {
            int a;
            cin >> a;
            cout << seg.find(a, a) << "\n";
        }
    }

    return 0;
}
