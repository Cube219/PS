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

struct Node
{
    int v;
    int pos;
};

struct SegTree
{
    int n;
    vector<Node> t;

    void init(int _n)
    {
        n = _n;
        t.resize(n * 2, emptyNode);
        for(int i = 0; i < n; ++i) {
            t[n + i].pos = i;
        }
    }

    void initv(int idx, int v)
    {
        t[n + idx].v = v;
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
        t[idx].v = v;
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
        if(l.v < r.v) return r;
        else return l;
    }

    const Node emptyNode = { -INF, 0 };
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

    vector<vector<Node>> ltb(n, vector<Node>(18));
    vector<vector<Node>> rtb(n, vector<Node>(18));

    SegTree lt;
    SegTree rt;
    lt.init(n); rt.init(n);

    for(int i = 0; i < n; ++i) {
        ltb[i][0] = { l[i], -1 };
        rtb[i][0] = { r[i], -1 };
    }

    for(int i = 1; i < 18; ++i) {
        for(int j = 0; j < n; ++j) {
            lt.initv(j, -ltb[j][i - 1].v);
            rt.initv(j, rtb[j][i - 1].v);
        }
        lt.build(); rt.build();

        for(int j = 0; j < n; ++j) {
            int curl = ltb[j][i - 1].v;
            int curr = rtb[j][i - 1].v;

            Node nxtl = lt.find(curl, curr);
            nxtl.v = -nxtl.v;
            Node nxtr = rt.find(curl, curr);
            ltb[j][i] = nxtl;
            rtb[j][i] = nxtr;
        }
    }

    for(int i = 0; i < q; ++i) {
        int s, e;
        cin >> s >> e;
        s--; e--;
        int res = 0;
        if(s < e) {
            int cur = s;
            for(int j = 18 - 1; j >= 0; --j) {
                if(rtb[cur][j].v < e) {
                    if(j == 17) {
                        res = -1;
                        break;
                    }
                    res += (1 << j);
                    cur = rtb[cur][j + 1].pos;
                    j++;
                }
            }
            if(cur < e && rtb[cur][0].v == e) res++;
            else if(cur < e) res = -1;
        } else {
            int cur = s;
            for(int j = 18 - 1; j >= 0; --j) {
                if(ltb[cur][j].v > e) {
                    if(j == 17) {
                        res = -1;
                        break;
                    }
                    res += (1 << j);
                    cur = ltb[cur][j + 1].pos;
                    j++;
                }
            }
            if(cur > e && ltb[cur][0].v == e) res++;
            else if(cur > e) res = -1;
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
