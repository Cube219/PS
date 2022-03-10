#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <numeric>
#include <vector>
using namespace std;

using ll = long long int;
constexpr int INF = 0x3f3f3f3f;
constexpr ll LNF = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 1'000'000'007;

struct DSU
{
    int n;
    vector<int> par, l, r;

    DSU(int _n) : n(_n), par(_n), l(_n, -1), r(_n, -1)
    {
        iota(par.begin(), par.end(), 0);
    }

    int find(int x)
    {
        while(x != par[x]) x = par[x] = par[par[x]];
        return x;
    }

    bool uni(int a, int b)
    {
        a = find(a);
        b = find(b);
        if(a == b) return false;
        par[b] = a;

        l[a] = min(l[a], l[b]);
        r[a] = max(r[a], r[b]);
        return true;
    }
};

struct SegTree
{
    int n;
    vector<int> t;

    SegTree(int _n)
    {
        n = _n;
        t.resize(n * 2, emptyNode);
    }

    void initv(int idx, int v)
    {
        t[n + idx] = v;
    }

    void build()
    {
        for(int i = n - 1; i > 0; --i) {
            t[i] = merge(t[i << 1], t[i << 1 | 1]);
        }
    }

    void update(int idx, int v)
    {
        idx += n;
        t[idx] = v;
        idx >>= 1;
        while(idx > 0) {
            t[idx] = merge(t[idx << 1], t[idx << 1 | 1]);
            idx >>= 1;
        }
    }

    int find(int l, int r)
    {
        l += n;
        r += n + 1;
        int resl = emptyNode;
        int resr = emptyNode;
        while(l < r) {
            if(l & 1) resl = merge(resl, t[l++]);
            if(r & 1) resr = merge(t[--r], resr);
            l >>= 1;
            r >>= 1;
        }
        return merge(resl, resr);
    }

    int merge(int l, int r)
    {
        return max(l, r);
    }

    const int emptyNode = -INF;
};

void solve()
{
    int n;
    cin >> n;
    struct Node
    {
        int v, idx;
    };
    vector<Node> h(n);
    for(int i = 0; i < n; ++i) {
        cin >> h[i].v;
        h[i].idx = i;
    }

    struct Range
    {
        int l, r, h;
    };
    vector<Range> lr(n);
    DSU dsu(n);
    sort(h.begin(), h.end(), [](const Node& l, const Node& r) {
        return l.v > r.v;
    });
    int lasti = 0;
    for(int i = 0; i < n; ++i) {
        int idx = h[i].idx;
        dsu.l[idx] = idx;
        dsu.r[idx] = idx;
        if(idx > 0 && dsu.l[idx - 1] != -1) dsu.uni(idx - 1, idx);
        if(idx < n - 1 && dsu.l[idx + 1] != -1) dsu.uni(idx, idx + 1);

        if(i == n - 1 || h[i].v != h[i + 1].v) {
            for(int j = lasti; j <= i; ++j) {
                int idx = h[j].idx;
                int rIdx = dsu.find(idx);
                lr[idx].l = dsu.l[rIdx];
                lr[idx].r = dsu.r[rIdx];
                lr[idx].h = h[j].v;
            }
            lasti = i + 1;
        }
    }

    struct Query
    {
        int l, r, w, idx;
    };
    int qNum;
    cin >> qNum;
    vector<Query> qList(qNum);
    for(int i = 0; i < qNum; ++i) {
        Query& q = qList[i];
        cin >> q.l >> q.r >> q.w;
        q.l--; q.r--;
        q.idx = i;
    }

    sort(qList.begin(), qList.end(), [](const Query& l, const Query& r) {
        return l.w > r.w;
    });
    sort(lr.begin(), lr.end(), [](const Range& l, const Range& r) {
        return l.r - l.l < r.r - r.l;
    });

    SegTree sg(n);
    for(int i = 0; i < n; ++i) {
        sg.initv(i, 0);
    }
    sg.build();
    vector<int> res(qNum);
    for(int i = 0; i < qNum; ++i) {
        Query& q = qList[i];
        while(lr.size() > 0 && (lr.back().r - lr.back().l + 1) >= q.w) {
            sg.update(lr.back().l, lr.back().h);
            lr.pop_back();
        }
        res[q.idx] = sg.find(q.l, q.r - q.w + 1);
    }

    for(int i = 0; i < n; ++i) {
        sg.initv(h[i].idx, -h[i].v);
    }
    sg.build();
    for(int i = 0; i < qNum; ++i) {
        Query& q = qList[i];
        res[q.idx] = max(res[q.idx], -sg.find(q.l, q.l + q.w - 1));
    }

    for(int v : res) cout << v << "\n";
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
