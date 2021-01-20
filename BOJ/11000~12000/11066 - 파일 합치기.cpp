#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
using namespace std;

using lli = long long int;

int tNum;
int n, d[501], dp[501][501];
int sum[501];

int p(int s, int e)
{
    if(s == e) return 0;
    else if(dp[s][e] != -1) return dp[s][e];

    int min = 987654321;
    for(int i = s; i < e; i++) {
        int left = p(s, i);
        int right = p(i + 1, e);
        if(min > left + right) min = left + right;
    }

    min += sum[e];
    if(s > 0) {
        min -= sum[s - 1];
    }

    dp[s][e] = min;
    return min;
}

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        cin >> n;

        for(int i = 0; i < n; i++) {
            for(int j = i + 1; j < n; j++) {
                dp[i][j] = -1;
            }
        }

        for(int i = 0; i < n; i++) {
            cin >> d[i];
        }

        sum[0] = d[0];
        for(int i = 1; i < n; i++) {
            sum[i] = sum[i - 1] + d[i];
        }

        cout << p(0, n - 1) << "\n";
    }

    return 0;
}
