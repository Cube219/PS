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
vector<pair<int, ll>> g[40001];
int par[400001][20];
ll sum[400001][20];
int dep[400001];

void dfs(int cur, int p, int d)
{
    par[cur][0] = p;
    dep[cur] = d;
    for(auto& nx : g[cur]) {
        int nxt = nx.first;
        ll cost = nx.second;
        if(nxt == p) continue;

        sum[nxt][0] = cost;
        dfs(nxt, cur, d + 1);
    }
}

void p()
{
    for(int i = 1; i < 20; ++i) {
        for(int j = 1; j <= n; ++j) {
            int p = par[j][i - 1];
            par[j][i] = par[p][i - 1];
            sum[j][i] = sum[j][i - 1] + sum[p][i - 1];
        }
    }
}

ll process(int a, int b)
{
    ll res = 0;

    if(dep[a] > dep[b]) swap(a, b);
    int gap = dep[b] - dep[a];
    int idx = 0;
    while(gap > 0) {
        if(gap % 2 == 1) {
            res += sum[b][idx];
            b = par[b][idx];
        }
        gap /= 2;
        idx++;
    }
    if(a != b) {
        for(int i = 20 - 1; i >= 0; --i) {
            if(par[a][i] != par[b][i]) {
                res += sum[a][i];
                res += sum[b][i];
                a = par[a][i];
                b = par[b][i];
            }
        }
        res += sum[a][0];
        res += sum[b][0];
    }
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

    dfs(1, 0, 0);
    p();

    cin >> m;
    for(int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        cout << process(a, b) << "\n";
    }

    return 0;
}
