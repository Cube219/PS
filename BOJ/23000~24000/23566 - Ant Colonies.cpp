#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;
constexpr int INF = 987654321;

struct SegTree
{
    struct Node
    {
        int v, mnpos, mxpos;

        int l, r, lidx, ridx;
        Node(int _l, int _r) :
            l(_l), r(_r), lidx(-1), ridx(-1), v(INF), mnpos(INF), mxpos(-1)
        {}
    };
    vector<Node> t;
    int n;

    void merge(Node& res, Node& l, Node& r)
    {
        res.v = min(l.v, r.v);
        if(l.mxpos != -1 && r.mnpos != INF) {
            res.v = min(res.v, l.r - l.mxpos + r.mnpos - r.l + 1);
        }

        res.mnpos = min(l.mnpos, r.mnpos);
        res.mxpos = max(l.mxpos, r.mxpos);

        res.l = l.l;
        res.r = r.r;
    }

    void init(int _n)
    {
        n = 1;
        while(n < _n) n *= 2;

        t.emplace_back(0, n - 1);
    }

    void updateImpl(int cl, int cr, int idx, int v, int node)
    {
        if(cl == cr) {
            if(v == 0) {
                t[node].mnpos = INF;
                t[node].mxpos = -1;
            } else {
                t[node].mnpos = cl;
                t[node].mxpos = cl;
            }
            return;
        }


        int m = (cl + cr) / 2;
        if(idx <= m) {
            if(t[node].lidx == -1) {
                t[node].lidx = t.size();
                t.emplace_back(cl, m);
            }
            updateImpl(cl, m, idx, v, t[node].lidx);
        } else {
            if(t[node].ridx == -1) {
                t[node].ridx = t.size();
                t.emplace_back(m + 1, cr);
            }
            updateImpl(m + 1, cr, idx, v, t[node].ridx);
        }

        Node lres = Node(cl, m);
        if(t[node].lidx != -1) lres = t[t[node].lidx];
        Node rres = Node(m + 1, cr);
        if(t[node].ridx != -1) rres = t[t[node].ridx];
        merge(t[node], lres, rres);
    }

    Node findImpl(int cl, int cr, int l, int r, int node)
    {
        if(l <= cl && cr <= r) return t[node];
        else if(cr < l || r < cl) return Node(cl, cr);

        Node& cur = t[node];

        int m = (cl + cr) / 2;
        Node lres = Node(cl, m);
        if(cur.lidx != -1) lres = findImpl(cl, m, l, r, cur.lidx);
        Node rres = Node(m + 1, cr);
        if(cur.ridx != -1) rres = findImpl(m + 1, cr, l, r, cur.ridx);

        Node res(cl, cr);
        merge(res, lres, rres);
        return res;
    }

    void update(int idx, int v)
    {
        updateImpl(0, n - 1, idx, v, 0);
    }

    Node find(int l, int r)
    {
        return findImpl(0, n - 1, l, r, 0);
    }
};

int n, m, a[100001];
vector<int> g[100001], g2[100001];
int par[100001], dep[100001], sz[100001], idx[100001], top[100001], num;
SegTree sg[100001];

void dfs0(int cur, int p)
{
    for(int nxt : g[cur]) {
        if(nxt == p) continue;

        dep[nxt] = dep[cur] + 1;
        par[nxt] = cur;
        g2[cur].push_back(nxt);
        dfs0(nxt, cur);
    }
}

int dfs1(int cur)
{
    sz[cur] = 1;
    for(int& nxt : g2[cur]) {
        sz[cur] += dfs1(nxt);
        if(sz[g2[cur][0]] < sz[nxt]) swap(g2[cur][0], nxt);
    }
    return sz[cur];
}

void hld(int cur)
{
    idx[cur] = num++;
    for(int nxt : g2[cur]) {
        if(g2[cur][0] == nxt) top[nxt] = top[cur];
        else top[nxt] = nxt;
        hld(nxt);
    }
}

int query(int u, int v, int c)
{
    auto& seg = sg[c];

    int res = INF;

    int ulen = INF, vlen = INF;

    while(top[u] != top[v]) {
        if(dep[top[u]] > dep[top[v]]) {
            auto r = seg.find(idx[top[u]], idx[u]);
            res = min(res, r.v);
            if(r.mxpos != -1) {
                res = min(res, idx[u] - r.mxpos + ulen + 1);
            }
            if(r.mnpos != INF) {
                ulen = r.mnpos - idx[top[u]];
            } else {
                ulen += idx[u] - idx[top[u]] + 1;
            }

            u = par[top[u]];
        } else {
            auto r = seg.find(idx[top[v]], idx[v]);
            res = min(res, r.v);
            if(r.mxpos != -1) {
                res = min(res, idx[v] - r.mxpos + vlen + 1);
            }
            if(r.mnpos != INF) {
                vlen = r.mnpos - idx[top[v]];
            } else {
                vlen += idx[v] - idx[top[v]] + 1;
            }

            v = par[top[v]];
        }
    }

    if(idx[u] > idx[v]) {
        swap(u, v);
        swap(ulen, vlen);
    }

    auto r = seg.find(idx[u], idx[v]);
    res = min(res, r.v);
    if(r.mnpos != INF) {
        res = min(res, ulen + r.mnpos - idx[u] + 1);
        res = min(res, vlen + idx[v] - r.mxpos + 1);
    } else {
        res = min(res, ulen + vlen + idx[v] - idx[u] + 2);
    }

    if(res == INF) res = -1;
    return res;
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;
    for(int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    for(int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    dfs0(0, -1);
    dfs1(0);
    hld(0);

    for(int i = 1; i <= n; ++i) {
        sg[i].init(n);
    }
    for(int i = 0; i < n; ++i) {
        sg[a[i]].update(idx[i], 1);
    }

    for(int i = 0; i < m; ++i) {
        char ch;
        cin >> ch;
        if(ch == 'U') {
            int num, c;
            cin >> num >> c;
            num--;
            sg[a[num]].update(idx[num], 0);
            sg[c].update(idx[num], 1);
            a[num] = c;
        } else {
            int u, v, c;
            cin >> u >> v >> c;
            u--; v--;

            cout << query(u, v, c) << "\n";
        }
    }

    return 0;
}
