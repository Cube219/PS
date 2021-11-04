#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;
constexpr ll MX = 1000000000000000000LL;

vector<ll> dp[8000];
int n;
ll k;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> k;
    k--;

    dp[n * 2 - 1].resize(2, 0);
    dp[n * 2 - 1][1] = 1;

    for(int i = 2; i <= n; ++i) {
        int idx = n * 2 - i;
        dp[idx].resize(i + 1, 0);
        for(int j = 0; j <= i; ++j) {
            if(j > 0) dp[idx][j] += dp[idx + 1][j - 1];
            if(j <= i - 2) dp[idx][j] += dp[idx + 1][j + 1];
            if(dp[idx][j] > MX) dp[idx][j] = MX;
        }
    }

    for(int i = n - 1; i >= 1; --i) {
        dp[i].resize(i + 1, 0);
        for(int j = 0; j <= i; ++j) {
            if(j > 0) dp[i][j] += dp[i + 1][j - 1];
            dp[i][j] += dp[i + 1][j + 1];
            if(dp[i][j] > MX) dp[i][j] = MX;
        }
    }

    int cnt = 0;
    for(int i = 0; i < n * 2 - 1; ++i) {
        if(dp[i + 1].size() <= cnt + 1) {
            cout << ")";
            cnt--;
        } else if(k >= dp[i + 1][cnt + 1]) {
            cout << ")";
            k -= dp[i + 1][cnt + 1];
            cnt--;
        } else {
            cout << "(";
            cnt++;
        }
    }

    cout << ")";

    return 0;
}
