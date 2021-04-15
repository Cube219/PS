#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

int n, m;
vector<int> g[100001];
int par[100001][18];
int sum[100001][18];
int dep[100001];

void dfs(int cur, int p, int d)
{
    par[cur][0] = p;
    dep[cur] = d;
    for(int nxt : g[cur]) {
        if(nxt == p) continue;

        sum[nxt][0] = 1;
        dfs(nxt, cur, d + 1);
    }
}

void p()
{
    for(int i = 1; i < 18; ++i) {
        for(int j = 1; j <= n; ++j) {
            int p = par[j][i - 1];
            par[j][i] = par[p][i - 1];
            sum[j][i] = sum[j][i - 1] + sum[p][i - 1];
        }
    }
}

int process(int a, int b)
{
    if(dep[a] > dep[b]) swap(a, b);
    int gap = dep[b] - dep[a];
    int idx = 0;
    while(gap > 0) {
        if(gap % 2 == 1) {
            b = par[b][idx];
        }
        gap /= 2;
        idx++;
    }
    if(a != b) {
        for(int i = 18 - 1; i >= 0; --i) {
            if(par[a][i] != par[b][i]) {
                a = par[a][i];
                b = par[b][i];
            }
        }
        a = par[a][0];
    }
    return a;
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

    dfs(1, 0, 0);
    p();

    cin >> m;
    for(int i = 0; i < m; ++i) {
        int r, u, v;
        cin >> r >> u >> v;

        int uv = process(u, v);
        int rUV = process(uv, r);
        if(rUV != uv) {
            cout << uv << "\n";
        } else {
            int ru = process(r, u);
            int rv = process(r, v);
            int t = process(ru, rv);
            if(t == ru) cout << rv << "\n";
            else cout << ru << "\n";
        }
    }

    return 0;
}
