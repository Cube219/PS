#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

using ll = long long int;
constexpr ll MOD = 1000000007;

int n, m, l;
string path;
char map[305][305];
ll dp[301][301][2];
ll sum[301][301];

void makesum(int idx)
{
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            sum[i][j] = dp[i][j][idx];
            if(i > 0) sum[i][j] += sum[i - 1][j];
            if(j > 0) sum[i][j] += sum[i][j - 1];
            if(i > 0 && j > 0) sum[i][j] -= sum[i - 1][j - 1];
            sum[i][j] += MOD;
            sum[i][j] %= MOD;
        }
    }
}

ll getsum(int x1, int y1, int x2, int y2)
{
    ll v = sum[x2][y2];
    x1--;
    y1--;
    if(x1 >= 0) {
        v = (v - sum[x1][y2] + MOD) % MOD;
    }
    if(y1 >= 0) {
        v = (v - sum[x2][y1] + MOD) % MOD;
    }
    if(x1 >= 0 && y1 >= 0) {
        v = (v + sum[x1][y1]) % MOD;
    }
    return v;
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m >> l >> path;
    for(int i = 0; i < n; ++i) {
        string str;
        cin >> str;
        for(int j = 0; j < m; ++j) {
            map[i][j] = str[j];
            if(map[i][j] == path[0]) {
                dp[i][j][0] = 1;
            }
        }
    }
    int psz = path.size();
    for(int z = 1; z < psz; ++z) {
        int cur = z % 2;
        int pre = 1 - cur;
        makesum(pre);
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < m; ++j) {
                dp[i][j][cur] = 0;
                if(map[i][j] != path[z]) continue;

                ll v = 0;
                if(i >= 2 && j >= 2) {
                    v = (v + getsum(0, 0, i - 2, j - 2) - dp[i - 2][j - 2][pre] + MOD) % MOD;
                }
                if(i >= 2 && j < m - 2) {
                    v = (v + getsum(0, j + 2, i - 2, m - 1) - dp[i - 2][j + 2][pre] + MOD) % MOD;
                }
                if(i < n - 2 && j >= 2) {
                    v = (v + getsum(i + 2, 0, n - 1, j - 2) - dp[i + 2][j - 2][pre] + MOD) % MOD;
                }
                if(i < n - 2 && j < m - 2) {
                    v = (v + getsum(i + 2, j + 2, n - 1, m - 1) - dp[i + 2][j + 2][pre] + MOD) % MOD;
                }

                dp[i][j][cur] = v;
            }
        }
    }

    ll res = 0;
    int cur = (psz - 1) % 2;
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            res += dp[i][j][cur];
            res %= MOD;
        }
    }
    cout << res;

    return 0;
}
