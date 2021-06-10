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
        int idx = 0;
    };

    vector<Node> t;
    int stLeaf;
    int dep;
    vector<int> root;

    void init(int n)
    {
        t.clear();
        root.clear();
        root.push_back(1);

        stLeaf = 1;
        while(stLeaf < n) {
            stLeaf *= 2;
            dep++;
        }
        t.resize(stLeaf * 2 + 1);
        for(int i = 0; i < n; ++i) {
            t[stLeaf + i].idx = i;
        }
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

    int find(int l, int r, int version)
    {
        return findImpl(0, stLeaf - 1, l, r, root[version]);
    }

    void update(int idx)
    {
        int cl = 0, cr = stLeaf - 1;
        int node = root.back();

        int newnode = t.size();
        root.push_back(newnode);
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
        while(newnode >= root.back()) {
            t[newnode].v = t[t[newnode].l].v + t[t[newnode].r].v;
            newnode--;
        }
    }

    void remove(int k)
    {
        int removeroot = root[root.size() - k];
        t.erase(t.begin() + removeroot, t.end());
        root.erase(root.end() - k, root.end());
    }
};

int q, n;
PST pst;

int getlesseq(int l, int r, int v)
{
    int s1 = pst.find(0, v, r);
    s1 -= pst.find(0, v, l - 1);

    return s1;
}

int getkth(int l, int r, int k)
{
    int rnode = pst.root[r];
    int lnode = pst.root[l - 1];
    while(1) {
        PST::Node& ln = pst.t[lnode];
        PST::Node& rn = pst.t[rnode];
        if(rn.l == -1) {
            return rn.idx;
        }

        int num = pst.t[rn.l].v - pst.t[ln.l].v;
        if(num > k) {
            lnode = ln.l;
            rnode = rn.l;
        } else {
            k -= num;
            lnode = ln.r;
            rnode = rn.r;
        }
    }
}

int getxor(int l, int r, int x)
{
    int rnode = pst.root[r];
    int lnode = pst.root[l - 1];
    for(int curdep = 0; curdep < pst.dep; ++curdep) {
        int bit = x & (1 << (pst.dep - curdep - 1));
        PST::Node& ln = pst.t[lnode];
        PST::Node& rn = pst.t[rnode];
        if(bit > 0) {
            if(pst.t[rn.l].v - pst.t[ln.l].v > 0) {
                lnode = ln.l;
                rnode = rn.l;
            } else {
                lnode = ln.r;
                rnode = rn.r;
            }
        } else {
            if(pst.t[rn.r].v - pst.t[ln.r].v > 0) {
                lnode = ln.r;
                rnode = rn.r;
            } else {
                lnode = ln.l;
                rnode = rn.l;
            }
        }
    }

    return pst.t[rnode].idx;
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    pst.init(500001);

    cin >> q;
    for(int i = 0; i < q; ++i) {
        int a, b, c, d;
        cin >> a;
        switch(a) {
            case 1:
                cin >> b;
                pst.update(b);
                n++;
                break;
            case 2:
                cin >> b >> c >> d;
                cout << getxor(b, c, d) << "\n";
                break;
            case 3:
                cin >> b;
                pst.remove(b);
                n -= b;
                break;
            case 4:
                cin >> b >> c >> d;
                cout << getlesseq(b, c, d) << "\n";
                break;
            case 5:
                cin >> b >> c >> d;
                cout << getkth(b, c, d - 1) << "\n";
                break;
            default:
                break;
        }
    }

    return 0;
}
