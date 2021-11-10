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

template <int N>
struct SegTree
{
    int n;
    int t[N * 2 + 1];

    void init(int _n)
    {
        n = _n;
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

int n, m, nsq;
int a[100001];
vector<int> vv;
Query q[100001];
ll curv, res[100001];
SegTree<100001> sg;

int getv(int v)
{
    return lower_bound(vv.begin(), vv.end(), v) - vv.begin();
}

void add(int v, bool isleft)
{
    if(isleft) {
        curv += sg.find(0, v - 1);
    } else {
        curv += sg.find(v + 1, vv.size() - 1);
    }
    sg.update(v, 1);
}

void remove(int v, bool isleft)
{
    sg.update(v, -1);
    if(isleft) {
        curv -= sg.find(0, v - 1);
    } else {
        curv -= sg.find(v + 1, vv.size() - 1);
    }
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;
    nsq = (int)sqrt(n);
    for(int i = 0; i < n; ++i) {
        cin >> a[i];
        vv.push_back(a[i]);
    }
    sort(vv.begin(), vv.end());
    vv.erase(unique(vv.begin(), vv.end()), vv.end());
    for(int i = 0; i < n; ++i) {
        a[i] = getv(a[i]);
    }
    sg.init(vv.size());

    for(int i = 0; i < m; ++i) {
        int l, r;
        cin >> l >> r;
        q[i] = { l - 1, r - 1, i };
    }
    sort(q, q + m, [](const Query& l, const Query& r) {
        if(l.l / nsq == r.l / nsq) return l.r < r.r;
        return l.l < r.l;
    });

    int l = q[0].l, r = q[0].l - 1;
    for(int i = 0; i < m; ++i) {
        auto& cur = q[i];
        while(cur.l < l) add(a[--l], true);
        while(r < cur.r) add(a[++r], false);
        while(l < cur.l) remove(a[l++], true);
        while(cur.r < r) remove(a[r--], false);

        res[cur.idx] = curv;
    }

    for(int i = 0; i < m; ++i) {
        cout << res[i] << "\n";
    }

    return 0;
}
