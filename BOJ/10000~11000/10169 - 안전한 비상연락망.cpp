#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;
constexpr ll INF = 9999999999999999;

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
        for(int i = 0; i < stLeaf; ++i) {
            t[stLeaf + i] = INF;
            lazy[i] = INF;
            lazy[stLeaf + i] = INF;
        }
    }

    void initv(int idx, int v)
    {
        t[stLeaf + idx] = v;
    }

    void build()
    {
        for(int i = stLeaf - 1; i > 0; --i) {
            t[i] = min(t[i * 2],t[i * 2 + 1]);
        }
    }

    void propagate(int l, int r, int node)
    {
        if(lazy[node] == INF) return;

        if(node < stLeaf) {
            lazy[node * 2] = min(lazy[node * 2], lazy[node]);
            lazy[node * 2 + 1] = min(lazy[node * 2 + 1], lazy[node]);
        }
        t[node] = min(t[node], lazy[node]);
        lazy[node] = INF;
    }

    ll findImpl(int cl, int cr, int l, int r, int node)
    {
        propagate(cl, cr, node);
        if(l <= cl && cr <= r) return t[node];
        else if(cr < l || r < cl) return INF;
        int m = (cl + cr) / 2;
        return min(findImpl(cl, m, l, r, node * 2), findImpl(m + 1, cr, l, r, node * 2 + 1));
    }

    void addImpl(int cl, int cr, int l, int r, int node, ll v)
    {
        propagate(cl, cr, node);
        if(l <= cl && cr <= r) {
            lazy[node] = min(lazy[node], v);
            propagate(cl, cr, node);
            return;
        } else if(cr < l || r < cl) return;
        int m = (cl + cr) / 2;
        addImpl(cl, m, l, r, node * 2, v);
        addImpl(m + 1, cr, l, r, node * 2 + 1, v);
        t[node] = min(t[node * 2],+ t[node * 2 + 1]);
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
    vector<pair<int, ll>>* g;
    SegTree<N>* sg;
    int num;
    int segToIdx[N];

    void init(vector<pair<int, ll>>* _g, SegTree<N>* _sg, int _n)
    {
        g = _g;
        sg = _sg;
        num = 0;

        _dfs(0, -1, 0);
        ch.push_back({ 0, 0, {} });
        _sg->init(_n);
        _hld(0, -1, 0);
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
        segToIdx[num] = node[cur].cost;
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

    void process(int a, int b, ll cost)
    {
        int ach = node[a].ch;
        int bch = node[b].ch;
        while(ach != bch) {
            if(ch[ach].dep > ch[bch].dep) {
                sg->add(ch[ach].begInSeg, ch[ach].begInSeg + node[a].idxInCh, cost);
                a = node[ch[ach].node[0]].par;
                ach = node[a].ch;
            } else {
                sg->add(ch[bch].begInSeg, ch[bch].begInSeg + node[b].idxInCh, cost);
                b = node[ch[bch].node[0]].par;
                bch = node[b].ch;
            }
        }
        int st = node[a].idxInCh;
        int ed = node[b].idxInCh;
        if(st > ed) swap(st, ed);
        if(st < ed) sg->add(ch[ach].begInSeg + st + 1, ch[ach].begInSeg + ed, cost);
    }
};


struct Edge
{
    int u, v, idx;
    ll cost;
};

vector<pair<int, ll>> g[100001];
int n, m;
Edge eg[300001];
bool use[300001];
int par[300001], num;
ll cost;
SegTree<100001> sg;
HLD<100001> hld;
ll res[300001];

int find(int a)
{
    vector<int> st;
    while(a != par[a]) {
        st.push_back(a);
        a = par[a];
    }
    for(int i = 0; i < st.size(); ++i) {
        par[st[i]] = a;
    }
    return a;
}
void uni(int a, int b)
{
    int ar = find(a);
    int br = find(b);
    if(ar == br) return;
    par[ar] = br;
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;
    for(int i = 0; i < m; ++i) {
        int u, v, c;
        cin >> u >> v >> c;
        u--; v--;
        eg[i] = { u, v, i, c };
    }
    for(int i = 0; i < n; ++i) {
        par[i] = i;
    }
    sort(eg, eg + m, [](const Edge& l, const Edge& r) {
        return l.cost < r.cost;
    });
    for(int i = 0; i < m; ++i) {
        int u = eg[i].u;
        int v = eg[i].v;
        if(find(u) != find(v)) {
            uni(u, v);
            cost += eg[i].cost;
            num++;
            use[eg[i].idx] = true;
            g[u].push_back({ v, eg[i].idx });
            g[v].push_back({ u, eg[i].idx });
            if(num == n - 1) break;
        }
    }
    hld.init(g, &sg, n);
    for(int i = 0; i < m; ++i) {
        if(use[eg[i].idx] == true) continue;
        hld.process(eg[i].u, eg[i].v, eg[i].cost);
    }
    for(int i = 1; i < n; ++i) {
        ll v = sg.find(i, i);
        res[hld.segToIdx[i]] = v;
    }
    sort(eg, eg + m, [](const Edge& l, const Edge& r) {
        return l.idx < r.idx;
    });
    for(int i = 0; i < m; ++i) {
        if(use[i] == false) {
            cout << cost << "\n";
        } else {
            if(res[i] == INF) cout << "-1\n";
            else {
                cout << cost - eg[i].cost + res[i] << "\n";
            }
        }
    }

    return 0;
}
