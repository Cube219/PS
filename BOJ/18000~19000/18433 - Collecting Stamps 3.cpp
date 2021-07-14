#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;
constexpr ll INF = 2305843009213693952;

struct Node
{
    ll pos;
    ll time;
};

int n, l, n2;
Node d[405];
ll dp[405][405][201][2];

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> l;
    for(int i = 0; i < n; ++i) {
        cin >> d[i + n + 1].pos;
    }
    for(int i = 0; i < n; ++i) {
        cin >> d[i + n + 1].time;
    }
    for(int i = 0; i < n; ++i) {
        d[i] = d[i + n + 1];
        d[i].pos -= l;
    }
    n2 = n * 2 + 1;
    for(int i = 0; i <= n2; ++i) {
        for(int j = 0; j <= n2; ++j) {
            for(int k = 0; k <= n; ++k) {
                dp[i][j][k][0] = INF;
                dp[i][j][k][1] = INF;
            }
        }
    }
    dp[n][n][0][0] = 0;
    dp[n][n][0][1] = 0;

    int res = 0;
    for(int sz = 2; sz <= n + 1; ++sz) {
        for(int l = n - sz + 1; l <= n; ++l) {
            int r = l + sz - 1;
            // left
            for(int i = 0; i <= n; ++i) {
                ll minv = INF;
                // l+1, r
                if(l < n) {
                    ll gap = d[l + 1].pos - d[l].pos;
                    minv = min(minv, dp[l + 1][r][i][0] + gap);
                    if(i > 0 && dp[l + 1][r][i - 1][0] + gap <= d[l].time) {
                        minv = min(minv, dp[l + 1][r][i - 1][0] + gap);
                    }
                    gap = d[r].pos - d[l].pos;
                    minv = min(minv, dp[l + 1][r][i][1] + gap);
                    if(i > 0 && dp[l + 1][r][i - 1][1] + gap <= d[l].time) {
                        minv = min(minv, dp[l + 1][r][i - 1][1] + gap);
                    }
                }
                dp[l][r][i][0] = minv;
                if(minv < INF) res = max(res, i);
            }

            // right
            for(int i = 0; i <= n; ++i) {
                ll minv = INF;
                // l, r-1
                if(r > n) {
                    ll gap = d[r].pos - d[l].pos;
                    minv = min(minv, dp[l][r - 1][i][0] + gap);
                    if(i > 0 && dp[l][r - 1][i - 1][0] + gap <= d[r].time) {
                        minv = min(minv, dp[l][r - 1][i - 1][0] + gap);
                    }
                    gap = d[r].pos - d[r - 1].pos;
                    minv = min(minv, dp[l][r - 1][i][1] + gap);
                    if(i > 0 && dp[l][r-1][i-1][1] + gap <= d[r].time) {
                        minv = min(minv, dp[l][r - 1][i - 1][1] + gap);
                    }
                }
                dp[l][r][i][1] = minv;
                if(minv < INF) res = max(res, i);
            }
        }
    }

    cout << res;

    return 0;
}
