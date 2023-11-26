#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <algorithm>
#include <cstdio>
#include <iostream>
#include <numeric>
#include <utility>
#include <vector>
using namespace std;

using ll = long long int;
constexpr int INF = 0x3f3f3f3f;
constexpr ll LNF = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 1'000'000'007;

void solve()
{
    ll n, m, k;
    cin >> n >> m >> k;
    vector<ll> a(n + 32, 0);
    for(int i = 0; i < n + 1; ++i) {
        cin >> a[i];
    }

    vector<vector<ll>> dp(n + 32, vector<ll>(k));
    for(int i = 0; i < n + 32; ++i) {
        dp[i][0] = a[i];
        if(i > 0 && dp[i - 1][0] > 0) dp[i][0] += dp[i - 1][0] / k;

        for(int j = 1; j < k; ++j) {
            dp[i][j] = dp[i][j - 1] - m;
        }
    }

    vector<int> res;
    ll reqNum = 0;
    for(int i = n + 32 - 1; i >= 0; i--) {
        for(int j = k - 1; j >= 0; j--) {
            if(dp[i][j] >= reqNum) {
                if(res.size() > 0 || j > 0) res.push_back(j);

                reqNum = max(0LL, (j * m + reqNum) - a[i]);
                reqNum *= k;

                break;
            }
        }
    }

    if(res.size() == 0)
        cout << "0";
    else {
        for(auto& v : res) cout << v;
    }
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
