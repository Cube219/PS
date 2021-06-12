#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;
constexpr ll INF = 999999999999999999;

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
        for(int i = 0; i < stLeaf; ++i) {
            t[stLeaf + i] = INF;
        }
    }

    void initv(int idx, ll v)
    {
        t[stLeaf + idx] = v;
    }

    void build()
    {
        for(int i = stLeaf - 1; i > 0; --i) {
            t[i] = min(t[i * 2], t[i * 2 + 1]);
        }
    }

    ll findImpl(int cl, int cr, int l, int r, int node)
    {
        if(l <= cl && cr <= r) return t[node];
        else if(cr < l || r < cl) return INF;
        int m = (cl + cr) / 2;
        return min(findImpl(cl, m, l, r, node * 2), findImpl(m + 1, cr, l, r, node * 2 + 1));
    }
    ll find(int l, int r)
    {
        return findImpl(0, stLeaf - 1, l, r, 1);
    }
};

template <int N>
struct HLD
{
    struct Chain
    {
        int begInSeg, dep;
        vector<int> node;
    };

    struct Node
    {
        int sz, par, cost, dep;
        int ch, idxInCh;
    };

    vector<Chain> ch;
    Node node[N];
    vector<pair<int, int>>* g;
    ll* d;
    SegTree<N>* sg;
    int num;

    void init(vector<pair<int, int>>* _g, SegTree<N>* _sg, ll* _d, int _n, int root)
    {
        g = _g;
        sg = _sg;
        num = 0;
        d = _d;

        _dfs(root, -1, 0);
        ch.push_back({ 0, 0, {} });
        _sg->init(_n);
        _hld(root, -1, 0);
        _sg->build();
    }

    int _dfs(int cur, int par, int dep)
    {
        node[cur].par = par;
        node[cur].dep = dep;
        for(auto& nx : g[cur]) {
            int nxt = nx.first;
            if(nxt == par) continue;
            node[cur].sz += _dfs(nxt, cur, dep + 1);
            node[nxt].cost = nx.second;
        }
        node[cur].sz++;
        return node[cur].sz;
    }

    void _hld(int cur, int par, int dep)
    {
        node[cur].ch = ch.size() - 1;
        node[cur].idxInCh = ch.back().node.size();
        ch.back().node.push_back(cur);
        sg->initv(num, d[cur]);
        num++;

        int hv = 0;
        int hidx = -1;
        for(auto& nx : g[cur]) {
            int nxt = nx.first;
            if(nxt == par) continue;
            if(hv < node[nxt].sz) {
                hv = node[nxt].sz;
                hidx = nxt;
            }
        }
        if(hidx != -1) {
            _hld(hidx, cur, dep);
        }
        for(auto& nx : g[cur]) {
            int nxt = nx.first;
            if(nxt == par || nxt == hidx) continue;
            ch.push_back({ num, dep + 1, {} });
            _hld(nxt, cur, dep + 1);
        }
    }

    ll process(int a, int b)
    {
        ll res = INF;
        int ach = node[a].ch;
        int bch = node[b].ch;
        while(ach != bch) {
            if(ch[ach].dep > ch[bch].dep) {
                ll r = sg->find(ch[ach].begInSeg, ch[ach].begInSeg + node[a].idxInCh);
                res = min(res, r);
                a = node[ch[ach].node[0]].par;
                ach = node[a].ch;
            } else {
                ll r = sg->find(ch[bch].begInSeg, ch[bch].begInSeg + node[b].idxInCh);
                res = min(res, r);
                b = node[ch[bch].node[0]].par;
                bch = node[b].ch;
            }
        }
        int st = node[a].idxInCh;
        int ed = node[b].idxInCh;
        if(st > ed) swap(st, ed);
        ll r = INF;
        r = sg->find(ch[ach].begInSeg + st, ch[ach].begInSeg + ed);
        res = min(res, r);
        return res;
    }
};

struct Edge
{
    int u, v;
};

bool isshop[100001];

int n, s, q, e;
Edge eg[100001];
vector<pair<int, int>> g[100001];
SegTree<100001> sg;
int nodenum[100001], ed[100001], depth[100001], num;
ll d[100001], cost[100001];
HLD<100001> hld;

ll dfs(int cur, int par, int dep, ll curcost)
{
    nodenum[cur] = num++;
    d[cur] = INF;
    depth[cur] = dep;
    cost[cur] = curcost;
    if(isshop[cur] == true) d[cur] = 0;
    for(auto& nx : g[cur]) {
        int nxt = nx.first;
        int cost = nx.second;
        if(nxt == par) continue;
        d[cur] = min(d[cur], dfs(nxt, cur, dep + 1, curcost + cost) + cost);
    }
    ed[cur] = num - 1;
    d[cur] -= curcost;
    return d[cur] + curcost;
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> s >> q >> e;
    for(int i = 0; i < n - 1; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        eg[i] = { a, b };
        g[a].push_back({ b, c });
        g[b].push_back({ a, c });
    }
    for(int i = 0; i < s; ++i) {
        int a;
        cin >> a;
        isshop[a] = true;
    }
    dfs(e, -1, 0, 0);

    hld.init(g, &sg, d, n, e);

    for(int i = 0; i < q; ++i) {
        int a, b;
        cin >> a >> b;
        a--;
        int cutroot;
        if(depth[eg[a].u] > depth[eg[a].v]) {
            cutroot = eg[a].u;
        } else {
            cutroot = eg[a].v;
        }
        if(nodenum[cutroot] <= nodenum[b] && nodenum[b] <= ed[cutroot]) {
            ll v = hld.process(b, cutroot) + cost[b];
            if(v > 100000000000000) {
                cout << "oo\n";
            } else {
                cout << v << "\n";
            }
        } else {
            cout << "escaped\n";
        }
    }

    return 0;
}
