#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

template <int N>
class SegTree
{
public:
    struct Node
    {
        int v;
        int idx;
    };

    Node t[N * 3];
    int stLeaf, n;

    void init(int n)
    {
        stLeaf = 1;
        while(stLeaf < n) stLeaf *= 2;
    }

    void initv(int idx, int v)
    {
        t[stLeaf + idx] = v;
    }

    Node merge(const Node& l, const Node& r)
    {
        if(l.v > r.v) return l;
        else return r;
    }

    void build()
    {
        for(int i = 0; i < stLeaf; ++i) {
            t[stLeaf + i] = { 0, -1 };
        }
        for(int i = stLeaf - 1; i > 0; --i) {
            t[i] = merge(t[i * 2], t[i * 2 + 1]);
        }
    }

    Node findImpl(int cl, int cr, int l, int r, int node)
    {
        if(cr < l || r < cl) return { 0, -1 };
        if(l <= cl && cr <= r) return t[node];
        int m = (cl + cr) / 2;
        return merge(findImpl(cl, m, l, r, node * 2), findImpl(m + 1, cr, l, r, node * 2 + 1));
    }

    Node find(int l, int r)
    {
        return findImpl(0, stLeaf - 1, l, r, 1);
    }

    void update(int idx, int v, int pos)
    {
        int node = stLeaf + idx;
        if(t[node].v >= v) return;
        t[node] = { v, pos };
        node /= 2;
        while(node > 0) {
            t[node] = merge(t[node * 2], t[node * 2 + 1]);
            node /= 2;
        }
    }
};

int n, k;
int a[500001];
char s[500010];
SegTree<1000001> eq, gt, lt;
int mxa;
int rec[500001][3];
int mxv, mxpos;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> k;
    for(int i = 0; i < n; ++i) {
        cin >> a[i];
        mxa = max(mxa, a[i]);
    }
    for(int i = 0; i < k; ++i) {
        cin >> s[i];
    }
    eq.init(mxa + 1);
    eq.build();
    gt.init(mxa + 1);
    gt.build();
    lt.init(mxa + 1);
    lt.build();

    mxv = 1;
    mxpos = 0;
    if(s[0] == '=') {
        eq.update(a[0], 1, 0);
    } else if(s[0] == '>') {
        gt.update(a[0], 1, 0);
    } else { // '<'
        lt.update(a[0], 1, 0);
    }

    for(int i = 1; i < n; ++i) {
        // =
        auto res = eq.find(a[i], a[i]);
        char nxts = s[res.v % k];
        if(nxts == '=') {
            eq.update(a[i], res.v + 1, i);
        } else if(nxts == '>') {
            gt.update(a[i], res.v + 1, i);
        } else {
            lt.update(a[i], res.v + 1, i);
        }
        rec[i][0] = res.idx;
        if(mxv < res.v + 1) {
            mxv = res.v + 1;
            mxpos = i;
        }

        // >
        res = gt.find(a[i] + 1, mxa);
        nxts = s[res.v % k];
        if(nxts == '=') {
            eq.update(a[i], res.v + 1, i);
        } else if(nxts == '>') {
            gt.update(a[i], res.v + 1, i);
        } else {
            lt.update(a[i], res.v + 1, i);
        }
        rec[i][1] = res.idx;
        if(mxv < res.v + 1) {
            mxv = res.v + 1;
            mxpos = i;
        }

        // <
        res = lt.find(0, a[i] - 1);
        nxts = s[res.v % k];
        if(nxts == '=') {
            eq.update(a[i], res.v + 1, i);
        } else if(nxts == '>') {
            gt.update(a[i], res.v + 1, i);
        } else {
            lt.update(a[i], res.v + 1, i);
        }
        rec[i][2] = res.idx;
        if(mxv < res.v + 1) {
            mxv = res.v + 1;
            mxpos = i;
        }
    }

    cout << mxv << "\n";
    vector<int> res(mxv);
    int curpos = mxpos;
    int curmode = (mxv - 2 + k) % k;
    for(int i = 0; i < mxv; ++i) {
        res[i] = a[curpos];
        if(s[curmode] == '=') {
            curpos = rec[curpos][0];
        } else if(s[curmode] == '>') {
            curpos = rec[curpos][1];
        } else {
            curpos = rec[curpos][2];
        }
        curmode = (curmode - 1 + k) % k;
    }
    for(int i = mxv - 1; i >= 0; --i) {
        cout << res[i] << " ";
    }

    return 0;
}
