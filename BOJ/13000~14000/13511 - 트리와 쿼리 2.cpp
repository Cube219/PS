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
    ll t[N * 3];
    int stLeaf, n;

    void init(int n)
    {
        stLeaf = 1;
        while(stLeaf < n) stLeaf *= 2;

    }
    void addValue(int idx, ll v)
    {
        t[stLeaf + idx] = v;
    }
    void init2()
    {
        for(int i = stLeaf - 1; i > 0; --i) {
            t[i] = t[i * 2] + t[i * 2 + 1];
        }
    }

    ll findImpl(int cl, int cr, int l, int r, int node)
    {
        if(l <= cl && cr <= r) return t[node];
        else if(cr < l || r < cl) return 0;
        int m = (cl + cr) / 2;
        return findImpl(cl, m, l, r, node * 2) + findImpl(m + 1, cr, l, r, node * 2 + 1);
    }

    ll find(int l, int r)
    {
        return findImpl(0, stLeaf - 1, l, r, 1);
    }
};

int n, m;
vector<pair<int, ll>> g[100001];

int parent[100001], sz[100001];
ll cost[100001];
vector<vector<int>> chList;
int ch[100001], chIdx[100001];
int chFirst[100001], chDepth[100001], num;
SegTree<100001> sg;

int dfs(int cur, int p)
{
    parent[cur] = p;
    sz[cur] = 1;
    for(auto& nx : g[cur]) {
        int nxt = nx.first;
        if(nxt == p) continue;
        ll cst = nx.second;
        cost[nxt] = cst;
        sz[cur] += dfs(nxt, cur);
    }
    return sz[cur];
}

void hld(int cur, int p, int dep)
{
    ch[cur] = chList.size() - 1;
    chIdx[cur] = chList.back().size();
    chList.back().push_back(cur);
    sg.addValue(num, cost[cur]);
    num++;

    int hv = -1, hvIdx = 0;
    for(auto& nx : g[cur]) {
        int nxt = nx.first;
        if(nxt == p) continue;
        if(hv < sz[nxt]) {
            hv = sz[nxt];
            hvIdx = nxt;
        }
    }
    if(hv != -1) {
        hld(hvIdx, cur, dep);
    }
    for(auto& nx : g[cur]) {
        int nxt = nx.first;
        if(nxt == p || nxt == hvIdx) continue;
        chList.push_back({});
        chFirst[chList.size() - 1] = num;
        chDepth[chList.size() - 1] = dep + 1;
        hld(nxt, cur, dep + 1);
    }
}

ll q1(int a, int b)
{
    ll ret = 0;
    int ach = ch[a];
    int bch = ch[b];
    while(ach != bch) {
        if(chDepth[ach] > chDepth[bch]) {
            int beg = chFirst[ach];
            ret += sg.find(beg, beg + chIdx[a]);
            a = parent[chList[ach][0]];
            ach = ch[a];
        } else {
            int beg = chFirst[bch];
            ret += sg.find(beg, beg + chIdx[b]);
            b = parent[chList[bch][0]];
            bch = ch[b];
        }
    }
    int st = chIdx[a];
    int ed = chIdx[b];
    if(st > ed) swap(st, ed);
    if(st < ed) ret += sg.find(chFirst[ach] + st + 1, chFirst[bch] + ed);

    return ret;
}

int q2(int a, int b, int k)
{
    int aa = a;
    int bb = b;
    k--;
    int aCnt = 0;
    int bCnt = 0;
    int ach = ch[a];
    int bch = ch[b];
    while(ach != bch) {
        if(chDepth[ach] > chDepth[bch]) {
            aCnt += chIdx[a] + 1;
            a = parent[chList[ach][0]];
            ach = ch[a];
        } else {
            bCnt += chIdx[b] + 1;
            b = parent[chList[bch][0]];
            bch = ch[b];
        }
    }
    if(chIdx[a] > chIdx[b]) {
        aCnt += chIdx[a] - chIdx[b];
    } else {
        bCnt += chIdx[b] - chIdx[a];
    }
    a = aa;
    b = bb;
    if(aCnt < k) {
        swap(a, b);
        aCnt = aCnt + bCnt - k;
    } else {
        aCnt = k;
    }

    ach = ch[a];
    bch = ch[b];
    while(ach != bch) {
        if(chDepth[ach] > chDepth[bch]) {
            if(aCnt - chIdx[a] <= 0) {
                int res = chList[ach][chIdx[a] - aCnt];
                return res;
            }
            aCnt -= chIdx[a] + 1;
            a = parent[chList[ach][0]];
            ach = ch[a];
        } else {
            b = parent[chList[bch][0]];
            bch = ch[b];
        }
    }
    int res = chList[ach][chIdx[a] - aCnt];
    return res;
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for(int i = 0; i < n - 1; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        g[a].push_back({ b, c });
        g[b].push_back({ a, c });
    }
    sg.init(n);
    dfs(1, -1);
    chList.push_back({});
    hld(1, -1, 0);
    sg.init2();

    cin >> m;
    for(int i = 0; i < m; ++i) {
        int a;
        cin >> a;
        if(a == 1) {
            int u, v;
            cin >> u >> v;
            cout << q1(u, v) << "\n";
        } else {
            int u, v, k;
            cin >> u >> v >> k;
            cout << q2(u, v, k) << "\n";
        }
    }

    return 0;
}
