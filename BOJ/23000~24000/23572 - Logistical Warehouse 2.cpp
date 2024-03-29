#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;
constexpr int INF = 987654321;

int n, k;
vector<int> g[100001];
int res;

int dfs(int cur, int par)
{
    int mx = 0, mn = INF;
    int cnum = 0;
    for(int nxt : g[cur]) {
        if(nxt == par) continue;

        cnum++;
        int r = dfs(nxt, cur);
        mx = max(mx, r);
        mn = min(mn, r);
    }

    int ret = mx;
    if(cnum >= 2) {
        if(mx + mn <= k * 2 + 1) {
            ret = mn;
        }
    }

    if(par == -1) {
        // root
        if(ret > k) res++;
        return 0;
    }
    if(cnum == 0) {
        // leaf
        return k + 2;
    }

    if(ret >= k * 2 + 1) {
        res++;
        ret = 0;
    }
    return ret + 1;
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> k;
    for(int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    dfs(1, -1);

    if(n == 1) res = 1;
    cout << res;

    return 0;
}
