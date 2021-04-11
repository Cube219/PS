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
int color[100001];
int has[100001];
vector<int> res;

void dfs(int cur, int par)
{
    if(has[color[cur]] == 0) {
        res.push_back(cur);
    }

    has[color[cur]]++;
    for(int nxt : g[cur]) {
        if(nxt == par) continue;
        dfs(nxt, cur);
    }
    has[color[cur]]--;
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for(int i = 1; i <= n; ++i) {
        cin >> color[i];
    }
    for(int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    dfs(1, -1);

    sort(res.begin(), res.end());
    for(int i = 0; i < res.size(); ++i) {
        cout << res[i] << "\n";
    }

    return 0;
}
