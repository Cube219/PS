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
        t[node] += v;
        node /= 2;
        while(node > 0) {
            t[node] = t[node * 2] + t[node * 2 + 1];
            node /= 2;
        }
    }
};

int n;
SegTree<100010> sg;
vector<int> d[50001];

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    sg.init(n * 2);
    for(int i = 0; i < n * 2; ++i) {
        int v;
        cin >> v;
        v--;
        d[v].push_back(i);
    }

    for(int i = 0; i < n; ++i) {
        if(d[i][0] > d[i][1]) swap(d[i][0], d[i][1]);
    }
    sort(d, d + n, [](const auto& l, const auto& r) {
        return l[0] < r[0];
    });

    int res = 0;
    for(int i = 0; i < n; ++i) {
        int v = sg.find(d[i][0], d[i][1]);
        res += v;
        sg.add(d[i][0], -1);
        sg.add(d[i][1], 1);
    }

    cout << res;

    return 0;
}
