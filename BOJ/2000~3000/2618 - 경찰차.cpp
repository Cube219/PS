#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <string.h>
using namespace std;

using lli = long long int;
int n, w, px[1001], py[1001];
int dp[1001][1001], r[1001][1001];

int p(int a, int b)
{
    if(a == w || b == w) return 0;
    if(dp[a][b] != -1) return dp[a][b];

    int next = max(a, b) + 1;

    int ax = px[a];
    int ay = py[a];
    if(a == 0) {
        ax = 1;
        ay = 1;
    }
    int bx = px[b];
    int by = py[b];
    if(b == 0) {
        bx = n;
        by = n;
    }

    int moveX = p(next, b) + (abs(ax - px[next]) + abs(ay - py[next]));
    int moveY = p(a, next) + (abs(bx - px[next]) + abs(by - py[next]));

    if(moveX < moveY) {
        dp[a][b] = moveX;
        r[a][b] = 1;
    } else {
        dp[a][b] = moveY;
        r[a][b] = 2;
    }

    return dp[a][b];
}

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> w;
    for(int i = 1; i <= w; i++) {
        cin >> px[i] >> py[i];
    }

    memset(dp, -1, sizeof(dp));

    p(0, 0);

    cout << dp[0][0] << "\n";
    int a = 0, b = 0;
    for(int i = 1; i <= w; i++) {
        cout << r[a][b] << "\n";
        if(r[a][b] == 1) {
            a = i;
        } else {
            b = i;
        }
    }

    return 0;
}
