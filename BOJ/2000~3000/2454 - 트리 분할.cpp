#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

int n, k;
vector<int> g[300001];
int res;

int dfs(int cur, int par)
{
    vector<int> d;
    for(int nxt : g[cur]) {
        if(nxt == par) continue;
        int t = dfs(nxt, cur);
        if(t % (k + 1) > 0) {
            d.push_back(t);
        }
    }
    sort(d.begin(), d.end());
    if(d.size() > 1) {
        if(d[0] + d[1] + 1 <= k + 1) {
            res--;
            return 0;
        }
    }
    if(d.size() > 0) {
        if(d[0] + 1 <= k + 1) {
            return d[0] + 1;
        }
    }
    res++;
    return 1;
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

    cout << res;

    return 0;
}
