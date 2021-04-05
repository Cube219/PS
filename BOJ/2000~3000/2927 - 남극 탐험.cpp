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
    int t[N * 3];
    int stLeaf, n;

    void init(int n)
    {
        stLeaf = 1;
        while(stLeaf < n) stLeaf *= 2;
    }
    void addValue(int idx, int v)
    {
        t[stLeaf + idx] = v;
    }
    void init2()
    {
        for(int i = stLeaf - 1; i > 0; --i) {
            t[i] = t[i * 2] + t[i * 2 + 1];
        }
    }

    int findImpl(int cl, int cr, int l, int r, int node)
    {
        if(l <= cl && cr <= r) return t[node];
        else if(cr < l || r < cl) return 0;
        int m = (cl + cr) / 2;
        return findImpl(cl, m, l, r, node * 2) + findImpl(m + 1, cr, l, r, node * 2 + 1);
    }

    int find(int l, int r)
    {
        return findImpl(0, stLeaf - 1, l, r, 1);
    }

    void update(int l, int v)
    {
        int node = stLeaf + l;
        t[node] = v;
        node /= 2;
        while(node > 0) {
            t[node] = t[node * 2] + t[node * 2 + 1];
            node /= 2;
        }
    }
};
SegTree<30001> sg;

int n, q;
char str[20];
int d[30001];
struct Query
{
    int type;
    int a;
    int b;
};
Query query[300001];

vector<int> g[30001];
bool complete[30001];
int unipar[30001];

int par[30001], sz[30001];
vector<vector<int>> chList;
int ch[30001], chIdx[30001];
int chFirst[30001], chDepth[30001], num;

int find(int v)
{
    if(unipar[v] == v) return v;
    return unipar[v] = find(unipar[v]);
}
bool uni(int a, int b)
{
    int ar = find(a);
    int br = find(b);
    if(ar == br) return false;

    unipar[ar] = br;
    return true;
}

int dfs(int cur, int p)
{
    complete[cur] = true;
    par[cur] = p;
    sz[cur] = 1;
    for(int nxt : g[cur]) {
        if(nxt == p) continue;
        sz[cur] += dfs(nxt, cur);
    }
    return sz[cur];
}

void hld(int cur, int p, int dep)
{
    complete[cur] = true;
    ch[cur] = chList.size() - 1;
    chIdx[cur] = chList.back().size();
    chList.back().push_back(cur);
    sg.addValue(num, d[cur]);
    num++;

    int hv = -1, hvNode = -1;
    for(int nxt : g[cur]) {
        if(nxt == p) continue;
        if(hv < sz[nxt]) {
            hv = sz[nxt];
            hvNode = nxt;
        }
    }
    if(hv != -1) {
        hld(hvNode, cur, dep);
    }
    for(int nxt : g[cur]) {
        if(nxt == p || nxt == hvNode) continue;
        chList.push_back({});
        chFirst[chList.size() - 1] = num;
        chDepth[chList.size() - 1] = dep + 1;
        hld(nxt, cur, dep + 1);
    }
}

int process(int a, int b)
{
    int ret = 0;
    int ach = ch[a];
    int bch = ch[b];
    while(ach != bch) {
        if(chDepth[ach] > chDepth[bch]) {
            int base = chFirst[ach];
            ret += sg.find(base, base + chIdx[a]);
            a = par[chList[ach][0]];
            ach = ch[a];
        } else {
            int base = chFirst[bch];
            ret += sg.find(base, base + chIdx[b]);
            b = par[chList[bch][0]];
            bch = ch[b];
        }
    }
    int st = chIdx[a];
    int ed = chIdx[b];
    if(st > ed) swap(st, ed);
    ret += sg.find(chFirst[ach] + st, chFirst[ach] + ed);

    return ret;
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for(int i = 0; i < n; ++i) {
        cin >> d[i];
        unipar[i] = i;
    }
    cin >> q;
    for(int i = 0; i < q; ++i) {
        int a, b;
        cin >> str >> a >> b;
        if(str[0] == 'b') {
            query[i].type = 0;
            a--; b--;
        } else if(str[0] == 'p') {
            query[i].type = 1;
            a--;
        } else {
            query[i].type = 2;
            a--; b--;
        }
        query[i].a = a;
        query[i].b = b;
    }

    for(int i = 0; i < q; ++i) {
        if(query[i].type != 0) continue;
        int a = query[i].a;
        int b = query[i].b;
        if(uni(a, b) == true) {
            g[a].push_back(b);
            g[b].push_back(a);
        }
    }
    sg.init(n);
    for(int i = 0; i < n; ++i) {
        if(complete[i] == false) {
            dfs(i, -1);
        }
    }
    for(int i = 0; i < n; ++i) complete[i] = false;
    for(int i = 0; i < n; ++i) {
        if(complete[i] == false) {
            chList.push_back({});
            chFirst[chList.size() - 1] = num;
            chDepth[chList.size() - 1] = 0;
            hld(i, -1, 0);
        }
    }
    sg.init2();

    for(int i = 0; i < n; ++i) {
        unipar[i] = i;
    }
    for(int i = 0; i < q; ++i) {
        if(query[i].type == 0) {
            if(uni(query[i].a, query[i].b) == true) cout << "yes\n";
            else cout << "no\n";
        } else if(query[i].type == 1) {
            int ach = ch[query[i].a];
            int chBegin = chFirst[ach];
            sg.update(chBegin + chIdx[query[i].a], query[i].b);
        } else {
            int ar = find(query[i].a);
            int br = find(query[i].b);
            if(ar != br) {
                cout << "impossible\n";
            } else {
                cout << process(query[i].a, query[i].b) << "\n";
            }
        }
    }

    return 0;
}
