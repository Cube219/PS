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

ll n, k;
ll dp[51][52];

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> k;

    dp[n - 1][1] = 1;
    for(int i = n - 2; i >= 0; --i) {
        for(int j = 0; j <= 50; ++j) {
            dp[i][j] = dp[i + 1][j + 1];
            if(j > 0) dp[i][j] += dp[i + 1][j - 1];
        }
    }
    string res;
    int cnt = 0;
    for(int i = 0; i < n - 1; ++i) {
        // (
        if(k < dp[i + 1][cnt + 1]) {
            res.push_back('(');
            cnt++;
        } else {
            res.push_back(')');
            k -= dp[i + 1][cnt + 1];
            cnt--;
            if(cnt < 0) {
                res.clear();
                break;
            }
        }
    }

    if(res.size() == 0) cout << "-1";
    else cout << res << ')';

    return 0;
}
