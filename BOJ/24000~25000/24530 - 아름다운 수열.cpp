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

class SegTree
{
public:
    struct Node
    {
        int mn, mnIdx, cnt;
    };
    vector<Node> t;
    int stLeaf, n;

    SegTree(int n)
    {
        stLeaf = 1;
        while(stLeaf < n) stLeaf *= 2;

        t.resize(stLeaf * 2, emptyNode);
    }

    void initv(int idx, int v)
    {
        t[stLeaf + idx] = { v, idx, 1 };
    }

    void build()
    {
        for(int i = stLeaf - 1; i > 0; --i) {
            t[i] = merge(t[i * 2], t[i * 2 + 1]);
        }
    }

    int findImpl(int cl, int cr, int l, int r, int node)
    {
        if(cr < l || r < cl) return 0;
        if(l <= cl && cr <= r) return t[node].cnt;
        int m = (cl + cr) / 2;
        return findImpl(cl, m, l, r, node * 2) + findImpl(m + 1, cr, l, r, node * 2 + 1);
    }

    int findCnt(int l, int r)
    {
        return findImpl(0, stLeaf - 1, l, r, 1);
    }

    // value, idx
    pair<int, int> search(int cl, int cr, int node, ll cnt)
    {
        if(t[node].cnt - 1 <= cnt) {
            return { t[node].mn, t[node].mnIdx };
        }

        int m = (cl + cr) / 2;
        auto res = search(cl, m, node * 2, cnt);
        if(cnt - t[node * 2].cnt >= 0) {
            auto res2 = search(m + 1, cr, node * 2 + 1, cnt - t[node * 2].cnt);
            if(res.first > res2.first) res = res2;
        }
        return res;
    }

    void update(int idx)
    {
        idx += stLeaf;
        t[idx] = { INF, idx - stLeaf, 0 };
        idx >>= 1;
        while(idx > 0) {
            t[idx] = merge(t[idx * 2], t[idx * 2 + 1]);
            idx >>= 1;
        }
    }

    Node merge(Node l, Node r)
    {
        Node res;
        if(l.mn <= r.mn) {
            res.mn = l.mn;
            res.mnIdx = l.mnIdx;
        } else {
            res.mn = r.mn;
            res.mnIdx = r.mnIdx;
        }
        res.cnt = l.cnt + r.cnt;
        return res;
    }

    const Node emptyNode = { INF, -1, 0 };
};

void solve()
{
    int n;
    ll k;
    cin >> n >> k;
    vector<int> a(n);
    for(auto& v : a) cin >> v;

    SegTree sg(n);
    for(int i = 0; i < n; ++i) {
        sg.initv(i, a[i]);
    }
    sg.build();

    vector<int> res(n);
    vector<char> comp(n, false);
    int pos = 0;
    for(int i = 0; i < n; ++i) {
        while(comp[pos]) pos++;

        if(k == 0) {
            res[i] = a[pos];
            comp[pos] = true;
            continue;
        }

        auto [v, idx] = sg.search(pos, sg.stLeaf - 1, 1, k);
        res[i] = v;
        comp[idx] = true;

        sg.update(idx);
        k -= sg.findCnt(pos, idx);
    }

    bool hasSame = false;
    int last = INF;
    for(int i = 0; i < n; ++i) {
        if(last == res[i]) {
            hasSame = true;
            break;
        }
        last = res[i];
    }
    if(hasSame == false && k & 1) swap(res[n - 1], res[n - 2]);

    for(int v : res) cout << v << " ";
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
