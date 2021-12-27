#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;
constexpr int INF = 0x3f3f3f3f;
constexpr ll LNF = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 1'000'000'007;

vector<int> cnt, cnum;

void change(int color, int num)
{
    if(color == 0) return;
    cnum[cnt[color]]--;
    cnt[color] += num;
    cnum[cnt[color]]++;
}

class SegTree
{
public:
    struct Node
    {
        int color = 0;
        bool isEnd = false;
    };
    vector<Node> t;
    int stLeaf, n;

    void init(int n)
    {
        stLeaf = 1;
        while(stLeaf < n) stLeaf *= 2;

        t.resize(stLeaf * 2, emptyNode);
    }

    void initv(int idx, Node v)
    {
        t[stLeaf + idx] = v;
    }

    void build()
    {
        t[1].isEnd = true;
    }

    void rm(int cl, int cr, int l, int r, int node)
    {
        if(cr < l || r < cl) return;
        if(t[node].isEnd) {
            change(t[node].color, -(cr - cl + 1));
            t[node].isEnd = false;
            return;
        }
        int m = (cl + cr) / 2;
        rm(cl, m, l, r, node * 2);
        rm(m + 1, cr, l, r, node * 2 + 1);
    }

    void aImpl(int cl, int cr, int l, int r, int color, int node)
    {
        if(cr < l || r < cl) return;
        if(l <= cl && cr <= r) {
            rm(cl, cr, l, r, node);
            t[node].isEnd = true;
            t[node].color = color;
            change(color, cr - cl + 1);
            return;
        }
        if(t[node].isEnd) {
            t[node].isEnd = false;
            t[node * 2].isEnd = true;
            t[node * 2].color = t[node].color;
            t[node * 2 + 1].isEnd = true;
            t[node * 2 + 1].color = t[node].color;
        }
        int m = (cl + cr) / 2;
        aImpl(cl, m, l, r, color, node * 2);
        aImpl(m + 1, cr, l, r, color, node * 2 + 1);
    }

    void apply(int st, int ed, int color)
    {
        aImpl(0, stLeaf - 1, st, ed, color, 1);
    }

    const Node emptyNode = { 0, false };
};


void solve()
{
    int n, c, q;
    cin >> n >> c >> q;
    vector<vector<int>> g(n);
    for(int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    vector<int> dep(n), sz(n), top(n), par(n), idx(n);
    vector<vector<int>> g2(n);
    int num = 0;

    dep[0] = 0;
    sz[0] = 0;
    auto dfs = [&](auto&& self, int cur, int p) -> void {
        for(int nxt : g[cur]) {
            if(nxt == p) continue;

            dep[nxt] = dep[cur] + 1;
            par[nxt] = cur;
            g2[cur].push_back(nxt);

            self(self, nxt, cur);
        }
    };
    dfs(dfs, 0, -1);
    auto dfs2 = [&](auto&& self, int cur) -> int {
        sz[cur] = 1;
        for(int& nxt : g2[cur]) {
            sz[cur] += self(self, nxt);

            if(sz[g2[cur][0]] < sz[nxt]) swap(g2[cur][0], nxt);
        }
        return sz[cur];
    };
    dfs2(dfs2, 0);

    SegTree sg;
    sg.init(n);
    top[0] = 0;
    auto hld = [&](auto&& self, int cur) -> void {
        idx[cur] = num++;
        for(int nxt : g2[cur]) {
            if(g2[cur][0] == nxt) top[nxt] = top[cur];
            else top[nxt] = nxt;
            self(self, nxt);
        }
    };
    hld(hld, 0);
    sg.build();

    auto query = [&](int u, int color) {
        while(top[u] != 0) {
            sg.apply(idx[top[u]], idx[u], color);
            u = par[top[u]];
        }
        if(idx[u] > 0) sg.apply(1, idx[u], color);
    };

    cnt.resize(c + 1, 0);
    cnum.resize(n + 1, 0);
    cnum[0] = c;
    for(int i = 0; i < q; ++i) {
        int u, c, m;
        cin >> u >> c >> m;
        u--;
        query(u, c);

        cout << cnum[m] << "\n";
    }
}

int main()
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int tNum = 1;
    // cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        solve();
    }

    return 0;
}
