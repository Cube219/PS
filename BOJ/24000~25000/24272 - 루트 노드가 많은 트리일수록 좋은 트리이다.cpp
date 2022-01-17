#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <unordered_map>
#include <vector>
using namespace std;

using ll = long long int;
constexpr int INF = 0x3f3f3f3f;
constexpr ll LNF = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 1'000'000'007;

class SegTree
{
public:
    struct Node
    {
        int mn, cnt;
    };
    vector<Node> t;
    vector<int> lazy;
    int stLeaf, n;

    SegTree(int n)
    {
        stLeaf = 1;
        while(stLeaf < n) stLeaf *= 2;

        t.resize(stLeaf * 2, emptyNode);
        lazy.resize(stLeaf * 2, 0);
    }

    void initv(int idx, int v)
    {
        t[stLeaf + idx].mn = v;
        t[stLeaf + idx].cnt = 1;
    }

    void build()
    {
        for(int i = stLeaf - 1; i > 0; --i) {
            t[i] = merge(t[i * 2], t[i * 2 + 1]);
        }
    }

    void propagate(int l, int r, int node)
    {
        if(lazy[node] == 0) return;

        if(node < stLeaf) {
            lazy[node * 2] += lazy[node];
            lazy[node * 2 + 1] += lazy[node];
        }
        t[node].mn += lazy[node];
        lazy[node] = 0;
    }

    Node findImpl(int cl, int cr, int l, int r, int node)
    {
        propagate(cl, cr, node);
        if(cr < l || r < cl) return emptyNode;
        if(l <= cl && cr <= r) return t[node];
        int m = (cl + cr) / 2;
        return merge(findImpl(cl, m, l, r, node * 2), findImpl(m + 1, cr, l, r, node * 2 + 1));
    }

    void addImpl(int cl, int cr, int l, int r, int node, int v)
    {
        propagate(cl, cr, node);
        if(cr < l || r < cl) return;
        if(l <= cl && cr <= r) {
            lazy[node] += v;
            propagate(cl, cr, node);
            return;
        }
        int m = (cl + cr) / 2;
        addImpl(cl, m, l, r, node * 2, v);
        addImpl(m + 1, cr, l, r, node * 2 + 1, v);
        t[node] = merge(t[node * 2], t[node * 2 + 1]);
    }

    Node find(int l, int r)
    {
        return findImpl(0, stLeaf - 1, l, r, 1);
    }

    void add(int l, int r, int v)
    {
        addImpl(0, stLeaf - 1, l, r, 1, v);
    }

    Node merge(Node l, Node r)
    {
        if(l.mn < r.mn) return l;
        else if(l.mn > r.mn) return r;

        return { l.mn, l.cnt + r.cnt };
    }

    const Node emptyNode = { INF, 0 };
};

void solve()
{
    int n;
    cin >> n;
    vector<vector<pair<int, int>>> g(n);
    for(int i = 0; i < n - 1; ++i) {
        int a, b, dir;
        string str;
        cin >> a >> str >> b;
        a--; b--;
        if(str[0] == '<') dir = -1;
        else if(str[1] == '>') dir = 1;
        else dir = 0;

        g[a].emplace_back(b, dir);
        g[b].emplace_back(a, -dir);
    }

    vector<int> st(n), ed(n), dep(n);
    unordered_map<ll, int> edges;
    int iNum = 0, invNum = 0;
    dep[0] = 0;
    auto dfs = [&](auto&& self, int cur, int pre) -> void {
        st[cur] = iNum++;

        for(auto [nxt, dir] : g[cur]) {
            if(nxt == pre) continue;

            if(dir == -1) invNum++;
            edges[(ll)cur << 32 | nxt] = dir;
            dep[nxt] = dep[cur] + 1;

            self(self, nxt, cur);
        }

        ed[cur] = iNum - 1;
    };
    dfs(dfs, 0, -1);

    SegTree sg(n);
    auto dfs2 = [&](auto&& self, int cur, int pre, int change) -> void {
        sg.initv(st[cur], invNum + change);
        for(auto [nxt, dir] : g[cur]) {
            if(nxt == pre) continue;

            self(self, nxt, cur, change + dir);
        }
    };
    dfs2(dfs2, 0, -1, 0);
    sg.build();

    int q;
    cin >> q;
    for(int i = 0; i < q; ++i) {
        int a, b, dir;
        string str;
        cin >> a >> str >> b;
        a--; b--;
        if(str[0] == '<') dir = -1;
        else if(str[1] == '>') dir = 1;
        else dir = 0;
        if(dep[a] > dep[b]) {
            swap(a, b);
            dir *= -1;
        }

        ll key = (ll)a << 32 | b;
        int oldDir = edges[key];
        if(oldDir == -1) {
            if(dir == 0) {
                if(st[b] > 0) sg.add(0, st[b] - 1, -1);
                if(ed[b] < n - 1) sg.add(ed[b] + 1, n - 1, -1);
            } else if(dir == 1) {
                if(st[b] > 0) sg.add(0, st[b] - 1, -1);
                if(ed[b] < n - 1) sg.add(ed[b] + 1, n - 1, -1);
                sg.add(st[b], ed[b], 1);
            }
        } else if(oldDir == 1) {
            if(dir == -1) {
                if(st[b] > 0) sg.add(0, st[b] - 1, 1);
                if(ed[b] < n - 1) sg.add(ed[b] + 1, n - 1, 1);
                sg.add(st[b], ed[b], -1);
            } else if(dir == 0) {
                sg.add(st[b], ed[b], -1);
            }
        } else {
            // oldDir == 0
            if(dir == -1) {
                if(st[b] > 0) sg.add(0, st[b] - 1, 1);
                if(ed[b] < n - 1) sg.add(ed[b] + 1, n - 1, 1);
            } else if(dir == 1) {
                sg.add(st[b], ed[b], 1);
            }
        }
        edges[key] = dir;

        auto r = sg.find(0, n - 1);
        if(r.mn > 0) cout << "0\n";
        else cout << r.cnt << "\n";
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
