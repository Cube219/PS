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

struct SegTree
{
    int n;
    struct Node
    {
        int mn, mx;
    };
    vector<Node> t;

    SegTree(int _n)
    {
        n = _n;
        t.resize(n * 2, emptyNode);
    }

    void initv(int idx, Node v)
    {
        t[n + idx] = v;
    }

    void build()
    {
        for(int i = n - 1; i > 0; --i) {
            t[i] = merge(t[i << 1], t[i << 1 | 1]);
        }
    }

    void update(int idx, Node v)
    {
        idx += n;
        t[idx] = v;
        idx >>= 1;
        while(idx > 0) {
            t[idx] = merge(t[idx << 1], t[idx << 1 | 1]);
            idx >>= 1;
        }
    }

    Node find(int l, int r)
    {
        l += n;
        r += n + 1;
        Node resl = emptyNode;
        Node resr = emptyNode;
        while(l < r) {
            if(l & 1) resl = merge(resl, t[l++]);
            if(r & 1) resr = merge(t[--r], resr);
            l >>= 1;
            r >>= 1;
        }
        return merge(resl, resr);
    }

    Node merge(Node l, Node r)
    {
        Node res;
        res.mn = min(l.mn, r.mn);
        res.mx = max(l.mx, r.mx);
        return res;
    }

    const Node emptyNode = { INF, -1 };
};



void solve()
{
    int n, d;
    cin >> n >> d;
    int prex = 0;
    vector<int> sz;
    for(int i = 0; i < n; ++i) {
        int x;
        cin >> x;

        int v = x - prex - 1;
        sz.push_back(v);

        prex = x;
    }

    SegTree sg(n);
    for(int i = 0; i < n; ++i) {
        sg.initv(i, { sz[i], sz[i] });
    }
    sg.build();

    int res = sg.find(0, n - 1).mn;
    for(int i = 0; i < n - 1; ++i) {
        int newsz = sz[i] + sz[i + 1] + 1;

        int curmn = INF;
        int curmx = -1;
        if(i > 0) {
            auto v = sg.find(0, i - 1);
            curmn = min(curmn, v.mn);
            curmx = max(curmx, v.mx);
        }
        if(i < n - 1) {
            auto v = sg.find(i + 2, n - 1);
            curmn = min(curmn, v.mn);
            curmx = max(curmx, v.mx);
        }

        curmx = max(curmx, newsz);
        curmn = min(curmn, newsz);

        // 맨 끝으로 옮기는 경우
        if(prex < d) {
            int v = min(curmn, d - prex - 1);
            res = max(res, v);
        }

        // 사이에 넣는 경우
        curmn = min(curmn, (curmx - 1) / 2);

        res = max(res, curmn);
    }

    // 마지막 맨 끝으로 옮기기
    if(prex < d) {
        sz.back() += d - prex;
        sg.update(n - 1, { sz.back(), sz.back() });
        res = max(res, sg.find(0, n - 1).mn);
    }

    cout << res << "\n";
}

int main()
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int tNum = 1;
    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        solve();
    }

    return 0;
}
