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
    int lazy[N * 3], lmax[N * 3], rmax[N * 3], cmax[N * 3], mx[N * 3];
    int stLeaf, n;

    void init(int _n)
    {
        stLeaf = 1;
        while(stLeaf < _n) stLeaf *= 2;
        n = _n;
    }

    void propagate(int l, int r, int node)
    {
        if(lazy[node] == 0) return;

        if(node < stLeaf) {
            lazy[node * 2] = lazy[node];
            lazy[node * 2 + 1] = lazy[node];
        }
        if(lazy[node] == 1) {
            lmax[node] = r - l + 1;
            rmax[node] = r - l + 1;
            cmax[node] = r - l + 1;
            mx[node] = r - l + 1;
        } else { // -1
            lmax[node] = 0;
            rmax[node] = 0;
            cmax[node] = 0;
            mx[node] = 0;
        }
        lazy[node] = 0;
    }

    int findImpl(int l, int r, int v, int node)
    {
        int m = (l + r) / 2;
        propagate(l, r, node);

        if(lmax[node] >= v) return l;
        if(mx[node * 2] >= v) return findImpl(l, m, v, node * 2);
        if(cmax[node] >= v) {
            int cnt = rmax[node * 2];
            return m - cnt + 1;
        }
        if(mx[node * 2 + 1] >= v) return findImpl(m + 1, r, v, node * 2 + 1);
        if(rmax[node] >= v) {
            return r - rmax[node] + 1;
        }
        return -1;
    }

    void addImpl(int cl, int cr, int l, int r, int node, int v)
    {
        propagate(cl, cr, node);
        if(l <= cl && cr <= r) {
            lazy[node] = v;
            propagate(cl, cr, node);
            return;
        } else if(cr < l || r < cl) return;
        int m = (cl + cr) / 2;
        addImpl(cl, m, l, r, node * 2, v);
        addImpl(m + 1, cr, l, r, node * 2 + 1, v);
        cmax[node] = rmax[node * 2] + lmax[node * 2 + 1];
        lmax[node] = lmax[node * 2];
        if(lmax[node * 2] == m - cl + 1) {
            lmax[node] += lmax[node * 2 + 1];
        }
        rmax[node] = rmax[node * 2 + 1];
        if(rmax[node * 2 + 1] == cr - m) {
            rmax[node] += rmax[node * 2];
        }
        mx[node] = max(lmax[node], rmax[node]);
        mx[node] = max(mx[node], cmax[node]);
        mx[node] = max(mx[node], mx[node * 2]);
        mx[node] = max(mx[node], mx[node * 2 + 1]);
    }

    int find(int v)
    {
        return findImpl(0, stLeaf - 1, v, 1);
    }

    void add(int l, int r, int v)
    {
        addImpl(0, stLeaf - 1, l, r, 1, v);
    }
};

int n, m;
SegTree<50001> sg;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;
    sg.init(n);
    sg.add(0, n - 1, 1);
    for(int i = 0; i < m; ++i) {
        int a;
        cin >> a;
        if(a == 1) {
            int b;
            cin >> b;
            int pos = sg.find(b);
            if(pos == -1) cout << "0\n";
            else {
                cout << pos + 1 << "\n";
                sg.add(pos, pos + b - 1, -1);
            }
        } else {
            int b, c;
            cin >> b >> c;
            b--;
            sg.add(b, b + c - 1, 1);
        }
    }

    return 0;
}
