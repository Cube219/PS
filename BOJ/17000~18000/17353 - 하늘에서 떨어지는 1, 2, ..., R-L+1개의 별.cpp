#define _CRT_SECURE_NO_WARNINGS 1

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
    ll t[N * 3], lazylr[N * 3], lazycnt[N * 3];
    int stLeaf, n;

    void init(int n, ll* pData)
    {
        stLeaf = 1;
        while(stLeaf < n) stLeaf *= 2;
        for(int i = 0; i < n; ++i) {
            if(pData == nullptr) t[stLeaf + i] = 0;
            else t[stLeaf + i] = pData[i];
        }
    }

    void propagate(int l, int r, int node)
    {
        if(lazycnt[node] == 0) return;

        if(node < stLeaf) {
            lazylr[node * 2] += lazylr[node];
            lazylr[node * 2 + 1] += lazylr[node];
            lazycnt[node * 2] += lazycnt[node];
            lazycnt[node * 2 + 1] += lazycnt[node];
        } else {
            t[node] += lazycnt[node] * l - lazylr[node];
        }
        lazylr[node] = 0;
        lazycnt[node] = 0;
    }

    ll findImpl(int cl, int cr, int l, int r, int node)
    {
        propagate(cl, cr, node);
        if(l <= cl && cr <= r) return t[node];
        else if(cr < l || r < cl) return 0;
        int m = (cl + cr) / 2;
        return findImpl(cl, m, l, r, node * 2) + findImpl(m + 1, cr, l, r, node * 2 + 1);
    }

    void addImpl(int cl, int cr, int l, int r, int node, ll v)
    {
        propagate(cl, cr, node);
        if(l <= cl && cr <= r) {
            lazylr[node] += v;
            lazycnt[node]++;
            propagate(cl, cr, node);
            return;
        } else if(cr < l || r < cl) return;
        int m = (cl + cr) / 2;
        addImpl(cl, m, l, r, node * 2, v);
        addImpl(m + 1, cr, l, r, node * 2 + 1, v);
    }

    ll find(int l, int r)
    {
        return findImpl(0, stLeaf - 1, l, r, 1);
    }

    void add(int l, int r, ll v)
    {
        addImpl(0, stLeaf - 1, l, r, 1, v);
    }
};


SegTree<100000> sg;
int n;
ll d[100001];

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for(int i = 0; i < n; ++i) {
        cin >> d[i];
    }
    sg.init(n, d);
    int m;
    cin >> m;
    for(int i = 0; i < m; ++i) {
        int a, b, c;
        cin >> a;
        if(a == 1) {
            cin >> b >> c;
            sg.add(b - 1, c - 1, b - 2);
        } else {
            cin >> b;
            cout << sg.find(b - 1, b - 1) << "\n";
        }
    }

    return 0;
}
