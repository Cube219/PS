#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;
constexpr ll MOD = 1000000007;

int n, m;
vector<int> g[300001];
int par[300001][21], dep[300001], h[300001];
vector<pair<int, int>> g2[300001];
int dir[300001];

void dfs(int cur, int p, int d)
{
    dep[cur] = d;
    h[cur] = d;
    par[cur][0] = p;
    for(int nxt : g[cur]) {
        if(nxt == p) continue;
        dfs(nxt, cur, d + 1);
    }
}

void build()
{
    for(int j = 1; j < 20; ++j) {
        for(int i = 0; i < n; ++i) {
            int p = par[i][j - 1];
            par[i][j] = par[p][j - 1];
        }
    }
}

int lca(int a, int b)
{
    if(dep[a] < dep[b]) swap(a, b);
    int gap = dep[a] - dep[b];
    for(int i = 0; i < 20 && gap > 0; ++i) {
        if(gap & 1) {
            a = par[a][i];
        }
        gap >>= 1;
    }
    if(a != b) {
        for(int i = 20 - 1; i >= 0; --i) {
            if(par[a][i] != par[b][i]) {
                a = par[a][i];
                b = par[b][i];
            }
        }
        a = par[a][0];
    }
    return a;
}

int dfs2(int cur, int p)
{
    for(int nxt : g[cur]) {
        if(nxt == p) continue;
        int ph = dfs2(nxt, cur);
        h[cur] = min(h[cur], ph);
        if(ph < dep[cur]) {
            g2[cur].push_back({ nxt, 0 });
            g2[nxt].push_back({ cur, 0 });
        }
    }
    return h[cur];
}

bool dfs3(int cur, int curdir)
{
    if(dir[cur] != 0) return dir[cur] == curdir;

    dir[cur] = curdir;
    for(auto& nx : g2[cur]) {
        int nxt = nx.first;
        int isrev = nx.second;

        bool res;
        if(isrev == 0) {
            res = dfs3(nxt, curdir);
        } else {
            res = dfs3(nxt, curdir * -1);
        }
        if(res == false) return false;
    }
    return true;
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;
    for(int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    dfs(0, -1, 0);
    build();

    for(int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        int c = lca(a, b);
        h[a] = min(h[a], dep[c]);
        h[b] = min(h[b], dep[c]);
        if(a != c && b != c) {
            g2[a].push_back({ b, 1 });
            g2[b].push_back({ a, 1 });
        }
    }
    dfs2(0, -1);

    ll res = 1;
    for(int i = 1; i < n; ++i) {
        if(dir[i] != 0) continue;
        if(dfs3(i, 1) == false) {
            res = 0;
            break;
        }
        res *= 2;
        res %= MOD;
    }

    cout << res;

    return 0;
}
