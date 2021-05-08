#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;

using ll = long long int;
constexpr ll MOD = 1000000007;

char str[100005];
int d[100001];
int n;
ll dp[100001][4][4][4];

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> str;
    n = strlen(str);
    for(int i = 0; i < n; ++i) {
        if(str[i] == 'A') d[i] = 0;
        else if(str[i] == 'C') d[i] = 1;
        else if(str[i] == 'G') d[i] = 2;
        else if(str[i] == 'T') d[i] = 3;
        else d[i] = 4;
    }
    // d[i][bst][st][ed]
    for(int bst = 0; bst < 4; ++bst) {
        for(int cur = 0; cur < 4; ++cur) {
            if(d[0] != 4 && d[0] != cur) continue;
            dp[0][bst][cur][cur] = 1;
        }
    }
    for(int i = 1; i < n; ++i) {
        for(int cur = 0; cur < 4; ++cur) {
            if(d[i] != 4 && d[i] != cur) continue;

            for(int bst = 0; bst < 4; ++bst) {
                for(int st = 0; st < 4; ++st) {
                    for(int ed = 0; ed < 4; ++ed) {
                        // 잇는 경우
                        if(ed != cur) {
                            dp[i][bst][st][cur] += dp[i - 1][bst][st][ed];
                            dp[i][bst][st][cur] %= MOD;
                        }
                        // 새로 만드는 경우
                        if(bst == ed) {
                            dp[i][st][cur][cur] += dp[i - 1][bst][st][ed];
                            dp[i][st][cur][cur] %= MOD;
                        }
                    }
                }
            }
        }
    }
    ll res = 0;
    for(int ed = 0; ed < 4; ++ed) {
        for(int st = 0; st < 4; ++st) {
            res += dp[n - 1][ed][st][ed];
            res %= MOD;
        }
    }
    cout << res;

    return 0;
}
    