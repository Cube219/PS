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
    using Type = int;

    Type merge(Type l, Type r)
    {
        return max(l, r);
    }

    const Type emptyNode = 0;

    vector<Type> t;
    vector<int> lazy;
    int stLeaf, n;

    SegTree(int n)
    {
        stLeaf = 1;
        while(stLeaf < n) stLeaf *= 2;

        t.resize(stLeaf * 2, emptyNode);
        lazy.resize(stLeaf * 2, 0);
    }

    void initv(int idx, Type v)
    {
        t[stLeaf + idx] = v;
    }

    void build()
    {
        for(int i = stLeaf - 1; i > 0; --i) {
            t[i] = merge(t[i * 2], t[i * 2 + 1]);
        }
    }

    void push(int l, int r, int node)
    {
        if(lazy[node] == 0) return;

        if(node < stLeaf) {
            lazy[node * 2] += lazy[node];
            lazy[node * 2 + 1] += lazy[node];
        }
        t[node] += lazy[node];
        lazy[node] = 0;
    }

    Type queryImpl(int cl, int cr, int l, int r, int node)
    {
        push(cl, cr, node);
        if(cr < l || r < cl) return emptyNode;
        if(l <= cl && cr <= r) return t[node];
        int m = (cl + cr) / 2;
        return merge(queryImpl(cl, m, l, r, node * 2), queryImpl(m + 1, cr, l, r, node * 2 + 1));
    }

    void udtImpl(int cl, int cr, int l, int r, int node, Type v)
    {
        push(cl, cr, node);
        if(cr < l || r < cl) return;
        if(l <= cl && cr <= r) {
            lazy[node] += v;
            push(cl, cr, node);
            return;
        }
        int m = (cl + cr) / 2;
        udtImpl(cl, m, l, r, node * 2, v);
        udtImpl(m + 1, cr, l, r, node * 2 + 1, v);
        t[node] = merge(t[node * 2], t[node * 2 + 1]);
    }

    Type query(int l, int r)
    {
        return queryImpl(0, stLeaf - 1, l, r, 1);
    }

    void update(int l, int r, Type v)
    {
        udtImpl(0, stLeaf - 1, l, r, 1, v);
    }
};

void solve()
{
    int n, k;
    cin >> n >> k;
    vector<int> c(n);
    for(auto& v : c) cin >> v;

    vector<int> last(k + 1, n - 1);
    SegTree sg(n + 1);
    for(int i = n - 1; i >= 0; --i) {
        if(c[i] > 0) {
            int r = last[c[i]];
            last[c[i]] = i - 1;

            sg.update(i + 1, r + 1, 1);
        }

        int v = sg.query(min(i + (k + 1) / 2, n), n);
        sg.update(i, i, v);
    }

    cout << sg.query(0, 0);
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
