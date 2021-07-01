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

int n, m;
int d[] = { 1, 18, 4, 13, 6, 10, 15, 2, 17, 3, 19, 7, 16, 8, 11, 14, 9, 12, 5, 20 };

double dp[505][505][2];

double ck(int a, int b, double s)
{
    // 1 turn
    double t = 0.0;
    for(int i = 0; i < 20; ++i) {
        int idx[3] = { i - 1, i, i + 1 };
        if(idx[0] < 0) idx[0] += 20;
        if(idx[2] >= 20) idx[2] -= 20;

        double v = 0;
        for(int j = 0; j < 3; ++j) {
            if(b - d[idx[j]] < 0) {
                v += 1.0 - s;
            } else {
                v += 1.0 - dp[a][b - d[idx[j]]][0];
            }
        }
        v /= 3;
        t = max(t, v);
    }
    double res = 0.0;
    for(int i = 0; i < 20; ++i) {
        if(a - d[i] < 0) {
            res += 1.0 - t;
        } else {
            res += 1.0 - dp[a - d[i]][b][1];
        }
    }
    return res /= 20;
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    m = 20;

    for(int i = 0; i <= 501; ++i) {
        for(int j = 0; j <= 501; ++j) {
            dp[i][j][0] = -1;
            dp[i][j][1] = -1;
        }
    }
    for(int i = 1; i <= 501; ++i) {
        dp[i][0][0] = 0;
        dp[i][0][1] = 1;
        dp[0][i][0] = 1;
        dp[0][i][1] = 0;
    }

    for(int i = 1; i <= 501; ++i) {
        for(int j = 1; j <= 501; ++j) {
            // 0 turn
            if(i < 20) {
                double l = 0, r = 1;
                while(r - l > 10e-9) {
                    double mid = (l + r) / 2;
                    double curv = ck(i, j, mid);
                    if(curv < mid) {
                        r = mid;
                    } else {
                        l = mid;
                    }
                }
                dp[i][j][0] = l;
            } else {
                double v = 0;
                for(int k = 0; k < 20; ++k) {
                    v += 1.0 - dp[i - d[k]][j][1];
                }
                dp[i][j][0] = v / 20.0;
            }

            // 1 turn
            for(int k = 0; k < 20; ++k) {
                int idx[3] = { k - 1, k, k + 1 };
                if(idx[0] < 0) idx[0] += 20;
                if(idx[2] >= 20) idx[2] -= 20;

                double v = 0;
                for(int z = 0; z < 3; ++z) {
                    if(j - d[idx[z]] < 0) {
                        v += 1.0 - dp[i][j][0];
                    } else {
                        v += 1.0 - dp[i][j - d[idx[z]]][0];
                    }
                }
                v /= 3;
                dp[i][j][1] = max(dp[i][j][1], v);
            }
        }
    }

    cout << fixed << setprecision(12);
    while(1) {
        cin >> n;
        if(n == 0) break;
        cout << dp[n][n][0] << " " << dp[n][n][1] << "\n";
    }

    return 0;
}
