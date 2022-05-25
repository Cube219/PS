#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <cassert>
#include <numeric>
#include <vector>
#include <set>
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
        int idx, lessNum, mx;
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
        t[stLeaf + idx].idx = v;
        t[stLeaf + idx].mx = v + 1;
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
        t[node].lessNum += lazy[node];
        t[node].mx -= lazy[node];
        lazy[node] = 0;
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

    void add(int l, int r, int v)
    {
        addImpl(0, stLeaf - 1, l, r, 1, v);
    }

    void update(int idx, int v)
    {
        int node = 1, cl = 0, cr = stLeaf - 1;
        while(cl < cr) {
            propagate(cl, cr, node);
            int m = (cl + cr) / 2;
            if(idx <= m) {
                node = node * 2;
                cr = m;
            } else {
                node = node * 2 + 1;
                cl = m + 1;
            }
        }
        propagate(cl, cr, node);
        t[node].idx = v;
        t[node].mx = t[node].idx - t[node].lessNum + 1;

        node >>= 1;
        while(node > 0) {
            propagate(0, 0, node * 2);
            propagate(0, 0, node * 2 + 1);
            t[node] = merge(t[node * 2], t[node * 2 + 1]);
            node >>= 1;
        }
    }

    Node merge(Node l, Node r)
    {
        return { 0, 0, max(l.mx, r.mx) };
    }

    const Node emptyNode = { -INF, 0, -INF };
};


void solve()
{
    int n, qNum;
    cin >> n >> qNum;
    vector<int> vv, a(n);
    for(auto& v : a) {
        cin >> v;
        vv.push_back(v);
    }
    struct Query
    {
        int v, idx;
    };
    vector<Query> ql(qNum);
    for(auto& q : ql) {
        cin >> q.idx >> q.v;
        vv.push_back(q.v);
    }

    sort(vv.begin(), vv.end());
    vv.erase(unique(vv.begin(), vv.end()), vv.end());
    auto getv = [&](int v) -> int { return lower_bound(vv.begin(), vv.end(), v) - vv.begin(); };
    for(auto& v : a) v = getv(v);
    for(auto& q : ql) q.v = getv(q.v);

    SegTree sg(vv.size());
    vector<set<int>> idxList(vv.size());
    for(int i = 0; i < n; ++i) {
        idxList[a[i]].insert(-i);
    }
    for(int i = 0; i < vv.size(); ++i) {
        if(idxList[i].size() == 0) continue;
        sg.initv(i, *idxList[i].begin() * -1);
    }
    sg.build();
    for(int i = 0; i < n; ++i) {
        sg.add(a[i], vv.size() - 1, 1);
    }

    for(auto [v, idx] : ql) {
        int oldv = a[idx];

        int preMxIdx = *idxList[oldv].begin() * -1;
        idxList[oldv].erase(-idx);
        if(idxList[oldv].size() == 0) {
            sg.update(oldv, -INF);
        } else {
            int curMxIdx = *idxList[oldv].begin() * -1;
            if(preMxIdx != curMxIdx) sg.update(oldv, curMxIdx);
        }

        a[idx] = v;
        if(idxList[v].size() == 0) {
            sg.update(v, idx);
            idxList[v].insert(-idx);
        } else {
            preMxIdx = *idxList[v].begin() * -1;
            idxList[v].insert(-idx);
            int curMnIdx = *idxList[v].begin() * -1;
            if(preMxIdx != curMnIdx) sg.update(v, curMnIdx);
        }

        if(oldv < v) {
            sg.add(oldv, v - 1, -1);
        } else if(oldv > v) {
            sg.add(v, oldv - 1, 1);
        }

        cout << sg.t[1].mx << "\n";
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
