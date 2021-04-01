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
    int t[N * 3], lazy[N * 3];
    int stLeaf, n;

    void init(int n)
    {
        stLeaf = 1;
        while(stLeaf < n) stLeaf *= 2;
        for(int i = 0; i < n; ++i) {
            t[stLeaf + i] = 1;
        }
        for(int i = stLeaf - 1; i > 0; --i) {
            t[i] = 1;
        }
    }

    void propagate(int l, int r, int node)
    {
        if(lazy[node] == 0) return;

        if(node < stLeaf) {
            lazy[node * 2] = max(lazy[node * 2], lazy[node]);
            lazy[node * 2 + 1] = max(lazy[node * 2 + 1], lazy[node]);
        }
        t[node] = max(t[node], lazy[node]);
        lazy[node] = 0;
    }

    int findImpl(int cl, int cr, int l, int r, int node)
    {
        propagate(cl, cr, node);
        if(l <= cl && cr <= r) return t[node];
        else if(cr < l || r < cl) return 0;
        int m = (cl + cr) / 2;
        return findImpl(cl, m, l, r, node * 2) + findImpl(m + 1, cr, l, r, node * 2 + 1);
    }

    void addImpl(int cl, int cr, int l, int r, int node, int v)
    {
        propagate(cl, cr, node);
        if(l <= cl && cr <= r) {
            lazy[node] = max(lazy[node], v);
            propagate(cl, cr, node);
            return;
        } else if(cr < l || r < cl) return;
        int m = (cl + cr) / 2;
        addImpl(cl, m, l, r, node * 2, v);
        addImpl(m + 1, cr, l, r, node * 2 + 1, v);
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

SegTree<200001> sg;
int ed[200001];
int n, q;
int parent[200001];
vector<int> g[200001];
int cvt[200001];

int cnt;
void dfs(int cur, int p)
{
    cnt++;
    int newCur = cnt;
    cvt[cur] = newCur;
    for(int nxt : g[cur]) {
        if(nxt == p) continue;
        dfs(nxt, cur);
    }
    ed[newCur] = cnt;
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> q;
    parent[1] = 1;
    for(int i = 2; i <= n; ++i) {
        cin >> parent[i];
        g[parent[i]].push_back(i);
    }
    dfs(1, -1);
    sg.init(n + 1);

    for(int i = 0; i < q; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        int ap = sg.find(cvt[a], cvt[a]);
        int bp = sg.find(cvt[b], cvt[b]);
        if(ap == bp) cout << "YES\n";
        else cout << "NO\n";

        if(c == 1) {
            int tmp;
            if(ap == bp) {
                tmp = cvt[a];
            } else {
                tmp = cvt[b];
            }
            sg.add(tmp, ed[tmp], tmp);
        }
    }

    return 0;
}
