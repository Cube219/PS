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

    void initv(int idx, int v)
    {
        t[stLeaf + idx] = v;
    }

    void build()
    {
        for(int i = stLeaf - 1; i > 0; --i) {
            t[i] = t[i * 2] + t[i * 2 + 1];
        }
    }

    int findImpl(int cl, int cr, int l, int r, int node)
    {
        if(cr < l || r < cl) return 0;
        if(l <= cl && cr <= r) return t[node];
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
        t[node] = v;
        node /= 2;
        while(node > 0) {
            t[node] = t[node * 2] + t[node * 2 + 1];
            node /= 2;
        }
    }
};

struct Node
{
    int l, r, x;
};

int n, m;
SegTree<200001> sg;
Node d[200001];
vector<int> st;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;
    for(int i = 0; i < m; ++i) {
        cin >> d[i].l >> d[i].r >> d[i].x;
        d[i].l--;
        d[i].r--;
    }
    sort(d, d + m, [](const Node& l, const Node& r) {
        return l.r < r.r;
    });

    sg.init(n);
    int lastr = -1;
    for(int i = 0; i < m; ++i) {
        Node& cur = d[i];
        for(int j = lastr + 1; j <= cur.r; ++j) {
            st.push_back(j);
        }

        int num = sg.find(cur.l, cur.r);
        if(num < cur.x) {
            num = cur.x - num;
            for(int j = 0; j < num; ++j) {
                sg.add(st.back(), 1);
                st.pop_back();
            }
        }
        lastr = cur.r;
    }

    int base = sg.stLeaf;
    for(int i = 0; i < n; ++i) {
        cout << sg.t[base + i] << " ";
    }

    return 0;
}
