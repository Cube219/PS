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
    ll t[N * 3], lazy[N * 3];
    int stLeaf, n;

    void init(int n)
    {
        stLeaf = 1;
        while(stLeaf < n) stLeaf *= 2;
    }
    void initValue(int idx, ll v)
    {
        t[stLeaf + idx] = v;
    }
    void init2()
    {
        for(int i = stLeaf - 1; i > 0; --i) {
            t[i] = t[i * 2] + t[i * 2 + 1];
        }
    }

    void propagate(int l, int r, int node)
    {
        if(lazy[node] == 0) return;

        if(node < stLeaf) {
            lazy[node * 2] += lazy[node];
            lazy[node * 2 + 1] += lazy[node];
        }
        t[node] += (r - l + 1) * lazy[node];
        lazy[node] = 0;
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
            lazy[node] += v;
            propagate(cl, cr, node);
            return;
        } else if(cr < l || r < cl) return;
        int m = (cl + cr) / 2;
        addImpl(cl, m, l, r, node * 2, v);
        addImpl(m + 1, cr, l, r, node * 2 + 1, v);
        t[node] = t[node * 2] + t[node * 2 + 1];
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
SegTree<100001> sg;

int n, m;
vector<int> g[100001];
int parent[100001], sz[100001];

vector<vector<int>> chList;
int ch[100001], chIdx[100001];
int chFirst[100001], chDepth[100001], num;

int dfs(int cur, int p)
{
    parent[cur] = p;
    sz[cur] = 1;
    for(int nxt : g[cur]) {
        if(nxt == p) continue;
        sz[cur] += dfs(nxt, cur);
    }
    return sz[cur];
}

void hld(int cur, int p, int dep)
{
    ch[cur] = chList.size() - 1;
    chIdx[cur] = chList.back().size();
    chList.back().push_back(cur);
    num++;

    int hv = -1, hvIdx = 0;
    for(int nxt : g[cur]) {
        if(nxt == p) continue;
        if(hv < sz[nxt]) {
            hv = sz[nxt];
            hvIdx = nxt;
        }
    }
    if(hv != -1) {
        hld(hvIdx, cur, dep);
    }
    for(int nxt : g[cur]) {
        if(nxt == p || nxt == hvIdx) continue;
        chList.push_back({});
        chDepth[chList.size() - 1] = dep + 1;
        chFirst[chList.size() - 1] = num;
        hld(nxt, cur, dep + 1);
    }
}

void add(int a, int b)
{
    int chA = ch[a];
    int chB = ch[b];
    while(chA != chB) {
        if(chDepth[chA] > chDepth[chB]) {
            int chBeg = chFirst[chA];
            sg.add(chBeg, chBeg + chIdx[a], 1);
            a = parent[chList[chA][0]];
            chA = ch[a];
        } else {
            int chBeg = chFirst[chB];
            sg.add(chBeg, chBeg + chIdx[b], 1);
            b = parent[chList[chB][0]];
            chB = ch[b];
        }
    }
    int st = chIdx[a];
    int ed = chIdx[b];
    if(st > ed) swap(st, ed);
    int chBeg = chFirst[chA];
    if(st < ed) {
        sg.add(chBeg + st + 1, chBeg + ed, 1);
    }
}

ll find(int a, int b)
{
    ll ret = 0;

    int chA = ch[a];
    int chB = ch[b];
    while(chA != chB) {
        if(chDepth[chA] > chDepth[chB]) {
            int chBeg = chFirst[chA];
            ret += sg.find(chBeg, chBeg + chIdx[a]);
            a = parent[chList[chA][0]];
            chA = ch[a];
        } else {
            int chBeg = chFirst[chB];
            ret += sg.find(chBeg, chBeg + chIdx[b]);
            b = parent[chList[chB][0]];
            chB = ch[b];
        }
    }
    int st = chIdx[a];
    int ed = chIdx[b];
    if(st > ed) swap(st, ed);
    int chBeg = chFirst[chA];
    if(st < ed) {
        ret += sg.find(chBeg + st + 1, chBeg + ed);
    }
    return ret;
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;
    sg.init(n);
    for(int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    dfs(1, -1);
    chList.push_back({});
    hld(1, -1, 0);

    sg.init2();

    for(int i = 0; i < m; ++i) {
        char a;
        int b, c;
        cin >> a >> b >> c;
        if(a == 'P') {
            add(b, c);
        } else {
            cout << find(b, c) << "\n";
        }
    }

    return 0;
}
