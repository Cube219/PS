#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
#include <map>
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

int n, q;
vector<int> g[100001];
int id[100001], idnum;
int st[100001], ed[100001];
map<int, int> color[100001];

void dfs(int cur, int par)
{
    st[cur] = idnum;
    id[cur] = idnum++;
    for(int nxt : g[cur]) {
        if(nxt == par) continue;
        dfs(nxt, cur);
    }
    ed[cur] = idnum - 1;
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> q;
    for(int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    sg.init(n);
    dfs(0, -1);

    for(int i = 0; i < q; ++i) {
        int a;
        cin >> a;
        if(a == 1) {
            int b, c;
            cin >> b >> c;
            b--;
            auto it = color[c].lower_bound(st[b]);
            if(it != color[c].end() && it->second <= st[b]) continue;
            while(it != color[c].end() && it->first <= ed[b]) {
                sg.add(it->second, it->first, -1);
                color[c].erase(it++);
            }

            color[c].insert({ ed[b], st[b] });
            sg.add(st[b], ed[b], 1);
        } else {
            int b;
            cin >> b;
            b--;
            cout << sg.find(st[b], ed[b]) << "\n";
        }
    }

    return 0;
}
