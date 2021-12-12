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
    struct Node
    {
        int lType;
        int rType;
        int v;
    };
    int n;
    Node t[N * 2 + 1];

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

    void update(int idx, int v)
    {
        idx += n;
        t[idx].lType = v;
        t[idx].rType = v;
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
        Node resl = { -1, -1, -1 };
        Node resr = { -1, -1, -1 };
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
        Node res;
        res.lType = l.lType;
        res.rType = r.rType;
        res.v = l.v + r.v;
        if(l.rType != r.lType) {
            res.v++;
        }
        return res;
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
    SegTree<100001> sg;
    sg.init(n);
    for(int i = 0; i < n; ++i) {
        int v;
        cin >> v;
        sg.t[n + i] = { v, v, 0 };
    }
    sg.build();

    for(int i = 0; i < q; ++i) {
        int t, a, b;
        cin >> t;
        if(t == 1) {
            cin >> a >> b;
            a--; b--;
            cout << sg.find(a, b).v + 1 << "\n";
        } else {
            cin >> a >> b;
            a--;
            sg.update(a, b);
        }
    }

    return 0;
}
