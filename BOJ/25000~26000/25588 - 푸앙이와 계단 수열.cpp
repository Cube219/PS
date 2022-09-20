#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <numeric>
#include <vector>
using namespace std;

using ll = long long int;
constexpr int INF = 0x3f3f3f3f;
constexpr ll LNF = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 1'000'000'007;

void solve()
{
    int n, k;
    cin >> n >> k;
    vector<int> d(n);
    for(auto& v : d) cin >> v;

    vector<int> num(n);
    int st = 0;
    num[0] = 1;
    for(int i = 1; i < n; ++i) {
        if(abs(d[i - 1] - d[i]) != 1) st = i;
        num[i] = i - st + 1;
    }

    vector<int> dp(n + 1);
    dp[0] = 0;
    for(int i = 1; i <= n; ++i) {
        dp[i] = INF;
        // 1, 2, 3
        for(int j = 1; j <= 3; ++j) {
            if(i - j < 0) {
                break;
            }
            dp[i] = min(dp[i], dp[i - j] + 1);
        }

        // k
        if(num[i - 1] >= k && i - k >= 0) {
            dp[i] = min(dp[i], dp[i - k] + 1);
        }
    }

    cout << dp[n];
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
