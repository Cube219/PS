#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
#include <cmath>
#include <memory.h>
using namespace std;

using ll = long long int;

template <int N>
struct SegTree
{
    int n;
    int t[N * 2 + 1];

    void init(int _n)
    {
        n = _n;
        // Add init values in [n, n+n)
    }

    void clear()
    {
        memset(t, 0, sizeof(int) * (n * 2 + 1));
    }

    void update(int idx, int v)
    {
        idx += n;
        t[idx] += v;
        idx >>= 1;
        while(idx > 0) {
            t[idx] = t[idx << 1] + t[idx << 1 | 1];
            idx >>= 1;
        }
    }

    int find(int l, int r)
    {
        l += n;
        r += n + 1;
        int resl = 0;
        int resr = 0;
        while(l < r) {
            if(l & 1) resl = resl + t[l++];
            if(r & 1) resr = t[--r] + resr;
            l >>= 1;
            r >>= 1;
        }
        return resl + resr;
    }
};

struct Query
{
    int l, r, idx;
};

int n, m, k, a[100001], nsq;
Query q[100001];
ll res[100001], curres;
SegTree<100001> sg;

void add(int num)
{
    int mn = max(0, num - k);
    int mx = min(100000, num + k);
    int v = sg.find(mn, mx);

    curres += v;

    sg.update(num, 1);
}

void remove(int num)
{
    sg.update(num, -1);

    int mn = max(0, num - k);
    int mx = min(100000, num + k);
    int v = sg.find(mn, mx);

    curres -= v;
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    sg.init(100001);

    cin >> n >> k;
    nsq = (int)sqrt(n);
    for(int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    cin >> m;
    for(int i = 0; i < m; ++i) {
        int l, r;
        cin >> l >> r;
        l--; r--;
        q[i] = { l, r, i };
    }
    sort(q, q + m, [](const Query& l, const Query& r) {
        if(l.l / nsq == r.l / nsq) return l.r < r.r;
        return l.l < r.l;
    });

    int l = 0, r = 0;
    int lsq = -1;
    for(int i = 0; i < m; ++i) {
        auto& cur = q[i];

        if(lsq != cur.l / nsq) {
            curres = 0;
            sg.clear();
            lsq = cur.l / nsq;

            for(int j = cur.l; j <= cur.r; ++j) {
                add(a[j]);
            }
            l = cur.l;
            r = cur.r;
        }

        while(cur.l < l) add(a[--l]);
        while(r < cur.r) add(a[++r]);
        while(l < cur.l) remove(a[l++]);
        while(cur.r < r) remove(a[r--]);

        res[cur.idx] = curres;
    }


    for(int i = 0; i < m; ++i) {
        cout << res[i] << "\n";
    }

    return 0;
}
