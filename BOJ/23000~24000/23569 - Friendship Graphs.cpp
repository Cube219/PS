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
bool has[1001][1001];
vector<bool> dp[2];
int c[1001], c1, c2, idx;
bool pos;

void dfs(int cur, int par, int color)
{
    c[cur] = color;
    if(color == -1) c1++;
    else c2++;

    for(int nxt : g[cur]) {
        if(nxt == par) continue;
        if(c[nxt] == 0) {
            dfs(nxt, cur, color * -1);
            if(pos == false) break;
        } else if(c[nxt] == c[cur]) {
            pos = false;
            break;
        }
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
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            has[i][j] = true;
        }
        has[i][i] = false;
    }
    for(int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        has[u][v] = has[v][u] = false;
    }
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            if(has[i][j]) g[i].push_back(j);
        }
    }

    int res = 987654321;
    dp[0].resize(1001, false);
    dp[1].resize(1001, false);
    dp[0][0] = true;
    for(int i = 0; i < n; ++i) {
        if(c[i] != 0) continue;

        c1 = 0; c2 = 0;
        pos = true;
        dfs(i, -1, 1);
        if(pos == false) break;

        int diff = abs(c1 - c2);
        for(int j = 0; j <= 1000; ++j) {
            if(dp[0][j] == false) continue;
            if(j + diff <= 1000) dp[1][j + diff] = true;
            dp[1][abs(j - diff)] = true;
        }
        for(int j = 0; j <= 1000; ++j) {
            dp[0][j] = false;
        }
        swap(dp[0], dp[1]);
    }

    if(pos == true) {
        for(int i = 0; i <= 1000; ++i) {
            if(dp[0][i] == true) {
                res = i;
                break;
            }
        }
    }
    if(res == 987654321) res = -1;

    cout << res;

    return 0;
}
