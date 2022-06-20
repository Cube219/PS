#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <iomanip>
#include <numeric>
#include <vector>
using namespace std;

using ll = long long int;
constexpr int INF = 0x3f3f3f3f;
constexpr ll LNF = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 1'000'000'007;

void solve()
{
    int n, len;
    cin >> n >> len;
    vector<int> d(n);
    for(auto& v : d) cin >> v;

    vector<int> dp(1011, -INF);
    dp[0] = 0;
    for(int v : d) {
        for(int i = 1010 - (v - 5); i >= 0; --i) {
            if(dp[i + (v - 5)] < dp[i] + 1) {
                dp[i + (v - 5)] = dp[i] + 1;
            }
        }
    }

    double res = -1;
    for(int i = len - 5; i >= 0; --i) {
        if(dp[i] <= 0) continue;

        int gap = len - i - 5;
        double v = (double)gap / (dp[i] + 1);
        if(v > 5.0) continue;
        res = max(res, 5.0 - v);
    }

    cout << fixed << setprecision(10);
    if(res < 0) cout << "impossible";
    else cout << res;
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
