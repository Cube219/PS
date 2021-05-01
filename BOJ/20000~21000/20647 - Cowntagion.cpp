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
vector<int> g[100001];

int dfs(int cur, int par)
{
    int cnum = 0;
    for(int nxt : g[cur]) {
        if(nxt == par) continue;
        cnum++;
    }
    int ret = 0;
    int d = 1;
    while(d <= cnum) {
        ret++;
        d *= 2;
    }

    for(int nxt : g[cur]) {
        if(nxt == par) continue;
        ret += dfs(nxt, cur) + 1;
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

    cin >> n;
    for(int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    int res = dfs(1, -1);

    cout << res;

    return 0;
}
