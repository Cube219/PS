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
    ll t[N * 3], mn[N * 3];
    int stLeaf, n;

    void init(int n)
    {
        stLeaf = 1;
        while(stLeaf < n) stLeaf *= 2;
        for(int i = 0; i < stLeaf; ++i) {
            mn[stLeaf + i] = 100000000000;
        }
    }

    void initv(int idx, int v)
    {
        t[stLeaf + idx] = v;
        mn[stLeaf + idx] = v;
    }

    void build()
    {
        for(int i = stLeaf - 1; i > 0; --i) {
            t[i] = t[i * 2] + t[i * 2 + 1];
            mn[i] = min(mn[i * 2], mn[i * 2 + 1]);
        }
    }

    ll findmnImpl(int cl, int cr, int l, int r, int node)
    {
        if(cr < l || r < cl) return 100000000000;
        if(l <= cl && cr <= r) return mn[node];
        int m = (cl + cr) / 2;
        return min(findmnImpl(cl, m, l, r, node * 2), findmnImpl(m + 1, cr, l, r, node * 2 + 1));
    }

    ll findsumImpl(int cl, int cr, int l, int r, int node)
    {
        if(cr < l || r < cl) return 0;
        if(l <= cl && cr <= r) return t[node];
        int m = (cl + cr) / 2;
        return findsumImpl(cl, m, l, r, node * 2) + findsumImpl(m + 1, cr, l, r, node * 2 + 1);
    }


    ll findsum(int l, int r)
    {
        return findsumImpl(0, stLeaf - 1, l, r, 1);
    }

    ll findmn(int l, int r)
    {
        return findmnImpl(0, stLeaf - 1, l, r, 1);
    }

    void change(int idx, ll v)
    {
        int node = stLeaf + idx;
        t[node] = v;
        mn[node] = v;
        node /= 2;
        while(node > 0) {
            t[node] = t[node * 2] + t[node * 2 + 1];
            mn[node] = min(mn[node * 2], mn[node * 2 + 1]);
            node /= 2;
        }
    }
};

int n, m;
SegTree<200001> sg;

ll lsum(int idx, int v)
{
    if(sg.t[sg.stLeaf + idx] < v) return sg.t[sg.stLeaf + idx];

    int l = 0, r = idx;
    while(l + 1 < r) {
        int m = (l + r) / 2;
        ll res = sg.findmn(m, idx);
        if(res < v) {
            l = m;
        } else {
            r = m;
        }
    }
    if(r == 1) {
        ll res = sg.findmn(0, idx);
        if(res >= v) return sg.findsum(0, idx);
    }
    return sg.findsum(r, idx);
}

ll rsum(int idx, int v)
{
    if(sg.t[sg.stLeaf + idx] < v) return 0;

    int l = idx, r = n - 1;
    while(l + 1 < r) {
        int m = (l + r) / 2;
        ll res = sg.findmn(idx, m);
        if(res < v) {
            r = m;
        } else {
            l = m;
        }
    }
    if(l == n - 2) {
        ll res = sg.findmn(idx, n - 1);
        if(res >= v) return sg.findsum(idx, n - 1);
    }
    return sg.findsum(idx, l);
}

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
        int a, b, c;
        cin >> a >> b >> c;
        if(a == 1) {
            b--;
            sg.change(b, c);
        } else {
            b--;
            cout << lsum(b, c) + rsum(b, c) - sg.t[sg.stLeaf + b] << "\n";
        }
    }

    return 0;
}
