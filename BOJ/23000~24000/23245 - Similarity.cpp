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
    ll t[N * 3];
    int stLeaf, n;

    void init(int n)
    {
        stLeaf = 1;
        while(stLeaf < n) stLeaf *= 2;
    }

    void clear()
    {
        for(int i = 0; i <= stLeaf * 2; ++i) {
            t[i] = 0;
        }
    }

    ll findImpl(int cl, int cr, int l, int r, int node)
    {
        if(cr < l || r < cl) return 0;
        if(l <= cl && cr <= r) return t[node];
        int m = (cl + cr) / 2;
        return findImpl(cl, m, l, r, node * 2) + findImpl(m + 1, cr, l, r, node * 2 + 1);
    }

    ll find(int l, int r)
    {
        return findImpl(0, stLeaf - 1, l, r, 1);
    }

    void add(int idx, ll v)
    {
        int node = stLeaf + idx;
        t[node] += v;
        node /= 2;
        while(node > 0) {
            t[node] = t[node * 2] + t[node * 2 + 1];
            node /= 2;
        }
    }
};

struct Node
{
    int v1, v2;
};

int n;
Node d[100001];
SegTree<1000001> sg;
ll d1[100001], res;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for(int i = 0; i < n; ++i) {
        cin >> d[i].v1;
    }
    for(int i = 0; i < n; ++i) {
        cin >> d[i].v2;
    }
    sort(d, d + n, [](const Node& l, const Node& r) {
        if(l.v1 == r.v1) return l.v2 < r.v2;
        return l.v1 < r.v1;
    });

    sg.init(1000001);

    int lasti = 0;
    for(int i = 1; i < n; ++i) {
        if(d[i].v1 != d[lasti].v1) {
            for(int j = lasti; j < i; ++j) {
                sg.add(d[j].v2, 1);
            }
            lasti = i;
        }
        d1[i] = sg.find(0, d[i].v2 - 1);
    }

    sg.clear();
    lasti = 1;
    for(int i = 2; i < n; ++i) {
        if(d[i].v1 != d[lasti].v1) {
            for(int j = lasti; j < i; ++j) {
                sg.add(d[j].v2, d1[j]);
            }
            lasti = i;
        }
        res += sg.find(0, d[i].v2 - 1);
    }

    cout << res;

    return 0;
}
