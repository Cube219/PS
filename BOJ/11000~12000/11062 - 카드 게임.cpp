#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
using namespace std;

using lli = long long int;

int tNum;
int n, d[1001];
pair<int, int> dp[1001][1001];

pair<int, int> p(int l, int r)
{
    if(l == r) return { d[l], 0 };
    else if(dp[l][r].first != 0 || dp[l][r].second != 0) return dp[l][r];

    auto left = p(l + 1, r);
    auto right = p(l, r - 1);

    if(d[l] + left.second > d[r] + right.second) {
        dp[l][r].first = d[l] + left.second;
        dp[l][r].second = left.first;
    } else {
        dp[l][r].first = d[r] + right.second;
        dp[l][r].second = right.first;
    }

    return dp[l][r];
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
            cin >> d[i];
        }
        for(int i = 0; i < n; i++) {
            for(int j = i; j < n; j++) {
                dp[i][j] = { 0, 0 };
            }
        }

        cout << p(0, n - 1).first << "\n";
    }

    return 0;
}
