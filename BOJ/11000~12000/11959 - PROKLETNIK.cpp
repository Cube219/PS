#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <numeric>
#include <vector>
#include <map>
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
        int v, r, mnL;
    };
    vector<Node> t;
    int stLeaf, n;

    SegTree(int _n)
    {
        n = _n;
        stLeaf = 1;
        while(stLeaf < n) stLeaf *= 2;

        t.resize(stLeaf * 2, emptyNode);
    }

    void build()
    {
        for(int i = 0; i < n; ++i) {
            t[stLeaf + i] = { 1, -1, i };
        }
        for(int i = stLeaf - 1; i > 0; --i) {
            t[i].mnL = min(t[i * 2].mnL, t[i * 2 + 1].mnL);
            t[i].v = max(t[i * 2].v, t[i * 2 + 1].v);
        }
    }

    void propagate(int l, int r, int node)
    {
        if(t[node].r == -1) return;

        if(node < stLeaf) {
            t[node * 2].r = t[node].r;
            t[node * 2 + 1].r = t[node].r;
        }

        if(t[node].mnL != -1) {
            t[node].v = max(t[node].v, t[node].r - t[node].mnL + 1);
        }
        t[node].r = -1;
    }

    int findImpl(int cl, int cr, int l, int r, int node)
    {
        propagate(cl, cr, node);
        if(cr < l || r < cl) return 0;
        if(l <= cl && cr <= r) return t[node].v;
        int m = (cl + cr) / 2;
        return max(findImpl(cl, m, l, r, node * 2), findImpl(m + 1, cr, l, r, node * 2 + 1));
    }

    void udtImpl(int cl, int cr, int l, int r, int node, int v)
    {
        propagate(cl, cr, node);
        if(cr < l || r < cl) return;
        if(l <= cl && cr <= r) {
            t[node].r = v;
            propagate(cl, cr, node);
            return;
        }
        int m = (cl + cr) / 2;
        udtImpl(cl, m, l, r, node * 2, v);
        udtImpl(m + 1, cr, l, r, node * 2 + 1, v);
        t[node].v = max(t[node * 2].v, t[node * 2 + 1].v);
    }

    int find(int l, int r)
    {
        return findImpl(0, stLeaf - 1, l, r, 1);
    }

    void update(int l, int r, int v)
    {
        udtImpl(0, stLeaf - 1, l, r, 1, v);
    }

    void except(int idx)
    {
        find(idx, idx);
        idx += stLeaf;
        t[idx].mnL = -1;
        idx >>= 1;

        while(idx > 0) {
            if(t[idx * 2].mnL != -1) t[idx].mnL = t[idx * 2].mnL;
            else t[idx].mnL = t[idx * 2 + 1].mnL;

            idx >>= 1;
        }
    }

    // Node merge(Node l, Node r)
    // {
    //     return l + r;
    // }

    const Node emptyNode = { 0, -1, -1 };
};


struct MxSegTree
{
    int n;
    vector<int> t;

    MxSegTree(int _n)
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

    const int emptyNode = -1;
};

void solve()
{
    int n;
    cin >> n;
    vector<int> d(n), dd;
    for(auto& v : d) {
        cin >> v;
        dd.push_back(v);
    }
    sort(dd.begin(), dd.end());
    dd.erase(unique(dd.begin(), dd.end()), dd.end());
    auto getdd = [&](int v) { return lower_bound(dd.begin(), dd.end(), v) - dd.begin(); };
    for(auto& v : d) v = getdd(v);

    struct Query
    {
        int l, r, idx, res;
    };
    int qNum;
    cin >> qNum;
    vector<Query> qList(qNum);
    for(int i = 0; i < qNum; ++i) {
        auto& q = qList[i];
        cin >> q.l >> q.r;
        q.l--; q.r--;
        q.idx = i;
        q.res = 0;
    }

    auto process = [&]() {
        sort(qList.begin(), qList.end(), [](const Query& l, const Query& r) {
            return l.r < r.r;
        });

        map<int, vector<int>> preList;
        SegTree sg(n);
        sg.build();
        MxSegTree mxSg(dd.size() + 1);
        mxSg.build();

        int i = 0;
        for(auto& q : qList) {
            for(; i <= q.r; ++i) {
                // Except
                auto it = preList.upper_bound(d[i]);
                while(it != preList.end()) {
                    for(int idx : it->second) {
                        sg.except(idx);
                    }
                    auto nxtIt = next(it);
                    preList.erase(it);
                    it = nxtIt;
                }
                // Range
                int l = mxSg.find(d[i] + 1, dd.size());
                sg.update(l + 1, i, i);

                mxSg.update(d[i], i);
                it = preList.find(d[i]);
                if(it == preList.end()) it = preList.insert({ d[i], {} }).first;
                it->second.push_back(i);
            }

            q.res = max(q.res, sg.find(q.l, q.r));
        }
    };
    process();
    reverse(d.begin(), d.end());
    for(auto& q : qList) {
        swap(q.l, q.r);
        q.l = n - 1 - q.l;
        q.r = n - 1 - q.r;
    }
    process();

    sort(qList.begin(), qList.end(), [](const Query& l, const Query& r) {
        return l.idx < r.idx;
    });
    for(auto& q : qList) cout << q.res << "\n";
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
