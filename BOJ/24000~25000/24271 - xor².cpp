#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;
constexpr int INF = 0x3f3f3f3f;
constexpr ll LNF = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 1'000'000'007;

class SegTree
{
public:
    vector<int> t;
    int stLeaf, n, dep;

    SegTree(int n)
    {
        stLeaf = 1;
        dep = 0;
        while(stLeaf < n) {
            stLeaf *= 2;
            dep++;
        }
        t.resize(stLeaf * 2, emptyNode);
    }

    void initv(int idx, int v)
    {
        t[stLeaf + idx] = v;
    }

    void build()
    {
        for(int i = stLeaf - 1; i > 0; --i) {
            t[i] = merge(t[i * 2], t[i * 2 + 1]);
        }
    }

    int findImpl(int cl, int cr, int l, int r, int node, int x, int curdep)
    {
        if(cr < l || r < cl) return emptyNode;
        if(l <= cl && cr <= r) return t[node];
        int m = (cl + cr) / 2;

        int lch, rch;
        if(x & (1 << curdep)){
            lch = node * 2 + 1;
            rch = node * 2;
        } else {
            lch = node * 2;
            rch = node * 2 + 1;
        }

        return merge(findImpl(cl, m, l, r, lch, x, curdep - 1), findImpl(m + 1, cr, l, r, rch, x, curdep - 1));
    }

    int find(int l, int r, int x)
    {
        return findImpl(0, stLeaf - 1, l, r, 1, x, dep - 1);
    }

    void update(int idx, int v)
    {
        idx += stLeaf;
        t[idx] ^= v;
        idx >>= 1;
        while(idx > 0) {
            t[idx] = merge(t[idx * 2], t[idx * 2 + 1]);
            idx >>= 1;
        }
    }

    int merge(int l, int r)
    {
        return l ^ r;
    }

    const int emptyNode = 0;
};


void solve()
{
    int n;
    cin >> n;
    SegTree sg(n);
    for(int i = 0; i < n; ++i) {
        int a;
        cin >> a;
        sg.initv(i, a);
    }
    sg.build();

    int q;
    cin >> q;
    for(int i = 0; i < q; ++i) {
        int a;
        cin >> a;
        if(a == 1) {
            int l, r, x;
            cin >> l >> r >> x;
            cout << sg.find(l, r, x) << "\n";
        } else {
            int pos, x;
            cin >> pos >> x;
            sg.update(pos, x);
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
