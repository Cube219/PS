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

ll r, c;

struct Node
{
    // 0: 음수, 1: 양수, 2: 제로
    ll v[3][3];
    Node()
    {
        for(int i = 0; i < 3; ++i) {
            for(int j = 0; j < 3; ++j) {
                v[i][j] = -1;
            }
        }
    }
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
            for(int l = 0; l < 3; ++l) {
                for(int r = 0; r < 3; ++r) {
                    t[n + i].v[l][r] = LNF;
                }
            }
        }
    }

    void initv(int idx, int v)
    {
        if(v > 0) {
            t[n + idx].v[0][0] = min(r, (v + 1) * c);
            t[n + idx].v[1][1] = 0;
            t[n + idx].v[2][2] = c * v;
        } else if(v < 0) {
            t[n + idx].v[0][0] = 0;
            t[n + idx].v[1][1] = min(r, (-v + 1) * c);
            t[n + idx].v[2][2] = c * (-v);
        } else {
            t[n + idx].v[0][0] = c;
            t[n + idx].v[1][1] = c;
            t[n + idx].v[2][2] = 0;
        }
    }

    void build()
    {
        for(int i = n - 1; i > 0; --i) {
            t[i] = merge(t[i << 1], t[i << 1 | 1]);
        }
    }

    void update(int idx, int v)
    {
        initv(idx, v);
        idx += n;
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
        if(l.v[0][0] == -1) {
            return r;
        }
        if(r.v[0][0] == -1) {
            return l;
        }
        Node res;
        for(int i = 0; i < 3; ++i) {
            for(int j = 0; j < 3; ++j) {
                res.v[i][j] = LNF;
            }
        }
        for(int ll = 0; ll < 3; ++ll) {
            for(int lr = 0; lr < 3; ++lr) {
                for(int rl = 0; rl < 3; ++rl) {
                    for(int rr = 0; rr < 3; ++rr) {
                        if(lr == rl) continue;
                        res.v[ll][rr] = min(res.v[ll][rr], l.v[ll][lr] + r.v[rl][rr]);
                    }
                }
            }
        }

        return res;
    }

    const Node emptyNode = Node();
};


void solve()
{
    int n, t;
    cin >> n >> r >> c >> t;
    SegTree sg;
    sg.init(n);
    for(int i = 0; i < n; ++i) {
        int a;
        cin >> a;
        sg.initv(i, a);
    }
    sg.build();

    auto get = [&]() {
        Node sres = sg.find(0, n - 1);
        ll res = LNF;
        for(int l = 0; l < 3; ++l) {
            for(int r = 0; r < 3; ++r) {
                res = min(res, sres.v[l][r]);
            }
        }
        return res;
    };
    cout << get() << "\n";

    for(int i = 0; i < t; ++i) {
        int pos, v;
        cin >> pos >> v;
        pos--;
        sg.update(pos, v);
        cout << get() << "\n";
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
