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
    int t[N * 3];
    int stLeaf, n;

    void init(int n)
    {
        stLeaf = 1;
        while(stLeaf < n) stLeaf *= 2;
    }

    int findImpl(int cl, int cr, int l, int r, int node)
    {
        if(l <= cl && cr <= r) return t[node];
        else if(cr < l || r < cl) return 0;
        int m = (cl + cr) / 2;
        return findImpl(cl, m, l, r, node * 2) + findImpl(m + 1, cr, l, r, node * 2 + 1);
    }

    int find(int l, int r)
    {
        return findImpl(0, stLeaf - 1, l, r, 1);
    }

    void add(int idx, int v)
    {
        int node = stLeaf + idx;
        t[node]++;
        node /= 2;
        while(node > 0) {
            t[node] = t[node * 2] + t[node * 2 + 1];
            node /= 2;
        }
    }
};

struct Node
{
    int v;
    int idx;
};

int n;
Node d[500001];
SegTree<500001> sg;
int res[500001];

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for(int i = 0; i < n; ++i) {
        cin >> d[i].v;
        d[i].idx = i;
    }
    sort(d, d + n, [](const Node& l, const Node& r) {
        if(l.v == r.v) return l.idx > r.idx;
        return l.v < r.v;
    });
    sg.init(n);
    for(int i = 0; i < n; ++i) {
        res[d[i].idx] = d[i].idx - sg.find(0, d[i].idx) + 1;
        sg.add(d[i].idx, 1);
    }

    for(int i = 0; i < n; ++i) {
        cout << res[i] << "\n";
    }


    return 0;
}
