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
    int n;
    cin >> n;
    vector<vector<ll>> dp(n, vector<ll>(2, -LNF));

    auto cal = [](char op, ll l, ll r) -> ll {
        if(l <= 0) return -LNF;
        if(op == '+') return l + r;
        else if(op == '-') return l - r;
        else if(op == '*') return l * r;
        else return l / r;
    };

    for(int i = 0; i < n; ++i) {
        string s[2];
        cin >> s[0] >> s[1];

        for(int j = 0; j < 2; ++j) {
            char op = s[j][0];
            ll v = s[j][1] - '0';

            if(i == 0) {
                dp[i][0] = max(dp[i][0], cal(op, 1, v));
                if(dp[i][0] <= 0) dp[i][0] = -LNF;
                dp[i][1] = 1;
            } else {
                dp[i][0] = max(dp[i][0], cal(op, dp[i - 1][0], v));
                dp[i][1] = max(dp[i][1], cal(op, dp[i - 1][1], v));
                dp[i][1] = max(dp[i][1], dp[i - 1][0]);
            }
        }
    }
    ll res = max(dp[n - 1][0], dp[n - 1][1]);
    if(res <= 0) cout << "ddong game";
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
