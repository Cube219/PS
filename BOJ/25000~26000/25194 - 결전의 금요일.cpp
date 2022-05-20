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
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto& v : a) {
        cin >> v;
    }

    vector<int> dp(7, 0), dp2(7, 0);
    for(int v : a) {
        v %= 7;
        dp2 = dp;
        for(int i = 7 - 1; i >= 0; --i) {
            int nxt = i + v;
            if(nxt > 6) nxt -= 7;
            if(dp[i] == 1) dp2[nxt] = 1;
        }
        dp2[v] = 1;

        swap(dp, dp2);
    }

    if(dp[4] == 1) cout << "YES";
    else cout << "NO";
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
