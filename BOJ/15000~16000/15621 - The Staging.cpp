#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <set>
#include <vector>
using namespace std;

using ll = long long int;

class SegTree
{
public:
    struct Node
    {
        int lv, rv, sz, lcnt, rcnt, res;
    };
    Node empty = { 0, 0, 0, 0, 0, 0 };

    vector<Node> t;
    int stLeaf, n;

    void init(int n)
    {
        stLeaf = 1;
        while(stLeaf < n) stLeaf *= 2;
        t.resize(stLeaf * 2, empty);
    }

    void initv(int idx, int v)
    {
        t[stLeaf + idx] = { v, v, 1, 1, 1, 1 };
    }

    Node merge(const Node& l, const Node& r)
    {
        if(r.sz == 0) {
            return l;
        }
        Node res;
        res.lv = l.lv;
        res.rv = r.rv;
        res.sz = l.sz + r.sz;

        res.lcnt = l.lcnt;
        if(l.lcnt == l.sz) {
            if(l.rv < r.lv) res.lcnt += r.lcnt;
        }
        res.rcnt = r.rcnt;
        if(r.rcnt == r.sz){
            if(l.rv < r.lv) res.rcnt += l.rcnt;
        }

        res.res = l.res + r.res;
        if(l.rv < r.lv) {
            if((l.rcnt & 1) == 1 && (r.lcnt & 1) == 1) res.res -= 2;
        }

        return res;
    }

    void build()
    {
        for(int i = stLeaf - 1; i > 0; --i) {
            t[i] = merge(t[i * 2], t[i * 2 + 1]);
        }
    }

    Node findImpl(int cl, int cr, int l, int r, int node)
    {
        if(cr < l || r < cl) return empty;
        if(l <= cl && cr <= r) return t[node];
        int m = (cl + cr) / 2;
        return merge(findImpl(cl, m, l, r, node * 2), findImpl(m + 1, cr, l, r, node * 2 + 1));
    }

    int find(int l, int r)
    {
        Node res = findImpl(0, stLeaf - 1, l, r, 1);
        if(res.lcnt == res.sz) return 0;
        if(res.lv < res.rv) return res.res;
        if((res.lcnt + res.rcnt) == res.sz) return 0;
        if((res.lcnt & 1) == 1 && (res.rcnt & 1) == 1) {
            return res.res - 2;
        }
        return res.res;
    }

    void update(int idx, int v)
    {
        int node = stLeaf + idx;
        t[node] = { v, v, 1, 1, 1, 1 };
        node /= 2;
        while(node > 0) {
            t[node] = merge(t[node * 2], t[node * 2 + 1]);
            node /= 2;
        }
    }
};

struct Group
{
    int st, ed;
    SegTree sg;
    int lastv;
};

int n, p[200001], t[200001], t2[200001];
int table[200001], gidx[200001], num;
vector<Group> g;
int q;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for(int i = 0; i < n; ++i) {
        int a;
        cin >> a;
        a--;
        p[i] = a;

        table[i] = -1;
    }
    for(int i = 0; i < n; ++i) {
        cin >> t[i];
    }

    for(int i = 0; i < n; ++i) {
        if(table[i] != -1) continue;

        int cur = i;
        g.push_back({ num, 0 });
        while(table[cur] == -1) {
            table[cur] = num++;
            t2[num - 1] = t[cur];
            gidx[cur] = g.size() - 1;

            cur = p[cur];
        }
        g.back().ed = num - 1;
    }

    int res = 0;
    for(auto& gr : g) {
        int gsz = gr.ed - gr.st + 1;

        gr.sg.init(gsz);
        for(int i = gr.st; i <= gr.ed; ++i) {
            gr.sg.initv(i - gr.st, t2[i]);
        }
        gr.sg.build();

        gr.lastv = (gsz - gr.sg.find(0, gsz - 1)) / 2;
        res += gr.lastv;
    }
    cout << res << "\n";

    cin >> q;
    for(int i = 0; i < q; ++i) {
        int a, b;
        cin >> a >> b;
        a--;

        Group& gr = g[gidx[a]];
        int gsz = gr.ed - gr.st + 1;

        res -= gr.lastv;
        gr.sg.update(table[a] - gr.st, b);
        gr.lastv = (gsz - gr.sg.find(0, gsz - 1)) / 2;
        res += gr.lastv;

        cout << res << "\n";
    }

    return 0;
}
