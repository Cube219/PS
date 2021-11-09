#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;
constexpr ll INF = 10000000001;

template <int N>
struct SegTree
{
    struct Node
    {
        ll mx, lmx, rmx, sum;
    };
    int n;
    Node t[N * 2 + 1];

    void init(int _n)
    {
        n = _n;
        // Add init values in [n, n+n)
    }

    Node merge(Node l, Node r)
    {
        Node res;
        res.mx = max(l.mx, r.mx);
        res.mx = max(res.mx, l.rmx + r.lmx);

        res.lmx = max(l.lmx, l.sum + r.lmx);
        res.rmx = max(r.rmx, r.sum + l.rmx);

        res.sum = l.sum + r.sum;

        return res;
    }

    void build()
    {
        for(int i = n - 1; i > 0; --i) {
            t[i] = merge(t[i << 1], t[i << 1 | 1]);
        }
    }

    Node find(int l, int r)
    {
        l += n;
        r += n + 1;
        Node resl = { -INF, -INF, -INF, 0 };
        Node resr = { -INF, -INF, -INF, 0 };
        while(l < r) {
            if(l & 1) resl = merge(resl, t[l++]);
            if(r & 1) resr = merge(t[--r], resr);
            l >>= 1;
            r >>= 1;
        }
        return merge(resl, resr);
    }
};

struct Node
{
    int l, r;
};

SegTree<100000> sg;
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
        sg.t[n + i] = { a, a, a, a };
    }
    sg.build();

    cin >> m;
    for(int i = 0; i < m; ++i) {
        Node a, b;
        cin >> a.l >> a.r >> b.l >> b.r;
        a.l--; a.r--; b.l--; b.r--;
        if(a.l > b.l) swap(a, b);

        if(a.r < b.l) {
            auto lres = sg.find(a.l, a.r);
            auto rres = sg.find(b.l, b.r);
            auto cres = sg.find(a.r + 1, b.l - 1);
            cout << lres.rmx + rres.lmx + cres.sum << "\n";
        } else {
            ll res;
            auto cres = sg.find(b.l, min(a.r, b.r));
            res = cres.mx;

            if(a.l < b.l) {
                auto lres = sg.find(a.l, b.l - 1);
                auto rres = sg.find(b.l, b.r);
                res = max(res, lres.rmx + rres.lmx);
            }
            if(a.r < b.r) {
                auto lres = sg.find(a.l, a.r);
                auto rres = sg.find(a.r + 1, b.r);
                res = max(res, lres.rmx + rres.lmx);
            }

            cout << res << "\n";
        }
    }
    
    return 0;
}
