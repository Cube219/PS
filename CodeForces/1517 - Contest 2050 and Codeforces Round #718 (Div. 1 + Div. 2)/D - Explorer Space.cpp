#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

using ll = long long int;
constexpr ll INF = 999999999999999;

int n, m, k;
ll dp[501][501][2], dp2[501][501];
int l[501][501], r[501][501], u[501][501], d[501][501];

ll res[501][501];

void process()
{
    if(k % 2 == 1) {
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < m; ++j) {
                res[i][j] = -1;
            }
        }
        return;
    }

    for(int cnt = 0; cnt < k / 2; ++cnt) {
        int cur = cnt % 2;
        int pre = 1 - cur;

        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < m; ++j) {
                dp[i][j][cur] = INF;
            }
        }

        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < m; ++j) {
                // l->r
                if(j > 0) {
                    if(dp[i][j][cur] > dp[i][j - 1][pre] + r[i][j - 1]) {
                        dp[i][j][cur] = dp[i][j - 1][pre] + r[i][j - 1];
                    }
                }
                // r->l
                if(j < m - 1) {
                    if(dp[i][j][cur] > dp[i][j + 1][pre] + l[i][j + 1]) {
                        dp[i][j][cur] = dp[i][j + 1][pre] + l[i][j + 1];
                    }
                }
                // u->d
                if(i > 0) {
                    if(dp[i][j][cur] > dp[i - 1][j][pre] + d[i -1][j]) {
                        dp[i][j][cur] = dp[i - 1][j][pre] + d[i - 1][j];
                    }
                }
                // d->u
                if(i < n - 1) {
                    if(dp[i][j][cur] > dp[i + 1][j][pre] + u[i + 1][j]) {
                        dp[i][j][cur] = dp[i + 1][j][pre] + u[i + 1][j];
                    }
                }
            }
        }
    }

    int cur = (k / 2 - 1) % 2;
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            if(dp[i][j][cur] == INF) {
                res[i][j] = -1;
            } else {
                res[i][j] = dp[i][j][cur] * 2;
            }
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

    cin >> n >> m >> k;
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m - 1; ++j) {
            int a;
            cin >> a;
            r[i][j] = a;
            l[i][j + 1] = a;
        }
    }
    for(int i = 0; i < n - 1; ++i) {
        for(int j = 0; j < m; ++j) {
            int a;
            cin >> a;
            d[i][j] = a;
            u[i + 1][j] = a;
        }
    }

    process();

    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            cout << res[i][j] << " ";
        }
        cout << "\n";
    }

    return 0;
}
