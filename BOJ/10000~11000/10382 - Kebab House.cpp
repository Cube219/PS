#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;
constexpr ll MOD = 1000000007;

int n, t, nn;
int x[1001], q[1001];

ll dp[250][251];
ll sum[250001];

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> t;
    for(int i = 0; i < n; ++i) {
        cin >> q[i] >> x[i];
        nn += q[i];
    }

    int idx = 0;
    for(int cur = 0; cur < n; ++cur) {
        int gap = q[cur] - x[cur];
        // i=0
        for(int j = 0; j <= 250; ++j) {
            dp[0][j] = 0;
        }
        if(gap > 0) {
            if(idx - t - 1 >= 0) {
                dp[0][gap - 1] = sum[idx - t - 1];
                dp[0][gap - 1] %= MOD;
            } else {
                dp[0][gap - 1] = 1;
            }
            sum[idx] += dp[0][gap - 1];
            sum[idx] %= MOD;
        }
        if(cur > 0) {
            dp[0][gap] = sum[idx - 1];
            dp[0][gap] %= MOD;
        } else {
            dp[0][gap] = 1;
        }
        sum[idx] += dp[0][gap];
        sum[idx] %= MOD;
        idx++;
        for(int i = 1; i < q[cur]; ++i) {
            for(int j = 0; j <= gap; ++j) {
                // not sleep
                dp[i][j] = dp[i - 1][j];
                dp[i][j] %= MOD;

                // sleep
                if(j < gap) {
                    if(i - t - 1 < 0) {
                        if(j == gap - 1) {
                            if(idx - t - 1 >= 0) {
                                dp[i][j] += sum[idx - t - 1];
                                dp[i][j] %= MOD;
                            } else {
                                dp[i][j] += 1;
                                dp[i][j] %= MOD;
                            }
                        }
                    } else {
                        dp[i][j] += dp[i - t - 1][j + 1];
                        dp[i][j] %= MOD;
                    }
                }
                sum[idx] += dp[i][j];
                sum[idx] %= MOD;
            }
            idx++;
        }
    }

    cout << sum[nn - 1];

    return 0;
}
