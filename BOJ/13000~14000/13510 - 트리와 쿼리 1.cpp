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
    void initadd(int v, int idx)
    {
        t[stLeaf + idx] = v;
    }
    void init2()
    {
        for(int i = stLeaf - 1; i > 0; --i) {
            t[i] = max(t[i * 2], t[i * 2 + 1]);
        }
    }

    int findImpl(int cl, int cr, int l, int r, int node)
    {
        if(l <= cl && cr <= r) return t[node];
        else if(cr < l || r < cl) return 0;
        int m = (cl + cr) / 2;
        return max(findImpl(cl, m, l, r, node * 2), findImpl(m + 1, cr, l, r, node * 2 + 1));
    }

    int find(int l, int r)
    {
        return findImpl(0, stLeaf - 1, l, r, 1);
    }

    void update(int l, int v)
    {
        t[stLeaf + l] = v;
        int node = stLeaf + l;
        node /= 2;
        while(node > 0) {
            t[node] = max(t[node * 2], t[node * 2 + 1]);
            node /= 2;
        }
    }
};

SegTree<100001> sg;

int n, q;
pair<int, int> edge[100001];
vector<pair<int, int>> g[100001];
int par[100001], sz[100001], cost[100001], depth[100001];
vector<vector<int>> chList;
int ch[100001], chIdx[100001];
int chBegin[100001], chDepth[100001], num;

int dfs(int cur, int p, int dep)
{
    par[cur] = p;
    depth[cur] = dep;
    for(auto& nx : g[cur]) {
        int nxt = nx.first;
        if(nxt == p) continue;
        sz[cur] += dfs(nxt, cur, dep + 1);
        cost[nxt] = nx.second;
    }
    sz[cur]++;
    return sz[cur];
}

void hld(int cur, int p, int depth)
{
    ch[cur] = chList.size() - 1;
    chIdx[cur] = chList.back().size();
    chList.back().push_back(cur);
    sg.initadd(cost[cur], num);
    num++;

    int hv = -1;
    int hvIdx = -1;
    for(auto& nx : g[cur]) {
        int nxt = nx.first;
        if(nxt == p) continue;
        if(hv < sz[nxt]) {
            hv = sz[nxt];
            hvIdx = nxt;
        }
    }
    if(hv != -1) {
        hld(hvIdx, cur, depth);
    }
    for(auto& nx : g[cur]) {
        int nxt = nx.first;
        if(nxt == p || nxt == hvIdx) continue;
        chList.push_back({});
        chBegin[chList.size() - 1] = num;
        chDepth[chList.size() - 1] = depth + 1;
        hld(nxt, cur, depth + 1);
    }
}

int process(int a, int b)
{
    int ret = -1;
    int aCh = ch[a];
    int bCh = ch[b];
    while(aCh != bCh) {
        if(chDepth[aCh] > chDepth[bCh]){
            int r = sg.find(chBegin[aCh], chBegin[aCh] + chIdx[a]);
            ret = max(ret, r);
            a = par[chList[aCh][0]];
            aCh = ch[a];
        } else {
            int r = sg.find(chBegin[bCh], chBegin[bCh] + chIdx[b]);
            ret = max(ret, r);
            b = par[chList[bCh][0]];
            bCh = ch[b];
        }
    }
    int st = chIdx[a];
    int ed = chIdx[b];
    if(st > ed) swap(st, ed);
    int r = 0;
    if(st < ed) r = sg.find(chBegin[aCh] + st + 1, chBegin[aCh] + ed);
    ret = max(ret, r);

    return ret;
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    sg.init(n);
    for(int i = 0; i < n - 1; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        g[a].push_back({ b, c });
        g[b].push_back({ a, c });
        edge[i] = { a, b };
    }
    dfs(1, -1, 0);
    chList.push_back({});
    hld(1, -1, 0);
    sg.init2();
    cin >> q;
    for(int i = 0; i < q; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        if(a == 1) {
            int e1 = edge[b - 1].first;
            int e2 = edge[b - 1].second;
            if(depth[e1] > depth[e2]) swap(e1, e2);
            b = e2;
            int cc = ch[b];
            int ci = chIdx[b];
            sg.update(chBegin[cc] + ci, c);
        } else {
            cout << process(b, c) << "\n";
        }
    }

    return 0;
}
