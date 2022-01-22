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
        t[idx] = max(t[idx], v);
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

    const int emptyNode = 0;
};


void solve()
{
    int n;
    cin >> n;
    vector<int> p(n), q(n);
    for(auto& v : p) cin >> v;
    for(auto& v : q) cin >> v;

    vector<int> qpos(n + 1);
    for(int i = 0; i < n; ++i) {
        qpos[q[i]] = i;
    }

    SegTree sg(n);
    for(int i = 0; i < n; ++i) {
        sg.initv(i, 0);
    }
    sg.build();
    int res = 0;
    for(int i = 0; i < n; ++i) {
        vector<pair<int, int>> tmp;
        for(int j = 1; j <= n; ++j) {
            if(p[i] * j > n) break;
            int pos = qpos[p[i] * j];
            tmp.emplace_back(pos, sg.find(0, pos - 1) + 1);
        }

        for(auto& v : tmp) {
            res = max(res, v.second);
            sg.update(v.first, v.second);
        }
    }

    cout << res;
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
