#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;

using ll = long long int;

vector<vector<int>> cost;
int n, m;
vector<vector<int>> g;
vector<vector<int>> dp;

void bt(int i, int j, int mymask, int parmask, int c)
{
    if(j >= m) {
        dp[0][mymask] = max(dp[0][mymask], c + dp[1][parmask]);
        return;
    }
    int bit = 1 << j;
    if((mymask & bit) > 0) {
        // 세로
        if(i > 0) {
            bt(i, j + 1, mymask, parmask ^ bit, c + cost[g[i - 1][j]][g[i][j]]);
        }
        // 가로
        int bit2 = 1 << (j + 1);
        if((mymask & bit2) > 0) {
            bt(i, j + 2, mymask, parmask, c + cost[g[i][j]][g[i][j + 1]]);
        }
    } else {
        bt(i, j + 1, mymask, parmask, c);
    }
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cost.resize(5);
    cost[0] = { 10, 8, 7, 5, 1 };
    cost[1] = { 8, 6, 4, 3, 1 };
    cost[2] = { 7, 4, 3, 2, 1 };
    cost[3] = { 5, 3, 2, 2, 1 };
    cost[4] = { 1, 1, 1, 1, 0 };

    cin >> n >> m;
    g.resize(n, vector<int>(m));
    for(int i = 0; i < n; ++i) {
        string str;
        cin >> str;
        for(int j = 0; j < m; ++j) {
            g[i][j] = str[j] - 'A';
            if(str[j] == 'F') g[i][j]--;
        }
    }

    int mm = 1 << m;
    dp.resize(2, vector<int>(mm, 0));
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < mm; ++j) {
            bt(i, 0, j, mm - 1, 0);
        }
        for(int j = 0; j < mm; ++j) {
            for(int k = j; k > 0; k = (k - 1) & j) {
                dp[0][j] = max(dp[0][j], dp[0][k]);
            }
        }
        swap(dp[0], dp[1]);
        fill(dp[0].begin(), dp[0].end(), 0);
    }

    int res = 0;
    for(int i = 0; i < mm; ++i) {
        res = max(res, dp[1][i]);
    }
    cout << res;

    return 0;
}
