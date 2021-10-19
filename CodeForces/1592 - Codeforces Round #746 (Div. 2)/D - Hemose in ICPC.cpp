#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

int n;
vector<int> g[1005];
int p[1005], d[1005], d2[1005], dnum;

void dfs(int cur, int par)
{
    d2[dnum] = cur;
    d[cur] = ++dnum;
    p[cur] = par;
    for(int nxt : g[cur]) {
        if(nxt == par) continue;
        dfs(nxt, cur);
    }
}

int ask(int l, int r)
{
    cout << "? " << r - l + 1 << " ";
    for(int i = l; i <= r; ++i) {
        cout << d2[i] << " ";
    }
    cout << endl;
    int res;
    cin >> res;
    return res;
}

int main(void)
{
    cin >> n;
    for(int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    dfs(1, -1);

    int v = ask(0, n - 1);

    int l = 0, r = n - 1;
    while(l + 1 < r) {
        int m = (l + r) / 2;
        int v2 = ask(0, m);
        if(v2 == v) {
            r = m;
        } else {
            l = m;
        }
    }
    cout << "! " << d2[r] << " " << p[d2[r]] << endl;

    return 0;
}
