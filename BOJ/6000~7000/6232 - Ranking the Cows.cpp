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
vector<int> g[1001];
bool ck[1001];

void dfs(int cur, int idx)
{
    ck[cur] = true;
    for(int nxt : g[cur]) {
        if(ck[nxt] == true) continue;
        dfs(nxt, idx);
    }
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;
    for(int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        g[a].push_back(b);
    }

    int sum = 0;
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            ck[j] = false;
        }
        dfs(i, i);
        for(int j = 0; j < n; ++j) {
            if(ck[j] == true) sum++;
        }
    }
    int sum2 = n * (n + 1) / 2;
    cout << sum2 - sum;

    return 0;
}
