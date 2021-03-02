#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
using namespace std;

using ll = long long int;

int n, d[1000001];
bool dp[1000001][2][2];
bool res = true;

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for(int i = 0; i < n; ++i) {
        cin >> d[i];
        if(d[i] > 2) res = false;
    }

    // 0 : right
    // 1 : left
    if(d[0] == 0) {
        dp[0][0][0] = true;
        dp[0][1][1] = true;
    } else if(d[0] == 1) {
        dp[0][0][1] = true;
        dp[0][1][0] = true;
    } else {
        res = false;
    }
    for(int i = 1; i < n - 1; ++i) {
        if(d[i] == 0) {
            if(dp[i - 1][0][0] == true || dp[i - 1][1][1] == true) {
                dp[i][0][0] = true;
                dp[i][1][1] = true;
            }
            if(dp[i - 1][0][1] == true || dp[i - 1][1][0] == true) {
                dp[i][0][1] = true;
                dp[i][1][0] = true;
            }
        } else if(d[i] == 1) {
            if(dp[i - 1][0][0] == true || dp[i - 1][1][1] == true) {
                dp[i][0][1] = true;
                dp[i][1][0] = true;
            }
            if(dp[i - 1][0][1] == true || dp[i - 1][1][0] == true) {
                dp[i][0][0] = true;
                dp[i][1][1] = true;
            }
        } else {
            if(dp[i - 1][0][1] == true || dp[i - 1][1][0] == true) {
                dp[i][0][1] = true;
                dp[i][1][0] = true;
            }
        }
    }
    if(d[n - 1] == 0) {
        if(dp[n - 2][0][0] == false && dp[n - 2][1][1] == false) {
            res = false;
        }
    } else if(d[n - 1] == 1) {
        if(dp[n - 2][0][1] == false && dp[n - 2][1][0] == false) {
            res = false;
        }
    } else {
        res = false;
    }

    if(res == false) cout << "NO";
    else cout << "YES";

    return 0;
}
