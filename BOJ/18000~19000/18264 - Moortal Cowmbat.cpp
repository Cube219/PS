#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;
constexpr ll INF = 9999999999999;

int n, m, k;
char str[100005];
int dis[30][30];
ll sum[100005][30];
ll dp[100005][30];


int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m >> k >> str;
    for(int i = 0; i < m; ++i) {
        for(int j = 0; j < m; ++j) {
            cin >> dis[i][j];
        }
    }

    for(int i = 0; i < m; ++i) {
        for(int j = 0; j < m; ++j) {
            for(int k = 0; k < m; ++k) {
                if(dis[j][k] > dis[j][i] + dis[i][k]) {
                    dis[j][k] = dis[j][i] + dis[i][k];
                }
            }
        }
    }

    for(int i = 0; i < m; ++i) {
        sum[0][i] = dis[str[0] - 'a'][i];
        for(int j = 1; j < n; ++j) {
            sum[j][i] = sum[j - 1][i] + dis[str[j] - 'a'][i];
        }
    }

    for(int i = 0; i < m; ++i) {
        for(int j = 0; j < k - 1; ++j) {
            dp[j][i] = INF;
        }
        dp[k - 1][i] = sum[k - 1][i];
    }

    for(int i = k; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            ll cost = dis[str[i] - 'a'][j];
            ll mn = INF;
            for(int z = 0; z < m; ++z) {
                mn = min(mn, dp[i - k][z]);
            }
            ll cost2 = sum[i - 1][j] - sum[i - k][j];
            dp[i][j] = cost + mn + cost2;
            dp[i][j] = min(dp[i][j], dp[i - 1][j] + cost);
        }
    }

    ll res = INF;
    for(int i = 0; i < m; ++i) {
        res = min(res, dp[n - 1][i]);
    }

    cout << res;

    return 0;
}
