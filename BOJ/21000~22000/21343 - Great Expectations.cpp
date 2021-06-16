#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <iomanip>
#include <vector>
using namespace std;

using ll = long long int;

struct Node
{
    int t;
    double p;
    int err;
};

int n, r, m;
Node d[51];
double cur;
double dp[55][5005];

double p(double k)
{
    for(int i = 0; i < r; ++i) {
        dp[m + 1][i] = n - d[m].t;
    }

    for(int i = m; i >= 1; --i) {
        for(int j = 0; j < r; ++j) {
            dp[i][j] = d[i].p * dp[i + 1][j] + d[i].t - d[i - 1].t;
            if(j + d[i].err >= r) {
                dp[i][j] += (1.0 - d[i].p) * k;
            } else {
                dp[i][j] += (1.0 - d[i].p) * min(k, dp[i + 1][j + d[i].err] + d[i].err);
            }
        }
    }
    return dp[1][0];
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> r >> m;
    for(int i = 1; i <= m; ++i) {
        cin >> d[i].t >> d[i].p >> d[i].err;
    }
    r -= n;

    double l = 0.0, r = 1000000000;
    for(int i = 0; i < 1000; ++i) {
        double mid = (l + r) / 2.0;
        cur = mid;

        double v = p(cur);
        if(v < cur) {
            r = v;
        } else {
            l = v;
        }
    }
    cout << fixed << setprecision(8) << l;

    return 0;
}
