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
constexpr int INF = 987654321;

int n;
int num[16][26];
ll dp[1 << 16];
int tnum[26];

ll p(int mask)
{
    if(dp[mask] != -1) return dp[mask];

    for(int i = 0; i < 26; ++i) {
        tnum[i] = INF;
    }
    for(int i = 0; i < n; ++i) {
        if((mask & (1 << i)) == 0) continue;

        for(int j = 0; j < 26; ++j) {
            tnum[j] = min(tnum[j], num[i][j]);
        }
    }
    int cnt = 0;
    for(int i = 0; i < 26; ++i) {
        cnt += tnum[i];
    }

    if((mask & -mask) == mask) {
        dp[mask] = cnt;
        return dp[mask];
    }

    int nxt = (mask - 1) & mask;
    dp[mask] = INF;
    while(nxt > 0) {
        ll a = p(nxt);
        ll b = p(mask ^ nxt);
        dp[mask] = min(dp[mask], a + b - cnt);
        nxt = (nxt - 1) & mask;
    }
    return dp[mask];
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int total = 0;
    cin >> n;
    for(int i = 0; i < n; ++i) {
        string str;
        cin >> str;
        for(int j = 0; j < str.size(); ++j) {
            num[i][str[j] - 'a']++;
            total++;
        }
    }

    for(int i = (1<<n) - 1; i >= 1; --i) {
        dp[i] = -1;
    }

    cout << p((1 << n) - 1) + 1;

    return 0;
}
