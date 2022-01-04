#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
#include <cmath>
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
        if(l > r) return 0;
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
        return l + r;
    }

    const int emptyNode = 0;
};

void solve()
{
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for(auto& v : a) cin >> v;

    struct Node
    {
        vector<ll> d;
        ll sum;
        int idx;
    };
    vector<Node> d(m);
    int sz = 0;
    for(int i = 0; i < m; ++i) {
        int k;
        cin >> k;
        sz += k;
        d[i].d.resize(k);
        for(auto& v : d[i].d) {
            cin >> v;
        }
        d[i].sum = 0;
        for(int j = 0; j < k; ++j) {
            d[i].sum += d[i].d[j];
        }
        d[i].idx = 0;
        if(i > 0) d[i].idx = d[i - 1].idx + d[i - 1].d.size();
    }

    sort(a.begin(), a.end());
    sort(d.begin(), d.end(), [](const Node& l, const Node& r) {
        return l.sum * r.d.size() < r.sum * l.d.size();
    });

    vector<int> idx(m, -1), ridx(n, -1);
    SegTree notAssign;
    notAssign.init(n);
    for(int i = 0; i < n; ++i) {
        notAssign.initv(i, 1);
    }
    int ai = 0;
    for(int i = 0; i < m; ++i) {
        while(ai < n && a[ai] * d[i].d.size() < d[i].sum) ++ai;
        if(ai >= n) break;
        idx[i] = ai;
        ridx[ai] = i;
        notAssign.initv(ai, 0);
        ai++;
    }
    notAssign.build();

    SegTree cantLeft;
    cantLeft.init(m);
    for(int i = 1; i < m; ++i) {
        if(idx[i - 1] == -1) break;

        if(a[idx[i - 1]] * d[i].d.size() < d[i].sum) {
            cantLeft.initv(i, 1);
        }
    }
    cantLeft.build();

    bool allAssign = idx[m - 1] == -1 ? false : true;

    vector<int> res(sz, 0);
    if(m == 1 || idx[m - 2] != -1) { // 1개 이하 그룹만 이탈
        for(int i = 0; i < m; ++i) {
            for(int j = 0; j < d[i].d.size(); ++j) {
                int r = 0;
                ll newsum = d[i].sum - d[i].d[j];

                ll newavg = newsum / (d[i].d.size() - 1);
                if(newsum % (d[i].d.size() - 1) > 0) newavg++;

                int newpos = lower_bound(a.begin(), a.end(), newavg) - a.begin();
                if(newpos == n) r = 0;
                else if(newsum * d[i].d.size() < d[i].sum * (d[i].d.size() - 1)) {
                    if(allAssign) r = 1;
                    else if(i == m - 1) {
                        int ck = notAssign.find(newpos, n - 1);
                        if(ck > 0) r = 1;
                        else r = 0;
                    } else {
                        // 이탈한 게 들어갈 수 있는지 확인
                        int ck = notAssign.find(newpos, idx[i] - 1);
                        int ck2 = cantLeft.find(i + 1, m - 1);
                        if(ck > 0 && ck2 == 0) r = 1;
                        else r = 0;
                    }
                } else {
                    if(!allAssign) r = 0;
                    else {
                        int ck = cantLeft.find(i + 1, ridx[newpos]);
                        int ck2 = notAssign.find(newpos, n - 1);
                        if(n > m || ck == 0 || ck2 > 0) r = 1;
                        else r = 0;
                    }
                }
                res[d[i].idx + j] = r;
            }
        }
    }

    for(int i = 0; i < res.size(); ++i) {
        cout << res[i];
    }
    cout << "\n";
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
