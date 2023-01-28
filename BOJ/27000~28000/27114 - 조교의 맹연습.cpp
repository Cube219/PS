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
    int a, b, c, k;
    cin >> a >> b >> c >> k;
    vector<vector<ll>> dp(4, vector<ll>(k + 1, LNF));
    dp[0][0] = 0;

    for(int j = 0; j <= k; ++j) {
        for(int i = 0; i < 4; ++i) {
            int nxti, nxtj;
            // A -> +1
            nxti = (i + 1) % 4;
            nxtj = j + a;
            if(nxtj <= k) dp[nxti][nxtj] = min(dp[nxti][nxtj], dp[i][j] + 1);

            // B -> -1
            nxti = (i - 1 + 4) % 4;
            nxtj = j + b;
            if(nxtj <= k) dp[nxti][nxtj] = min(dp[nxti][nxtj], dp[i][j] + 1);

            // C -> +2
            nxti = (i + 2) % 4;
            nxtj = j + c;
            if(nxtj <= k) dp[nxti][nxtj] = min(dp[nxti][nxtj], dp[i][j] + 1);
        }
    }

    if(dp[0][k] == LNF) cout << "-1";
    else cout << dp[0][k];
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
