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
int d[100001];
int e1[100001], e2[100001];

void dfs(int cur, int par, int status)
{
    d[cur] = status;
    for(int nxt : g[cur]) {
        if(nxt == par) continue;
        dfs(nxt, cur, status * (-1));
    }
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
        e1[i] = a;
        e2[i] = b;
    }
    dfs(1, -1, -1);
    for(int i = 0; i < n - 1; ++i) {
        if(d[e1[i]] == 1) cout << "0\n";
        else cout << "1\n";
    }

    return 0;
}
