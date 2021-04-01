#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;
constexpr int INF = 987654321;

int n;
int map[17][17];
int dp[17][1 << 16];

int search(int cur, int set)
{
    int ret = INF;

    if(dp[cur][set] != 0) return dp[cur][set];
    if(set == (1 << n) - 1) {
        if(map[cur][0] > 0) {
            ret = map[cur][0];
        } else {
            ret = INF;
        }
    } else {
        for(int nxt = 0; nxt < n; ++nxt) {
            if(map[cur][nxt] == 0) continue;
            if((set & (1 << nxt)) > 0) continue;

            int cost = search(nxt, set | (1 << nxt)) + map[cur][nxt];
            ret = min(ret, cost);
        }
    }
    dp[cur][set] = ret;
    return ret;
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            cin >> map[i][j];
        }
    }

    cout << search(0, 1);

    return 0;
}
