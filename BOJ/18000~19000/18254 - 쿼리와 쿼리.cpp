#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#ifndef CUBE_PS
#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#endif

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <numeric>
#include <vector>
#include <cstring>
#include <chrono>

using namespace std;

using ll = long long int;
constexpr int INF = 0x3f3f3f3f;
constexpr ll LNF = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 1'000'000'007;

class SegTree
{
public:
    vector<int> t;
    vector<int> lazy;
    int stLeaf, n;

    SegTree(int n)
    {
        stLeaf = 1;
        while(stLeaf < n) stLeaf *= 2;

        t.resize(stLeaf * 2, emptyNode);
        lazy.resize(stLeaf * 2, 0);
    }

    void propagate(int l, int r, int node)
    {
        if(lazy[node] == 0) return;

        if(node < stLeaf) {
            lazy[node * 2] ^= lazy[node];
            lazy[node * 2 + 1] ^= lazy[node];
        }

        t[node] ^= ((r - l + 1) & 1) & lazy[node];
        lazy[node] = 0;
    }

    int findImpl(int cl, int cr, int l, int r, int node)
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
            lazy[node] ^= v;
            propagate(cl, cr, node);
            return;
        }
        int m = (cl + cr) / 2;
        addImpl(cl, m, l, r, node * 2, v);
        addImpl(m + 1, cr, l, r, node * 2 + 1, v);
        t[node] = merge(t[node * 2], t[node * 2 + 1]);
    }

    int find(int l, int r)
    {
        return findImpl(0, stLeaf - 1, l, r, 1);
    }

    void add(int l, int r, int v)
    {
        addImpl(0, stLeaf - 1, l, r, 1, v);
    }

    int merge(int l, int r)
    {
        return l ^ r;
    }

    const int emptyNode = 0;
};

int a_imos[100001], udt_imos[100001];

void solve()
{
    int n, m, qNum;
    cin >> n >> m >> qNum;
    vector<int> a(n), asum(n);
    for(auto& v : a) cin >> v;

    struct Update
    {
        int l, r, x;
    };
    vector<Update> update(m);
    for(auto& v : update) {
        cin >> v.l >> v.r >> v.x;
        v.l--; v.r--;
    }

    struct Query
    {
        int qnum, l, r;
        int v; // or res
    };
    vector<Query> query(qNum);
    for(auto& q : query) {
        cin >> q.qnum >> q.l >> q.r;
        if(q.qnum == 1) cin >> q.v;
        else q.v = 0;
        q.l--; q.r--;
    }

    int bucketSz = 90;

    SegTree sg(n);
    struct Border
    {
        int pos, qIdx, v;
    };
    vector<Border> border;
    for(int i = 0; i < qNum; ++i) {
        Query& q = query[i];
        if(q.qnum == 2) continue;
        if(q.l > 0) border.push_back({ q.l - 1, i, q.v });
        border.push_back({ q.r, i, q.v });
    }
    sort(border.begin(), border.end(), [](const Border& l, const Border& r) {
        return l.pos > r.pos;
    });

    for(int i = 0; i < m; ++i) {
        sg.add(update[i].l, update[i].r, 1);

        while(border.size() > 0 && border.back().pos == i) {
            int qIdx = border.back().qIdx;
            int qBucket = qIdx / bucketSz;
            for(int j = 0; j < bucketSz; ++j) {
                if((qIdx + j) / bucketSz > qBucket) break;
                if(qIdx + j >= qNum) break;
                Query& q = query[qIdx + j];
                if(q.qnum == 1) continue;

                int ret = sg.find(q.l, q.r);
                if(ret & 1) q.v ^= border.back().v;
            }
            border.pop_back();
        }
        if(border.size() == 0) break;
    }

    auto process = [&](int st, int ed) {
        memset(a_imos, 0, sizeof(int) * n);
        for(int i = 0; i < m; ++i) {
            Update& up = update[i];
            a_imos[up.l] ^= up.x;
            if(up.r < n - 1) a_imos[up.r + 1] ^= up.x;
        }
        for(int i = 1; i < n; ++i) a_imos[i] ^= a_imos[i - 1];
        
        asum[0] = a[0] ^ a_imos[0];
        for(int i = 1; i < n; ++i) asum[i] = a[i] ^ asum[i - 1] ^ a_imos[i];

        for(int i = st; i <= ed; ++i) {
            Query& q = query[i];
            if(q.qnum == 2) {
                q.v ^= asum[q.r];
                if(q.l > 0) q.v ^= asum[q.l - 1];
            }
        }

        memset(udt_imos, 0, sizeof(int) * m);
        for(int i = st; i <= ed; ++i) {
            Query& q = query[i];
            if(q.qnum == 2) continue;
            udt_imos[q.l] ^= q.v;
            if(q.r < m - 1) udt_imos[q.r + 1] ^= q.v;
        }
        for(int i = 1; i < m; ++i) udt_imos[i] ^= udt_imos[i - 1];
        for(int i = 0; i < m; ++i) update[i].x ^= udt_imos[i];
    };

    for(int st = 0; st < qNum; st += bucketSz) {
        process(st, min(st + bucketSz - 1, qNum - 1));
    }

    for(auto& q : query) {
        if(q.qnum == 2) cout << q.v << "\n";
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
