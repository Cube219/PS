#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;

using ll = long long int;

int n, m;
vector<int> g[100001];
int p[100001][32];
int cenP[100001];
int dep[100001], sz[100001];
bool visit[100001];
bool color[100001];
multiset<int> s[100001];

void dfs(int cur, int par, int cnt)
{
    dep[cur] = cnt;
    p[cur][0] = par;
    if(par == -1) p[cur][0] = 0;
    for(int nxt : g[cur]) {
        if(nxt == par) continue;
        dfs(nxt, cur, cnt + 1);
    }
}

void makesparse()
{
    for(int i = 1; i < 30; ++i) {
        for(int j = 1; j <= n; ++j) {
            int curp = p[j][i - 1];
            if(curp > 0) p[j][i] = p[curp][i - 1];
        }
    }
}

int getSize(int cur, int par)
{
    sz[cur] = 1;
    for(int nxt : g[cur]) {
        if(nxt == par || visit[nxt] == true) continue;
        sz[cur] += getSize(nxt, cur);
    }
    return sz[cur];
}
int getCen(int cur, int par, int size)
{
    for(int nxt : g[cur]) {
        if(nxt == par || visit[nxt] == true) continue;
        if(sz[nxt] > size / 2) return getCen(nxt, cur, size);
    }
    return cur;
}
void mkCen(int cur, int par)
{
    int size = getSize(cur, -1);
    int cen = getCen(cur, -1, size);

    visit[cen] = true;
    cenP[cen] = par;
    for(int nxt : g[cen]) {
        if(nxt == par || visit[nxt] == true) continue;
        mkCen(nxt, cen);
    }
}

int lca(int u, int v)
{
    int uDep = dep[u];
    int vDep = dep[v];
    if(uDep < vDep) {
        swap(u, v);
        swap(uDep, vDep);
    }
    int gap = uDep - vDep;
    int i = 0;
    while(gap > 0) {
        if(gap % 2 == 1) {
            u = p[u][i];
        }
        i++;
        gap /= 2;
    }
    if(u != v) {
        for(int i = 30 - 1; i >= 0; --i) {
            if(p[u][i] > 0 && p[u][i] != p[v][i]) {
                u = p[u][i];
                v = p[v][i];
            }
        }
        u = p[u][0];
    }
    return u;
}

int getdis(int u, int v)
{
    return dep[u] + dep[v] - 2 * dep[lca(u, v)];
}

void update(int idx)
{
    color[idx] = !color[idx];
    int cur = idx;
    while(cur != -1) {
        int dis = getdis(idx, cur);
        if(color[idx] == true) s[cur].insert(dis);
        else s[cur].erase(s[cur].find(dis));
        cur = cenP[cur];
    }
}

int get(int idx)
{
    int res = 987654321;
    int cur = idx;
    while(cur != -1) {
        int dis = getdis(idx, cur);
        if(s[cur].size() > 0) {
            res = min(res, *s[cur].begin() + dis);
        }
        cur = cenP[cur];
    }
    if(res == 987654321) res = -1;
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
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    dfs(1, -1, 0);
    makesparse();
    mkCen(1, -1);

    cin >> m;
    for(int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        if(a == 1) {
            update(b);
        } else {
            cout << get(b) << "\n";
        }
    }

    return 0;
}
