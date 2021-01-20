#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <math.h>
using namespace std;

using ll = long long int;

int r, n;
struct Node
{
    int t;
    int x;
    int y;
};
Node d[100001];
int dp[100001];
int maxV[100001];
int res = -1;

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> r >> n;
    for(int i = 0; i < n; i++) {
        int t, x, y;
        cin >> t >> x >> y;
        d[i] = { t, x, y };
    }
    if(d[0].x - 1 + d[0].y - 1 <= d[0].t) dp[0] = 1;
    else dp[0] = -1;

    if(res < dp[0]) res = dp[0];
    maxV[0] = res;

    for(int i = 1; i < n; i++) {
        if(d[i].x - 1 + d[i].y - 1 <= d[i].t) dp[i] = 1;
        else dp[i] = -1;

        for(int j = i - 1; j >= 0; j--) {
            if(d[i].t - d[j].t >= (r-1) * 2) {
                if(maxV[j] != -1 && maxV[j] + 1 > dp[i]) dp[i] = maxV[j] + 1;
                break;
            }
            if(abs(d[i].x - d[j].x) + abs(d[i].y - d[j].y) > d[i].t - d[j].t) continue;
            if(dp[j] != -1 && dp[j] + 1 > dp[i]) dp[i] = dp[j] + 1;
        }

        if(res < dp[i]) res = dp[i];
        maxV[i] = res;
    }

    if(res == -1) res = 0;
    cout << res;

    return 0;
}
