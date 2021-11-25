#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

struct SegTree
{
    struct Node
    {
        ll mn;
        ll ed;
    };
    int n;
    vector<Node> t;

    void init(int _n)
    {
        n = _n;
        t.resize(n * 2 + 1);
        // Add init values in [n, n+n)
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
        Node resl = { 0, 0 };
        Node resr = { 0, 0 };
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
        res.mn = min(l.mn, l.ed + r.mn);
        res.ed = l.ed + r.ed;
        return res;
    }
};

int tNum;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        int n;
        ll s;
        cin >> n >> s;
        vector<int> a(n);
        for(int& v : a) cin >> v;

        SegTree sg;
        sg.init(n);
        for(int i = 0; i < n; ++i) {
            sg.t[n + i] = { min(0, a[i]), a[i] };
        }
        sg.build();

        int st = 0, ed = -1;
        for(int i = 0; i < n; ++i) {
            int lo = i - 1, hi = n;
            while(lo + 1 < hi) {
                int m = (lo + hi) / 2;
                ll mn = sg.find(i, m).mn;
                if(mn + s < 0) {
                    hi = m;
                } else {
                    lo = m;
                }
            }
            // use lo
            if(ed - st + 1 < lo - i + 1) {
                ed = lo;
                st = i;
            }
        }
        if(ed - st+ 1 <= 0) {
            cout << "-1\n";
        } else {
            cout << st + 1 << " " << ed + 1 << "\n";
        }
    }

    return 0;
}
