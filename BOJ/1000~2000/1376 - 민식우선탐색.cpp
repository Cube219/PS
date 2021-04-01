#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

class SegTree
{
public:
    int* t;
    int stLeaf, n;
    int cnt;

    void init(int _n)
    {
        n = _n;
        cnt = n;

        stLeaf = 1;
        while(stLeaf < n) stLeaf *= 2;
        t = (int*)malloc(sizeof(int) * stLeaf * 2 + 1);

        for(int i = 0; i < stLeaf; ++i) {
            if(i < n) t[stLeaf + i] = 1;
            else t[stLeaf + i] = 0;
        }
        for(int i = stLeaf - 1; i > 0; --i) {
            t[i] = t[i * 2] + t[i * 2 + 1];
        }
    }
    void shutdown()
    {
        free(t);
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

    void add(int l)
    {
        t[stLeaf + l] = 0;
        int node = stLeaf + l;
        node /= 2;
        while(node > 0) {
            t[node] = t[node * 2] + t[node * 2 + 1];
            node /= 2;
        }
    }

    void remove(int idx)
    {
        add(idx);
        cnt--;
    }

    int getMinIdx()
    {
        if(t[stLeaf] == 1) return 0;

        int l = 0, r = n - 1;
        while(l < r) {
            int m = (l + r) / 2;
            int v = find(0, m);
            if(v < 1) {
                l = m + 1;
            } else {
                r = m;
            }
        }
        return r;
    }

    int getMidIdx()
    {
        int midcnt = (cnt + 1) / 2;
        int l = 0, r = n - 1;
        while(l < r) {
            int m = (l + r) / 2;
            int v = find(0, m);
            if(v < midcnt) {
                l = m + 1;
            } else {
                r = m;
            }
        }
        return r;
    }
};


int n, m;
vector<int> g[100001];
SegTree sg[100001];
vector<int> res;

void dfs(int cur)
{
    res.push_back(cur);
    for(int adj : g[cur]) {
        int idx = lower_bound(g[adj].begin(), g[adj].end(), cur) - g[adj].begin();
        sg[adj].remove(idx);
    }

    while(sg[cur].cnt > 0){
        int nxtidx;
        if(sg[cur].cnt % 2 == 0) {
            nxtidx = sg[cur].getMinIdx();
        } else {
            nxtidx = sg[cur].getMidIdx();
        }
        dfs(g[cur][nxtidx]);
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
    for(int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        if(a == b) continue;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    for(int i = 1; i <= n; ++i) {
        sort(g[i].begin(), g[i].end());
        g[i].erase(unique(g[i].begin(), g[i].end()), g[i].end());
        sg[i].init(g[i].size());
    }

    dfs(1);

    for(int i = 0; i < res.size(); ++i) {
        cout << res[i] << " ";
    }

    for(int i = 1; i <= n; ++i) {
        sg[i].shutdown();
    }

    return 0;
}
