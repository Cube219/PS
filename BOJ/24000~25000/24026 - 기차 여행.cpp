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

    void init(int _n)
    {
        n = _n;
        t.resize(n * 2, emptyNode);
        // Add init values in [n, n+n)
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
    int n, q;
    cin >> n >> q;
    vector<int> l(n), r(n);
    for(int i = 0; i < n; ++i) {
        cin >> l[i] >> r[i];
        l[i]--; r[i]--;
    }

    vector<SegTree> lsg(18), rsg(18);

    lsg[0].init(n); rsg[0].init(n);
    for(int i = 0; i < n; ++i) {
        lsg[0].initv(i, -l[i]);
        rsg[0].initv(i, r[i]);
    }
    lsg[0].build(); rsg[0].build();
    for(int j = 1; j < 18; ++j) {
        lsg[j].init(n);
        rsg[j].init(n);
        for(int i = 0; i < n; ++i) {
            int curl = -lsg[j - 1].t[n + i];
            int curr = rsg[j - 1].t[n + i];

            lsg[j].initv(i, lsg[j - 1].find(curl, curr));
            rsg[j].initv(i, rsg[j - 1].find(curl, curr));
        }
        lsg[j].build();
        rsg[j].build();
    }

    for(int i = 0; i < q; ++i) {
        int s, e;
        cin >> s >> e;
        s--; e--;
        int res = 0;

        int curl = s, curr = s;
        for(int j = 18 - 1; j >= 0; --j) {
            int nxtl = -lsg[j].find(curl, curr);
            int nxtr = rsg[j].find(curl, curr);
            if(nxtl <= e && e <= nxtr) continue;

            res += 1 << j;
            curl = nxtl;
            curr = nxtr;
        }
        if(e < curl || curr < e) {
            int nxtl = -lsg[0].find(curl, curr);
            int nxtr = rsg[0].find(curl, curr);
            if(nxtl <= e && e <= nxtr) {
                res++;
            } else {
                res = -1;
            }
        }
        cout << res << "\n";
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
