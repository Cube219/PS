#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;
constexpr ll MOD = 100000000;

int n, m;
int map[13][13], mrbit[13];
ll dp[13][1 << 13];

bool valid(int v)
{
    for(int i = 0; i < m - 1; ++i) {
        int lbit = 1 << i;
        int rbit = 1 << (i + 1);
        if((v & lbit) > 0 && (v & rbit) > 0) return false;
    }
    return true;
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
        for(int j = 0; j < m; ++j) {
            cin >> map[i][j];
        }
        for(int j = 0; j < m; ++j) {
            mrbit[i] += (1 - map[i][j]) * (1 << j);
        }
    }
    for(int i = 0; i < 1 << m; ++i) {
        if((mrbit[0] & i) > 0 || valid(i) == false) continue;
        dp[0][i] = 1;
    }
    for(int i = 1; i < n; ++i) {
        for(int j = 0; j < 1 << m; ++j) {
            if((mrbit[i] & j) > 0 || valid(j) == false) continue;
            for(int k = 0; k < 1 << m; ++k) {
                if((j & k) > 0) continue;
                dp[i][j] += dp[i - 1][k];
                dp[i][j] %= MOD;
            }
        }
    }
    ll res = 0;
    for(int i = 0; i < 1 << m; ++i) {
        res += dp[n - 1][i];
        res %= MOD;
    }
    cout << res;

    return 0;
}
