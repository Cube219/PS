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

int n, m;
ll d[301];
ll dp[305][305][2];
ll res;

ll p(int l, int r, int isright, int remain)
{
    if(remain <= 0) return 0;
    if(dp[l][r][isright] != INF) return dp[l][r][isright];

    ll& curdp = dp[l][r][isright];

    if(l > 0) {
        if(isright == 0) {
            curdp = min(curdp, p(l - 1, r, 0, remain - 1) + (ll)remain * (d[l] - d[l - 1]));
        } else {
            curdp = min(curdp, p(l - 1, r, 0, remain - 1) + (ll)remain * (d[r] - d[l - 1]));
        }
    }
    if(r < n - 1) {
        if(isright == 0) {
            curdp = min(curdp, p(l, r + 1, 1, remain - 1) + (ll)remain * (d[r + 1] - d[l]));
        } else {
            curdp = min(curdp, p(l, r + 1, 1, remain - 1) + (ll)remain * (d[r + 1] - d[r]));
        }
    }
    return curdp;
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
        cin >> d[i];
    }
    n++;
    sort(d, d + n);
    int zidx = 0;
    for(int i = 0; i < n; ++i) {
        if(d[i] == 0) {
            zidx = i;
            break;
        }
    }
    for(int i = 1; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            for(int k = 0; k < n; ++k) {
                dp[j][k][0] = INF;
                dp[j][k][1] = INF;
            }
        }
        ll r = p(zidx, zidx, 0, i);
        res = max(res, m * i - r);
        r = p(zidx, zidx, 1, i);
        res = max(res, m * i - r);
    }
    cout << res;

    return 0;
}
