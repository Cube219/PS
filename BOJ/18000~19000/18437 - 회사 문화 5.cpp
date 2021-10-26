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
    int t[N * 3], lazy[N * 3];
    int stLeaf, n;

    void init(int n)
    {
        stLeaf = 1;
        while(stLeaf < n) stLeaf *= 2;

        for(int i = 1; i < n; ++i) {
            t[stLeaf + i] = 1;
        }
        for(int i = stLeaf; i >= 0; --i) {
            t[i] = t[i * 2] + t[i * 2 + 1];
        }
    }

    void propagate(int l, int r, int node)
    {
        if(lazy[node] == 0) return;

        if(node < stLeaf) {
            lazy[node * 2] = lazy[node];
            lazy[node * 2 + 1] = lazy[node];
        }
        if(lazy[node] == 1) t[node] = (r - l + 1);
        else t[node] = 0;

        lazy[node] = 0;
    }

    int findImpl(int cl, int cr, int l, int r, int node)
    {
        propagate(cl, cr, node);
        if(cr < l || r < cl) return 0;
        if(l <= cl && cr <= r) return t[node];
        int m = (cl + cr) / 2;
        return findImpl(cl, m, l, r, node * 2) + findImpl(m + 1, cr, l, r, node * 2 + 1);
    }

    void addImpl(int cl, int cr, int l, int r, int node, int v)
    {
        propagate(cl, cr, node);
        if(cr < l || r < cl) return;
        if(l <= cl && cr <= r) {
            lazy[node] = v;
            propagate(cl, cr, node);
            return;
        }
        int m = (cl + cr) / 2;
        addImpl(cl, m, l, r, node * 2, v);
        addImpl(m + 1, cr, l, r, node * 2 + 1, v);
        t[node] = t[node * 2] + t[node * 2 + 1];
    }

    int find(int l, int r)
    {
        return findImpl(0, stLeaf - 1, l, r, 1);
    }

    void add(int l, int r, int v)
    {
        addImpl(0, stLeaf - 1, l, r, 1, v);
    }
};

int n, m;
vector<int> g[100001];
int st[100001], ed[100001], num;
SegTree<100002> sg;

void dfs(int cur)
{
    st[cur] = num++;
    for(int nxt : g[cur]) {
        dfs(nxt);
    }
    ed[cur] = num - 1;
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for(int i = 1; i <= n; ++i) {
        int p;
        cin >> p;
        g[p].push_back(i);
    }

    dfs(1);
    sg.init(n + 1);

    cin >> m;
    for(int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        if(a == 1) {
            sg.add(st[b] + 1, ed[b], 1);
        } else if(a == 2) {
            sg.add(st[b] + 1, ed[b], -1);
        } else {
            cout << sg.find(st[b] + 1, ed[b]) << "\n";
        }
    }

    return 0;
}
