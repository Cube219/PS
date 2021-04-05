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
    ll t[N * 3], lazy[N * 3];
    int stLeaf, n;

    void init(int n)
    {
        stLeaf = 1;
        while(stLeaf < n) stLeaf *= 2;
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

    void add(int l, ll v)
    {
        int node = stLeaf + l;
        t[node] += v;
        node /= 2;
        while(node > 0) {
            t[node] = t[node * 2] + t[node * 2 + 1];
            node /= 2;
        }
    }
};

SegTree<200001> sg;
int n, c;
vector<int> g[200001];
int depth[200001];
int st[200001], ed[200001], num;

void dfs(int cur, int p, int dep)
{
    st[cur] = num;
    depth[cur] = dep;
    num++;
    for(int nxt : g[cur]) {
        if(nxt == p) continue;
        dfs(nxt, cur, dep + 1);
    }
    ed[cur] = num - 1;
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> c;
    for(int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    dfs(c, -1, 1);

    sg.init(n);
    int num;
    cin >> num;
    for(int i = 0; i < num; ++i) {
        int a, b;
        cin >> a >> b;
        if(a == 1) {
            sg.add(st[b], 1);
        } else {
            ll cnt = sg.find(st[b], ed[b]);
            cout << depth[b] * cnt << "\n";
        }
    }

    return 0;
}
