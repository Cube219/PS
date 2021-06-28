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

struct Node
{
    int before, after;
};

int n, m;
Node d[301];
int dp[301][301];

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> m >> n;
    for(int i = 0; i < n; ++i) {
        cin >> d[i].before >> d[i].after;
    }

    for(int i = 0; i < n; ++i) {
        int bsum = 0;
        int asum = 0;
        for(int j = 0; j < n; ++j) {
            dp[i][j] = INF;
        }
        for(int j = i; j >= 0; --j) {
            bsum += d[j].before;
            asum += d[j].after;
            if(bsum > m || asum > m) break;
            if(j == 0) {
                dp[i][j] = 3;
                break;
            }

            int bsum2 = 0;
            for(int k = j - 1; k >= 0; --k) {
                bsum2 += d[k].after;
                if(bsum + bsum2 > m) {
                    dp[i][j] = min(dp[i][j], dp[j - 1][k] + 2);
                } else {
                    dp[i][j] = min(dp[i][j], dp[j - 1][k] + 1);
                }
            }
        }
    }
    int res = INF;
    for(int i = 0; i < n; ++i) {
        res = min(res, dp[n - 1][i]);
    }
    cout << res;

    return 0;
}
