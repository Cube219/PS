#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;
constexpr int INF = 0x3f3f3f3f;
constexpr ll LNF = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 1'000'000'007;

void solve()
{
    string str;
    cin >> str;

    int h = (str[0] - '0') * 10 + (str[1] - '0');
    int m = (str[3] - '0') * 10 + (str[4] - '0');
    m += h * 60;

    vector<int> dp(3601, INF);
    dp[0] = 0;
    vector<int> gap = { 10, 30, 60, 600 };
    for(int i = 0; i < 3601; ++i) {
        for(int g : gap) {
            if(i + g < 3601) dp[i + g] = min(dp[i + g], dp[i] + 1);
        }
    }

    int res = dp[m] + 1;
    if(m >= 30) res = min(res, dp[m - 30] + 1);

    cout << res;
}

int main()
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int tNum = 1;
    // cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        solve();
    }

    return 0;
}
