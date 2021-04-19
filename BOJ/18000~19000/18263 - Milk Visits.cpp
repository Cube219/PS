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
    vector<int> t[N * 3];
    int stLeaf;

    void init(int n)
    {
        stLeaf = 1;
        while(stLeaf < n) stLeaf *= 2;
    }

    void addValue(int idx, int v)
    {
        t[stLeaf + idx].push_back(v);
    }

    void merge(int node)
    {
        auto& cur = t[node];
        auto& lnode = t[node * 2];
        auto& rnode = t[node * 2 + 1];

        auto lit = lnode.begin();
        auto rit = rnode.begin();
        while(lit != lnode.end() && rit != rnode.end()) {
            if(*lit < *rit) {
                cur.push_back(*lit);
                ++lit;
            } else {
                cur.push_back(*rit);
                ++rit;
            }
        }
        cur.insert(cur.end(), lit, lnode.end());
        cur.insert(cur.end(), rit, rnode.end());
        cur.erase(unique(cur.begin(), cur.end()), cur.end());
    }

    void init2()
    {
        for(int i = stLeaf - 1; i > 0; --i) {
            merge(i);
        }
    }

    bool hasImpl(int cl, int cr, int l, int r, int node, int v)
    {
        if(l <= cl && cr <= r) {
            auto it = lower_bound(t[node].begin(), t[node].end(), v);
            if(it == t[node].end() || *it != v) return false;
            else return true;
        } else if(cr < l || r < cl) return false;
        int m = (cl + cr) / 2;
        return hasImpl(cl, m, l, r, node * 2, v) || hasImpl(m + 1, cr, l, r, node * 2 + 1, v);
    }

    bool has(int l, int r, int v)
    {
        return hasImpl(0, stLeaf - 1, l, r, 1, v);
    }
};

SegTree<100001> sg;
int n, m;
int d[100001];
vector<int> g[100001];

int parent[100001], sz[100001];
int ch[100001], chIdx[100001], chFirstNode[100001], curChIdx, num;
int chFirst[100001], chDepth[100001], chNum;

int dfs(int cur, int par)
{
    parent[cur] = par;
    sz[cur] = 1;
    for(int nxt : g[cur]) {
        if(nxt == par) continue;
        sz[cur] += dfs(nxt, cur);
    }
    return sz[cur];
}

void hld(int cur, int par, int dep)
{
    ch[cur] = chNum - 1;
    chIdx[cur] = curChIdx++;
    sg.addValue(num, d[cur]);
    num++;

    int maxNode = -1, maxv = -1;
    for(int nxt : g[cur]) {
        if(nxt == par) continue;
        if(maxv < sz[nxt]) {
            maxv = sz[nxt];
            maxNode = nxt;
        }
    }

    if(maxNode != -1) {
        hld(maxNode, cur, dep);
    }

    for(int nxt : g[cur]) {
        if(nxt == par || nxt == maxNode) continue;
        chNum++;
        curChIdx = 0;
        chFirst[chNum - 1] = num;
        chFirstNode[chNum - 1] = nxt;
        chDepth[chNum - 1] = dep + 1;
        hld(nxt, cur, dep + 1);
    }
}

bool query(int a, int b, int v)
{
    bool res = false;
    int ach = ch[a];
    int bch = ch[b];
    while(ach != bch && res == false) {
        if(chDepth[ach] > chDepth[bch]) {
            int first = chFirst[ach];
            res = sg.has(first, first + chIdx[a], v);
            a = parent[chFirstNode[ach]];
            ach = ch[a];
        } else {
            int first = chFirst[bch];
            res = sg.has(first, first + chIdx[b], v);
            b = parent[chFirstNode[bch]];
            bch = ch[b];
        }
    }
    if(res == true) return true;
    if(chIdx[a] > chIdx[b]) swap(a, b);
    int first = chFirst[ach];
    res = sg.has(first + chIdx[a], first + chIdx[b], v);

    return res;
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;
    sg.init(n);
    for(int i = 0; i < n; ++i) {
        cin >> d[i];
    }
    for(int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    dfs(0, -1);
    chNum = 1;
    hld(0, -1, 0);
    sg.init2();

    for(int i = 0; i < m; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        a--; b--;
        if(query(a, b, c) == true) cout << "1";
        else cout << "0";
    }

    return 0;
}
