#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

constexpr int INF = 600000;

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
        for(int i = 0; i < stLeaf; ++i) {
            t[stLeaf + i] = INF;
            t[i] = INF;
        }
    }

    int findImpl(int cl, int cr, int l, int r, int node)
    {
        if(l <= cl && cr <= r) return t[node];
        else if(cr < l || r < cl) return INF;
        int m = (cl + cr) / 2;
        return min(findImpl(cl, m, l, r, node * 2), findImpl(m + 1, cr, l, r, node * 2 + 1));
    }

    int find(int l, int r)
    {
        return findImpl(0, stLeaf - 1, l, r, 1);
    }

    void add(int l, int v)
    {
        int node = stLeaf + l;
        t[node] = min(t[node], v);
        node /= 2;
        while(node > 0) {
            t[node] = min(t[node * 2], t[node * 2 + 1]);
            node /= 2;
        }
    }
};


struct Node
{
    int a, b, c;
};

int n;
Node d[500001];
SegTree<500001> sg;
int res;

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for(int i = 0; i < n; ++i) {
        int a;
        cin >> a;
        d[a - 1].a = i;
    }
    for(int i = 0; i < n; ++i) {
        int b;
        cin >> b;
        d[b - 1].b = i;
    }
    for(int i = 0; i < n; ++i) {
        int c;
        cin >> c;
        d[c - 1].c = i;
    }
    sort(d, d + n, [](const auto& l, const auto& r) {
        return l.a < r.a;
    });
    sg.init(n);

    for(int i = 0; i < n; ++i) {
        int v = sg.find(0, d[i].b - 1);
        if(v == INF || d[i].c < v) {
            res++;
        }
        sg.add(d[i].b, d[i].c);
    }

    cout << res;

    return 0;
}
