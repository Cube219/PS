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
    ll t[N * 3];
    ll lgap[N * 3], lst[N * 3], rgap[N * 3], rst[N * 3];
    int stLeaf, n;

    void init(int n)
    {
        stLeaf = 1;
        while(stLeaf < n) stLeaf *= 2;
    }

    void initv(int idx, int v)
    {
        t[stLeaf + idx] = v;
    }

    void build()
    {
    }

    void propagate(int l, int r, int node)
    {
        if(lgap[node] == 0 && rgap[node] == 0) return;
        ll sz = r - l + 1;

        if(node < stLeaf) {
            int lnode = node * 2;
            int rnode = node * 2 + 1;

            lgap[lnode] += lgap[node];
            lgap[rnode] += lgap[node];
            lst[lnode] += lst[node];
            lst[rnode] += lst[node] + sz / 2 * lgap[node];

            rgap[lnode] += rgap[node];
            rgap[rnode] += rgap[node];
            rst[lnode] += rst[node] + sz / 2 * rgap[node];
            rst[rnode] += rst[node];
        } else {
            t[node] += lst[node];
            t[node] += rst[node];
        }

        lgap[node] = 0;
        rgap[node] = 0;
        lst[node] = 0;
        rst[node] = 0;
    }

    ll findImpl(int cl, int cr, int l, int r, int node)
    {
        propagate(cl, cr, node);
        if(cr < l || r < cl) return 0;
        if(l <= cl && cr <= r) return t[node];
        int m = (cl + cr) / 2;
        return findImpl(cl, m, l, r, node * 2) + findImpl(m + 1, cr, l, r, node * 2 + 1);
    }

    template <bool isNeg>
    void addImpl(int cl, int cr, int l, int r, int node, ll v)
    {
        propagate(cl, cr, node);
        if(cr < l || r < cl) return;
        if(l <= cl && cr <= r) {
            if(isNeg == true) {
                rgap[node]++;
                if(r <= cr) {
                    rst[node] += v;
                } else {
                    rst[node] += v + (r - cr);
                }
            } else {
                lgap[node]++;
                if(cl <= l) {
                    lst[node] += v;
                } else {
                    lst[node] += v + (cl - l);
                }
            }

            propagate(cl, cr, node);
            return;
        }
        int m = (cl + cr) / 2;
        addImpl<isNeg>(cl, m, l, r, node * 2, v);
        addImpl<isNeg>(m + 1, cr, l, r, node * 2 + 1, v);
        t[node] = t[node * 2] + t[node * 2 + 1];
    }

    ll find(int l, int r)
    {
        return findImpl(0, stLeaf - 1, l, r, 1);
    }

    template <bool isNeg>
    void add(int l, int r, ll v)
    {
        addImpl<isNeg>(0, stLeaf - 1, l, r, 1, v);
    }
};

SegTree<100001> sg;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    vector<vector<int>> g(n), g2(n);
    for(int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    vector<int> dep(n), sz(n), top(n), par(n), idx(n);
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

    auto query = [&](int a, int b) {
        vector<int> ast, aed, bst, bed;

        while(top[a] != top[b]) {
            if(dep[top[a]] > dep[top[b]]) {
                ast.push_back(idx[top[a]]);
                aed.push_back(idx[a]);
                a = par[top[a]];
            } else {
                bst.push_back(idx[top[b]]);
                bed.push_back(idx[b]);
                b = par[top[b]];
            }
        }

        if(idx[a] > idx[b]) {
            ast.push_back(idx[b]);
            aed.push_back(idx[a]);
        } else {
            bst.push_back(idx[a]);
            bed.push_back(idx[b]);
        }

        int num = 0;
        for(int i = 0; i < ast.size(); ++i) {
            sg.add<true>(ast[i], aed[i], num);
            num += aed[i] - ast[i] + 1;
        }
        for(int i = bst.size() - 1; i >= 0; --i) {
            sg.add<false>(bst[i], bed[i], num);
            num += bed[i] - bst[i] + 1;
        }
    };

    int q;
    cin >> q;
    for(int i = 0; i < q; ++i) {
        int t, a, b;
        cin >> t;
        if(t == 1) {
            cin >> a >> b;
            a--; b--;
            query(a, b);
        } else {
            cin >> a;
            a--;
            cout << sg.find(idx[a], idx[a]) << "\n";
        }
    }

    return 0;
}
