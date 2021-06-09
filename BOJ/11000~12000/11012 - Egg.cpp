#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

struct PST
{
    struct Node
    {
        int l = -1, r = -1;
        int v = 0;
    };
    vector<Node> t;
    int stLeaf;
    int root[50005];
    int rcnt = 0;

    void init(int n)
    {
        t.clear();
        rcnt = 0;
        root[0] = 1;

        stLeaf = 1;
        while(stLeaf < n) stLeaf *= 2;
        t.resize(stLeaf * 2 + 1);
        
        for(int i = 1; i < stLeaf; ++i) {
            t[i].l = i * 2;
            t[i].r = i * 2 + 1;
        }
    }

    int findImpl(int cl, int cr, int l, int r, int node)
    {
        if(l <= cl && cr <= r) return t[node].v;
        else if(cr < l || r < cl) return 0;
        int m = (cl + cr) / 2;
        return findImpl(cl, m, l, r, t[node].l) + findImpl(m + 1, cr, l, r, t[node].r);
    }

    int find(int l, int r, int v)
    {
        return findImpl(0, stLeaf - 1, l, r, root[v]);
    }

    void update(int idx)
    {
        int cl = 0, cr = stLeaf - 1;
        int node = root[rcnt];

        int newnode = t.size();
        root[++rcnt] = newnode;
        t.push_back(t[node]);

        while(cl != cr) {
            int m = (cl + cr) / 2;
            if(idx <= m) {
                cr = m;
                t[newnode].l = newnode + 1;
                newnode++;

                node = t[node].l;
                t.push_back(t[node]);
            } else {
                cl = m + 1;
                t[newnode].r = newnode + 1;
                newnode++;

                node = t[node].r;
                t.push_back(t[node]);
            }
        }
        t[newnode].v = t[node].v + 1;
        newnode--;
        while(newnode >= root[rcnt]) {
            t[newnode].v = t[t[newnode].l].v + t[t[newnode].r].v;
            newnode--;
        }
    }
};

struct Node
{
    int x, y;
};
int tNum;
int n, m;
Node d[10001];
PST pst;
int xidx[100001];
vector<int> xx;

int getnearx(int x)
{
    auto it = upper_bound(xx.begin(), xx.end(), x);
    if(it == xx.begin()) return -1;
    else return *prev(it);
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        cin >> n >> m;
        for(int i = 0; i < n; ++i) {
            int x, y;
            cin >> x >> y;
            d[i] = { x, y };
        }
        sort(d, d + n, [](const Node& l, const Node& r) {
            return l.x < r.x;
        });
        pst.init(100001);
        xx.clear();
        int lastx = d[0].x;
        for(int i = 0; i < n; ++i) {
            pst.update(d[i].y);
            if(lastx != d[i].x) {
                xidx[lastx] = i;
                xx.push_back(lastx);
            }
            lastx = d[i].x;
        }
        xidx[lastx] = n;
        xx.push_back(lastx);

        ll res = 0;
        for(int i = 0; i < m; ++i) {
            int l, r, b, t;
            cin >> l >> r >> b >> t;
            int lx = getnearx(l - 1);
            int rx = getnearx(r);

            int r1 = 0, r2 = 0;
            if(rx != -1) {
                r1 = pst.find(b, t, xidx[rx]);
            }
            if(lx != -1) {
                r2 = pst.find(b, t, xidx[lx]);
            }
            res += (ll)(r1 - r2);
        }
        cout << res << "\n";
    }

    return 0;
}
