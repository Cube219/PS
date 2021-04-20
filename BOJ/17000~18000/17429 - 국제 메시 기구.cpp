#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = unsigned long long int;
constexpr ll MOD = 1ll << 32;

template <int N>
class SegTree
{
public:
    ll t[N * 3], addlazy[N * 3], mullazy[N * 3];
    int stLeaf, n;

    void init(int n)
    {
        stLeaf = 1;
        while(stLeaf < n) stLeaf *= 2;
        for(int i = stLeaf * 2; i > 0; --i) {
            mullazy[i] = 1;
        }
    }

    void propagate(int l, int r, int node)
    {
        if(addlazy[node] == 0 && mullazy[node] == 1) return;

        if(node < stLeaf) {
            addlazy[node * 2] *= mullazy[node];
            addlazy[node * 2] %= MOD;
            addlazy[node * 2] += addlazy[node];
            addlazy[node * 2] %= MOD;
            mullazy[node * 2] *= mullazy[node];
            mullazy[node * 2] %= MOD;

            addlazy[node * 2 + 1] *= mullazy[node];
            addlazy[node * 2 + 1] %= MOD;
            addlazy[node * 2 + 1] += addlazy[node];
            addlazy[node * 2 + 1] %= MOD;
            mullazy[node * 2 + 1] *= mullazy[node];
            mullazy[node * 2 + 1] %= MOD;
        }
        t[node] *= mullazy[node];
        t[node] += (r - l + 1) * addlazy[node];
        t[node] %= MOD;
        addlazy[node] = 0;
        mullazy[node] = 1;
    }

    ll findImpl(int cl, int cr, int l, int r, int node)
    {
        propagate(cl, cr, node);
        if(l <= cl && cr <= r) return t[node];
        else if(cr < l || r < cl) return 0;
        int m = (cl + cr) / 2;
        return (findImpl(cl, m, l, r, node * 2) + findImpl(m + 1, cr, l, r, node * 2 + 1)) % MOD;
    }

    void addImpl(int cl, int cr, int l, int r, int node, ll v, bool isMul)
    {
        propagate(cl, cr, node);
        if(l <= cl && cr <= r) {
            if(isMul == true) {
                addlazy[node] *= v;
                addlazy[node] %= MOD;
                mullazy[node] *= v;
                mullazy[node] %= MOD;
            } else {
                addlazy[node] += v;
                addlazy[node] %= MOD;
            }
            propagate(cl, cr, node);
            return;
        } else if(cr < l || r < cl) return;
        int m = (cl + cr) / 2;
        addImpl(cl, m, l, r, node * 2, v, isMul);
        addImpl(m + 1, cr, l, r, node * 2 + 1, v, isMul);
        t[node] = (t[node * 2] + t[node * 2 + 1]) % MOD;
    }

    ll find(int l, int r)
    {
        return findImpl(0, stLeaf - 1, l, r, 1);
    }

    void add(int l, int r, ll v)
    {
        addImpl(0, stLeaf - 1, l, r, 1, v, false);
    }

    void mul(int l, int r, ll v)
    {
        addImpl(0, stLeaf - 1, l, r, 1, v, true);
    }
};

int n, q;
vector<int> g[500001];

SegTree<500001> sg;
int sz[500001], parent[500001];
int ch[500001], chIdx[500001], curChIdx;
int chFirst[500001], chDepth[500001], chFirstNode[500001], chNum;
int st[500001], en[500001], num;

int dfs(int cur, int par)
{
    sz[cur] = 1;
    parent[cur] = par;
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
    st[cur] = num++;

    int mxNode = -1, mx = -1;
    for(int nxt : g[cur]) {
        if(nxt == par) continue;
        if(mx < sz[nxt]) {
            mx = sz[nxt];
            mxNode = nxt;
        }
    }
    if(mxNode != -1) {
        hld(mxNode, cur, dep);
    }

    for(int nxt : g[cur]) {
        if(nxt == par || nxt == mxNode) continue;
        chNum++;
        chFirst[chNum - 1] = num;
        chDepth[chNum - 1] = dep + 1;
        chFirstNode[chNum - 1] = nxt;
        curChIdx = 0;
        hld(nxt, cur, dep + 1);
    }
    en[cur] = num - 1;
}

ll query(int a, int b, ll v, bool isMul, bool isfind)
{
    ll ret = 0;

    int ach = ch[a];
    int bch = ch[b];
    while(ach != bch) {
        int l, r;
        if(chDepth[ach] > chDepth[bch]) {
            int beg = chFirst[ach];
            l = chFirst[ach];
            r = l + chIdx[a];
            a = parent[chFirstNode[ach]];
            ach = ch[a];
        } else {
            l = chFirst[bch];
            r = l + chIdx[b];
            b = parent[chFirstNode[bch]];
            bch = ch[b];
        }
        if(isfind == false) {
            if(isMul == false) sg.add(l, r, v);
            else sg.mul(l, r, v);
        } else {
            ret += sg.find(l, r);
            ret %= MOD;
        }
    }
    if(chIdx[a] > chIdx[b]) swap(a, b);
    int l = chFirst[ach] + chIdx[a];
    int r = chFirst[ach] + chIdx[b];
    if(isfind == false) {
        if(isMul == false) sg.add(l, r, v);
        else sg.mul(l, r, v);
    } else {
        ret += sg.find(l, r);
        ret %= MOD;
    }

    return ret;
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> q;
    for(int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    sg.init(n);
    dfs(0, -1);
    chNum = 1;
    hld(0, -1, 0);

    for(int i = 0; i < q; ++i) {
        int a, b, c, d;
        cin >> a;
        switch(a) {
            case 1:
                cin >> b >> c;
                b--;
                sg.add(st[b], en[b], c);
                break;
            case 2:
                cin >> b >> c >> d;
                b--; c--;
                query(b, c, d, false, false);
                break;
            case 3:
                cin >> b >> c;
                b--;
                sg.mul(st[b], en[b], c);
                break;
            case 4:
                cin >> b >> c >> d;
                b--; c--;
                query(b, c, d, true, false);
                break;
            case 5:
                cin >> b;
                b--;
                cout << sg.find(st[b], en[b]) << "\n";
                break;
            case 6:
                cin >> b >> c;
                b--; c--;
                cout << query(b, c, 0, false, true) << "\n";
                break;
        }
    }

    return 0;
}
